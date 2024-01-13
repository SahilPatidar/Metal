#include"../../include/codegen/LLVMCodeGen.hpp"
#include<llvm/IR/ConstantFold.h>
#include<llvm/IR/Constant.h>
#include<llvm/IR/DerivedTypes.h>
#include<llvm/IR/BasicBlock.h>
#include<llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include"../../include/Error.hpp"
#include"../../include/parser/type.hpp"
// #include <llvm/Support/Casting.h>
#include<iostream>
#include<stdlib.h>




#include "llvm/IR/Intrinsics.h"

namespace codegen{



Value *IRCodegenVisitor::codeGenIdentifier(ast::Identifier *AstNode) {
    dumpir1("Identifier");
    std::string Ident = AstNode->getIdent();

    if(ResMgr.Has(Ident)){
        return ResMgr.getInfo(Ident);
    }
    BasicBlock *BB = Builder.GetInsertBlock();
    // Value *Val = codeGenStmt(AstNode->getDecl());
    Value *Val = codeGenImportStmt(AstNode->getDecl());
    Builder.SetInsertPoint(BB);
    dumpir2("Identifier");
    return Val;
}

Value *IRCodegenVisitor::codeGenGroupedExpr(ast::GroupedExpr *AstNode ){
    dumpir1("GroupedExpr");
    return codeGenStmt(AstNode->getExpression());
}

Constant *IRCodegenVisitor::codeGenNumericLiteral(ast::NumericLiteral *AstNode) {
    dumpir1("NumericLiteral");
    return ConstantInt::get(getTypeUsingStmtTypeInfo(AstNode->getTypeInfo()), AstNode->getLexeme().getDataInt());
}

Constant *IRCodegenVisitor::codeGenNullLiteral(ast::NullLiteral *AstNode) {
    dumpir1("NullLiteral");
    return ConstantPointerNull::get(PointerType::get(Context, 0));
}


Constant *IRCodegenVisitor::codeGenFloatLiteral(ast::FloatLiteral *AstNode) {
    dumpir1("FloatLiteral");
    return ConstantFP::get(Context, APFloat((double)AstNode->getLexeme().getDataFlt()));
}


Constant *IRCodegenVisitor::codeGenBoolLiteral(ast::BoolLiteral *AstNode) {
    dumpir1("BoolLiteral");
    return AstNode->getLexeme().getTokTy() == ast::TRUE?ConstantInt::getTrue(Context): ConstantInt::getFalse(Context);
}    


Constant *IRCodegenVisitor::codeGenStringLiteral(ast::StringLiteral *AstNode) {
    dumpir1("StringLiteral");
    Constant* StrVal;
    if(AstNode->ischar()) {
        StrVal = ConstantInt::get(getTypeUsingStmtTypeInfo(AstNode->getTypeInfo()), (uint8_t)AstNode->getLexeme().getDataInt());
    }else
        StrVal = Builder.CreateGlobalStringPtr(AstNode->getLexeme().getStr());

    return StrVal;
}


Value *IRCodegenVisitor::codegenFieldExpr(ast::FieldExpr *AstNode, Value *Alloca) {
    dumpir1(__func__);
    std::vector<ast::Ast *> &Field = AstNode->getArgs();
    if(isConstF || AstNode->isCF()) {
        std::vector<Constant *> ArrayVals;
        for(size_t i = 0, size = Field.size(); i < size; i++) {
            ArrayVals.push_back(codeGenConst(Field[i]));
            if(!ArrayVals.back()) {
                err::err_out(AstNode, "unable convert to IR");
                return nullptr;
            }
        }
        Type *ArrTy = getTypeUsingStmtTypeInfo(AstNode->getTypeInfo());
        return ConstantArray::get(static_cast<ArrayType *>(ArrTy), ArrayVals);
    }
    Type *ArrTy = nullptr;
    if(!Alloca) {
        ArrTy = getTypeUsingStmtTypeInfo(AstNode->getTypeInfo());
        Alloca = Builder.CreateAlloca(ArrTy);
    }else{
        ArrTy = static_cast<AllocaInst *>(Alloca)->getAllocatedType();
    }


    Type *I64 = Type::getInt64Ty(Context);
    Value *OffVal = Builder.CreateInBoundsGEP(ArrTy, Alloca, {ConstantInt::get(I64, 0), ConstantInt::get(I64, 0)});
    for(size_t i = 0, size = Field.size(); i < size; i++) {
        Value *Val = codeGenStmt(Field[i]);
        if(!Val) {
            err::err_out(AstNode, "unable convert to IR");
            return nullptr;
        }

        if(Val->getType()->isPointerTy()) {
            Val = LoadValue(Field[i], Val, getTypeUsingStmtTypeInfo(Field[i]->getTypeInfo()));
        }
        Builder.CreateStore(Val, OffVal);
        if(i + 1 != size)
            OffVal = Builder.CreateInBoundsGEP(ArrTy->getArrayElementType(), OffVal, {ConstantInt::get(I64, 1)});
    }
    dumpir2(__func__);
    return Alloca;
}


Value *IRCodegenVisitor::codeGenPrefixExpr(ast::PrefixExpr *AstNode) {
    dumpir1(__func__);
    ast::Token_type Op = AstNode->getOp().getTokType();
    ast::Ast *Var = AstNode->getBase();
    Value *Val = codeGenStmt(Var);
    Type *VTy = getType(Val, Var);
    if(!Val){
        err::err_out(Var, "unable to convert prefix expr to ir");
        return nullptr;
    }
    switch (Op)
    {
    case ast::STAR:
    {
        if(!Var->Is(ast::NodePrefix) && dyn_cast<CallInst>(Val)) {
            return Val;
        }
        Val = Builder.CreateLoad(Val->getType(), Val);
        if(!Val) {
            return nullptr;
        } 
            dumpir2(__func__);
        return Val;
    }
        break;
    case ast::AND:
    {
        return Val;
    }
        break;
    case ast::PLUS:
    case ast::MINUS:
    {
        return Builder.CreateNeg(LoadValue(Var, Val, VTy));
    }
        break;
    case ast::CND_NOT:
    case ast::NOT:
    {
        return Builder.CreateNot(LoadValue(Var, Val, VTy));
    }
        break;
    default:
        break;
    }
    return nullptr;
}

Value *IRCodegenVisitor::codegenPhiAndCond(ast::Expression &Expr) {
    const ast::Tok &Op = Expr.getOp();
    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();

    Value *Lhs = nullptr;
    Value *Rhs = nullptr;
    Value *LhsOp = Lhs;
    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    // BasicBlock *PhiBB = BasicBlock::Create(Context);
    BasicBlock *PhiBB = FalseBB.back();
    BasicBlock *TBB = BasicBlock::Create(Context);
    putTrueBB(TBB);
    Lhs = codeGenStmt(LhsExpr);
    dropTrueBB();
    if(!Lhs){
        err::err_out(LhsExpr, "unable convert binary expression to IR");
        return nullptr;
    }
    if(!dyn_cast<BranchInst>(Lhs)) {
        Builder.CreateCondBr(Lhs, TBB, PhiBB);
    }
    TheFunction->insert(TheFunction->end(), TBB);
    Builder.SetInsertPoint(TBB);

    dropFalseBB();
    Rhs = codeGenStmt(RhsExpr);
    if(!Rhs){
        err::err_out(RhsExpr, "IR generation failed");
        return nullptr;
    }

    Builder.CreateBr(PhiBB);
    TheFunction->insert(TheFunction->end(), PhiBB);
    Builder.SetInsertPoint(PhiBB);
    PHINode *Phi = GenPHI(Rhs, Type::getInt1Ty(Context));
    if(!Phi) {
        err::err_out(RhsExpr, "Falied to generate PHI");
        return nullptr;
    }
    return Phi;
}

Value *IRCodegenVisitor::codegenAndCond(ast::Expression &Expr) {
    const ast::Tok &Op = Expr.getOp();
    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();

    Value *Lhs = nullptr;
    Value *Rhs = nullptr;
    Value *LhsOp = Lhs;
    Function *TheFunction = Builder.GetInsertBlock()->getParent();

    if(FalseBB.empty()) {
        BasicBlock *FinalBB = BasicBlock::Create(Context);
        putFalseBB(FinalBB);
        return codegenPhiAndCond(Expr);
    }

    /// put true block in stack that lhs can use it if lhs condition become true.
    /*
    ...
    ...
    br lhs, truebb, falsebb
    truebb:
        ...
        ...
    */
    BasicBlock *TBB = BasicBlock::Create(Context);
    putTrueBB(TBB);
    Lhs = codeGenStmt(LhsExpr);
    dropTrueBB();
    if(!Lhs){
        err::err_out(LhsExpr, "unable convert binary expression to IR");
        return nullptr;
    }

    if(!dyn_cast<BranchInst>(Lhs)) {
        Builder.CreateCondBr(Lhs, TBB, FalseBB.back());
    }

    TheFunction->insert(TheFunction->end(), TBB);
    Builder.SetInsertPoint(TBB);

    Rhs = codeGenStmt(RhsExpr);
    if(!Rhs) {
        err::err_out(RhsExpr, "unable convert binary expression to IR");
        return nullptr;
    }

    if(!TrueBB.empty() && !FalseBB.empty()) {
        if(!dyn_cast<BranchInst>(Rhs)) {
            return Builder.CreateCondBr(Rhs, TrueBB.back(), FalseBB.back());
        }
    }
    // if(FalseBB.empty()){}

    return Rhs;
}

Value *IRCodegenVisitor::codegenPhiOrCond(ast::Expression &Expr) {
    const ast::Tok &Op = Expr.getOp();
    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();

    Value *Lhs = nullptr;
    Value *Rhs = nullptr;

    Function *TheFunction = Builder.GetInsertBlock()->getParent();

    BasicBlock *PhiBB = TrueBB.back();
    BasicBlock *FBB = BasicBlock::Create(Context);
    putFalseBB(FBB);
    Lhs = codeGenStmt(LhsExpr);
    dropFalseBB();
    if(!Lhs){
        err::err_out(LhsExpr, "unable convert binary expression to IR");
        return nullptr;
    }

    if(!dyn_cast<BranchInst>(Lhs)) {
        Builder.CreateCondBr(Lhs, PhiBB, FBB);
    }

    TheFunction->insert(TheFunction->end(), FBB);
    Builder.SetInsertPoint(FBB);

    dropTrueBB();
    Rhs = codeGenStmt(RhsExpr);
    if(!Rhs) {
        err::err_out(RhsExpr, "unable convert binary expression to IR");
        return nullptr;
    }

    // if(FalseBB.empty())
    //     return Rhs;

    Builder.CreateBr(PhiBB);
    TheFunction->insert(TheFunction->end(), PhiBB);
    Builder.SetInsertPoint(PhiBB);
    PHINode *Phi = GenPHI(Rhs, Type::getInt1Ty(Context));
    if(!Phi) {
        err::err_out(RhsExpr, "Falied to generate PHI");
        return nullptr;
    }

    return Phi;
}

Value *IRCodegenVisitor::codegenOrCond(ast::Expression &Expr) {
    const ast::Tok &Op = Expr.getOp();
    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();

    Value *Lhs = nullptr;
    Value *Rhs = nullptr;

    Function *TheFunction = Builder.GetInsertBlock()->getParent();

    if(TrueBB.empty()) {
        BasicBlock *FinalBB = BasicBlock::Create(Context);
        putTrueBB(FinalBB);
        return codegenPhiOrCond(Expr);
    }

    /// put true block in stack that lhs can use it if lhs condition become true.
    /*
    ...
    ...
    br lhs, truebb, falsebb
    truebb:
        ...
        ...
    */
    BasicBlock *FBB = BasicBlock::Create(Context);
    putFalseBB(FBB);
    Lhs = codeGenStmt(LhsExpr);
    dropFalseBB();

    if(!Lhs){
        err::err_out(LhsExpr, "unable convert binary expression to IR");
        return nullptr;
    }

    if(!dyn_cast<BranchInst>(Lhs)) {
        Builder.CreateCondBr(Lhs, TrueBB.back(), FBB);
    }
    TheFunction->insert(TheFunction->end(), FBB);
    Builder.SetInsertPoint(FBB);

    Rhs = codeGenStmt(RhsExpr);
    if(!Rhs) {
        err::err_out(RhsExpr, "unable convert binary expression to IR");
        return nullptr;
    }

    if(!TrueBB.empty() && !FalseBB.empty()) {
        if(!dyn_cast<BranchInst>(Rhs)) {
            return Builder.CreateCondBr(Rhs, TrueBB.back(), FalseBB.back());
        }
        // return Rhs;
    }
    return Rhs;
}

void extractIntegerTypeInfo(Value *Val, bool &IsSigned, uint64_t &Mask) {
    if (IntegerType *ITy = dyn_cast<IntegerType>(Val->getType())) {
        IsSigned = ITy->getSignBit();
        Mask = ITy->getBitMask();
    }
}

// Function to check and extract floating-point type information
bool isFloatingPointType(Value *Val) {
    return Val->getType()->isFloatTy() || Val->getType()->isDoubleTy();
}

Value *IRCodegenVisitor::codegenBinaryExpr(ast::Expression &Expr) {
    dumpir1("codegenBinaryExpr");
    const ast::Tok &Op = Expr.getOp();
    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();

    Value *Lhs = nullptr;
    Value *Rhs = nullptr;
    if(Op.getTokType() == ast::CND_AND || Op.getTokType() == ast::CND_OR) {
        if(Op.getTokType() == ast::CND_AND)
            return codegenAndCond(Expr);
        else
            return codegenOrCond(Expr);
    }

    if(Op.IsAssignOP() || Op.IsAssnCombinedOP()) {
        Rhs = codeGenStmt(RhsExpr);
        Lhs = codeGenStmt(LhsExpr);
    }else{
        Lhs = codeGenStmt(LhsExpr);
        Rhs = codeGenStmt(RhsExpr);
    }

    if(!Lhs || !Rhs){
        err::err_out(&Expr, "unable convert binary expression to IR");
        return nullptr;
    }
    Value *Inst = nullptr;
    bool LIsS = false;
    bool RIsS = false;
    uint64_t LMask = 0;
    uint64_t RMask = 0;
    Value *LhsOp = Lhs;
    Type *LOprTy = getType(Lhs, LhsExpr);
    Type *ROprTy = getType(Rhs, RhsExpr);

    if(!Expr.getOp().IsAssignOP() && Lhs->getType()->isPointerTy()) {
        Lhs = LoadValue(LhsExpr, Lhs, LOprTy);
    }
    Rhs = LoadValue(RhsExpr, Rhs, ROprTy);
 
    extractIntegerTypeInfo(Lhs, LIsS, LMask);
    extractIntegerTypeInfo(Rhs, RIsS, RMask);

    bool IsFPTy = isFloatingPointType(Lhs) || isFloatingPointType(Rhs);
    
    switch (Op.getTokType())
    {
    case ast::PLUS:        
    {
        if(IsFPTy)
            Inst = Builder.CreateFAdd(Lhs, Rhs);
        else if(LIsS || RIsS) 
            Inst = Builder.CreateNSWAdd(Lhs, Rhs);
        else
            Inst = Builder.CreateNUWAdd(Lhs, Rhs);
    }
        break;
    case ast::MINUS:
        if(IsFPTy)
            Inst = Builder.CreateFSub(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateNSWSub(Lhs, Rhs);
            else 
                Inst = Builder.CreateNUWSub(Lhs, Rhs);

        break;
    case ast::STAR:
        if(IsFPTy)
            Inst = Builder.CreateFMul(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateNSWMul(Lhs, Rhs);
            else 
                Inst = Builder.CreateNUWMul(Lhs, Rhs);

        break;
    case ast::DIV:
        if(IsFPTy)
            Inst = Builder.CreateFDiv(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateSDiv(Lhs, Rhs);
            else 
                Inst = Builder.CreateUDiv(Lhs, Rhs);

        break;
    case ast::MODULO:
        if(IsFPTy)
            Inst = Builder.CreateFRem(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateSRem(Lhs, Rhs);
            else 
                Inst = Builder.CreateURem(Lhs, Rhs);
        break;
    case ast::LSHIFT:
        Inst = Builder.CreateLShr(Lhs, Rhs);
        break;
    case ast::RSHIFT:
        Inst = Builder.CreateShl(Lhs, Rhs);
        break;
    case ast::CND_AND:
        break;
    case ast::CND_OR:
        break;
    case ast::OR:
        Inst = Builder.CreateOr(Lhs, Rhs);
        break;
    case ast::AND:
        Inst = Builder.CreateAnd(Lhs, Rhs);
        break;
    case ast::XOR:
        Inst = Builder.CreateXor(Lhs, Rhs);
        break;
    case ast::ASN:
    {
        Inst = Builder.CreateStore(Rhs, LhsOp);
    }
        break;
    case ast::ASN_AND:
    {
        Value *Val = Builder.CreateAnd(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_DIV:
    {
        Value *Val = Builder.CreateUDiv(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_LSHIFT:
    {
        Value *Val = Builder.CreateLShr(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_MINUS:
    {
        Value *Val = Builder.CreateSub(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_MOD:
    {
        Value *Val = Builder.CreateURem(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_OR:
    {
        Value *Val = Builder.CreateOr(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_XOR:
    {
        Value *Val = Builder.CreateXor(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_PLUS:
    {
        Value *Val = Builder.CreateAdd(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::ASN_RSHIFT:
    {
        Value *Val = Builder.CreateShl(Lhs,Rhs);
        Inst = Builder.CreateStore(Val,LhsOp);
    }
        break;
    case ast::GT:
        if(IsFPTy)
            Inst = Builder.CreateFCmpOGT(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateICmpSGT(Lhs, Rhs);
            else 
                Inst = Builder.CreateICmpUGT(Lhs, Rhs);
        break;
    case ast::LT:
        if(IsFPTy)
            Inst = Builder.CreateFCmpOLT(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateICmpSLT(Lhs, Rhs);
            else 
                Inst = Builder.CreateICmpULT(Lhs, Rhs);
        break;
    case ast::GEQL:
        if(IsFPTy)
            Inst = Builder.CreateFCmpOGE(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateICmpSGE(Lhs, Rhs);
            else 
                Inst = Builder.CreateICmpUGE(Lhs, Rhs);
        break;
    case ast::LEQL:
        if(IsFPTy)
            Inst = Builder.CreateFCmpOLE(Lhs, Rhs);
        else 
            if(LIsS || RIsS) 
                Inst = Builder.CreateICmpSLE(Lhs, Rhs);
            else 
                Inst = Builder.CreateICmpULE(Lhs, Rhs);
        break;
    case ast::EQL:
        if(IsFPTy)
            Inst = Builder.CreateFCmpOEQ(Lhs, Rhs);
        else 
            Inst = Builder.CreateICmpEQ(Lhs, Rhs);
        break;     
    case ast::NEQL:
        if(IsFPTy)
            Inst = Builder.CreateFCmpONE(Lhs, Rhs);
        else 
            Inst = Builder.CreateICmpNE(Lhs, Rhs);
        break;     
    default:
        break;
    }

    dumpir2("codegenBinaryExpr");
    return Inst;
}


// Helper function to generate constant structs
Value *IRCodegenVisitor::codegenConstantStruct(Type *STy, ast::Ast *&RhsExpr) {
    std::vector<ast::Ast *> &Vals = static_cast<ast::FieldExpr *>(RhsExpr)->getArgs();
    std::vector<Constant *> FVals;

    for (size_t i = 0, size = Vals.size(); i < size; i++) {
        ast::VarStmt *V = static_cast<ast::VarStmt *>(Vals[i]);
        Constant *CVal = codeGenConst(V->getVal());

        if (!CVal) {
            err::err_out(Vals[i], "unable to convert to IR");
            return nullptr;
        }

        FVals.push_back(CVal);
    }

    return ConstantStruct::get(static_cast<StructType *>(STy), FVals);
}


bool IRCodegenVisitor::codegenStructElement(Type *STy, Value *Alloca, ast::VarStmt *V, size_t idx) {
    Value *Val = codeGenStmt(V->getVal());

    if (!Val) {
        err::err_out(V->getVal(), "unable to convert to IR");
        return false;
    }

    Value *Addr = Builder.CreateStructGEP(STy, Alloca, idx);
    Type *Ty = getType(Val, V->getVal());

    if (!Ty) {
        err::err_out(V->getVal(), "unable to convert to IR");
        return false;
    }

    Val = LoadValue(V->getVal(), Val, Ty);
    Builder.CreateStore(Val, Addr);

    return true;
}

Value *IRCodegenVisitor::codegenStructExpr(ast::Expression &Expr, Value *Alloca) {
        dumpir1("codegenStructExpr");

    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();
    Type *STy = codeGenTy(LhsExpr);
    std::vector<ast::Ast *>&Vals = static_cast<ast::FieldExpr *>(RhsExpr)->getArgs();

    if (isConstF || static_cast<ast::FieldExpr *>(RhsExpr)->isCF()) {
        return codegenConstantStruct(STy, RhsExpr);
    }
    if(!Alloca)
        Alloca = Builder.CreateAlloca(STy);

    for(size_t idx = 0, size = Vals.size(); idx < size; idx++) {
        ast::VarStmt *V = static_cast<ast::VarStmt *>(Vals[idx]);
        if (!codegenStructElement(STy, Alloca, V, idx)) {
            return nullptr;
        }
    }

        dumpir2("codegenStructExpr");
    return Alloca;
}


Value *IRCodegenVisitor::codegenArg(ast::Ast *Expr, Type *Ty) {
    dumpir1("codegenArg");
    Value *ArgVal = codeGenStmt(Expr);
    if(!ArgVal) {
        return nullptr;
    }   
    if(!Ty)
        Ty = getType(ArgVal, Expr);

    ArgVal = LoadValue(Expr, ArgVal, Ty);
    dumpir2("codegenArg");
    return ArgVal;
}


Value *IRCodegenVisitor::codegenCallExpr(ast::Expression &Expr, Value *Alloca) {
        dumpir1("codegenCallExpr");
    Value *V = codeGenStmt(Expr.getLhs());
    FunctionType *FunTy = nullptr;

    // Check if V is a pointer type and load if necessary
    if(dyn_cast<GetElementPtrInst>(V) || dyn_cast<AllocaInst>(V) || dyn_cast<LoadInst>(V)) {
        Type *Ty = getType(V, Expr.getLhs());
        V = Builder.CreateLoad(V->getType(), V);
        if (dyn_cast<PointerType>(Ty)) {
            err::err_out(&Expr, "unable to get function type from the loaded value");
            return nullptr;
        }
        FunTy = dyn_cast<FunctionType>(Ty);
    }else {
        if (auto *Fun = dyn_cast<Function>(V)) {
            FunTy = Fun->getFunctionType();
        } else {
            err::err_out(&Expr, "expected a function value");
            return nullptr;
        }
    }

    std::vector<Value *> ArgV;
    std::vector<ast::Ast *> &Args = static_cast<ast::FieldExpr *>(Expr.getRhs())->getArgs();
    size_t i = 0;
    for(size_t siz = FunTy->getNumParams(); i < siz; i++) {
        Value *Arg = codegenArg(Args[i], FunTy->getFunctionParamType(i));
        if(!Arg) {
            return nullptr;
        }
        ArgV.push_back(Arg);
    }
    for(size_t siz = Args.size(); i < siz; i++) {
        Value *Arg = codegenArg(Args[i], nullptr);
        if(!Arg) {
            return nullptr;
        }
        ArgV.push_back(Arg);
    }
    // Handle return type for array or struct types
    if((FunTy->getReturnType()->isArrayTy() || FunTy->getReturnType()->isStructTy()) && !Alloca) {
        AllocaInst *alloca = Builder.CreateAlloca(FunTy->getReturnType());
        Value *CallV = Builder.CreateCall(FunTy, V, ArgV);
        Builder.CreateStore(CallV, alloca);
        return alloca;
    }
        dumpir2("codegenCallExpr");
    return Builder.CreateCall(FunTy, V, ArgV);
}



Value *IRCodegenVisitor::codegenIntCast(Value *Val, Type *DestTy) {
    switch (DestTy->getTypeID())
    {
    case Type::TypeID::IntegerTyID:
        return Builder.CreateIntCast(Val, DestTy, static_cast<IntegerType *>(Val->getType())->getSignBit());
    case Type::TypeID::PointerTyID:
    {
        if(Val->getType()->isIntegerTy(64)) {
            Val = Builder.CreateSExt(Val, Type::getInt64Ty(Context));
        }
        return Builder.CreateIntToPtr(Val, DestTy);
    }
    case Type::TypeID::FloatTyID:
    case Type::TypeID::DoubleTyID:
    {
        if(dyn_cast<IntegerType>(Val->getType())->getSignBit())
            return Builder.CreateSIToFP(Val, DestTy);
        return Builder.CreateUIToFP(Val, DestTy);
    }           
    default:
        break;
    }
    return nullptr;
}


Value *IRCodegenVisitor::codegenFPCast(Value *Val, Type *DestTy) {
    switch (DestTy->getTypeID())
    {
    case Type::TypeID::IntegerTyID:
    {
        if(dyn_cast<IntegerType>(DestTy)->getSignBit())
            return Builder.CreateFPToSI(Val, DestTy);
        return Builder.CreateFPToUI(Val, DestTy);
    }
    case Type::TypeID::FloatTyID:
        return Builder.CreateFPCast(Val, DestTy);
    case Type::TypeID::DoubleTyID:
        return Builder.CreateFPExt(Val, DestTy);
    default:
        break;
    }
    return nullptr;
}

Value *IRCodegenVisitor::codegenFPExtCast(Value *Val, Type *DestTy) {
    switch (DestTy->getTypeID())
    {
    case Type::TypeID::IntegerTyID:
    {
        if(dyn_cast<IntegerType>(DestTy)->getSignBit())
            return Builder.CreateFPToSI(Val, DestTy);
        return Builder.CreateFPToUI(Val, DestTy);
    }
    case Type::TypeID::FloatTyID:
        return Builder.CreateFPCast(Val, DestTy);
    case Type::TypeID::DoubleTyID:
        return Builder.CreateFPExt(Val, DestTy);
    default:
        break;
    }
    return nullptr;
}


Value *IRCodegenVisitor::codegenPtrCast(Value *Val, Type *DestTy) {
    switch (DestTy->getTypeID())
    {
    case Type::TypeID::IntegerTyID:
        return Builder.CreatePtrToInt(Val, DestTy);
    case Type::TypeID::PointerTyID:
        return Builder.CreatePointerCast(Val, DestTy);
    default:
        break;
    }
    return nullptr;
}



Value *IRCodegenVisitor::codegenCastExpr(ast::Expression &Expr) {
        dumpir1("codegenCastExpr");

    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();
    Value *Inst = nullptr;
    Value *Lhs = codeGenStmt(LhsExpr);
    if(!Lhs) {
        err::err_out(&Expr, "unable convert to IR");
        return nullptr;
    }
    Type *Ty = codeGenTy(RhsExpr);
    Lhs = LoadValue(LhsExpr, Lhs, getType(Lhs, LhsExpr));
    switch (Lhs->getType()->getTypeID())
    {
    case Type::TypeID::FloatTyID: 
        return codegenFPCast(Lhs, Ty);
    case Type::TypeID::DoubleTyID: 
        return codegenFPExtCast(Lhs, Ty);
    case Type::TypeID::IntegerTyID: 
        return codegenIntCast(Lhs, Ty);
    case Type::TypeID::PointerTyID: 
        return codegenPtrCast(Lhs, Ty);
    case Type::TypeID::TypedPointerTyID:
        break;
    default:
        break;
    }
    return nullptr;
}


Value *IRCodegenVisitor::codegenMemExpr(ast::Expression &Expr) {
        dumpir1("codegenMemExpr");

    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&RhsExpr = Expr.getRhs();
    Value *Lhs = codeGenStmt(LhsExpr);
    if(!Lhs) {
        err::err_out(&Expr, "unable convert to IR");
        return nullptr;
    }

    StructType *StTy = nullptr;
    ast::Type *Ty = LhsExpr->getTypeInfo();
    if(Ty->Is(ast::Type::PointerTy)) {
        Ty = static_cast<ast::PointerType *>(Ty)->getTo();
        StTy = static_cast<StructType *>(getTypeUsingStmtTypeInfo(Ty));
        uint32_t idx = static_cast<ast::StructType *>(Ty)->getIdx(RhsExpr->toString());
        
        if(!dyn_cast<CallInst>(Lhs)) {
            Lhs = Builder.CreateLoad(Lhs->getType(), Lhs);
        }
        return Builder.CreateStructGEP(StTy, Lhs, idx);
    }else
        StTy = static_cast<StructType *>(getType(Lhs, LhsExpr));

    uint32_t idx = static_cast<ast::StructType *>(Ty)->getIdx(RhsExpr->toString());
    Value *RhsVal = Builder.CreateStructGEP(StTy, Lhs, idx);
    if(!RhsVal) {
        err::err_out(&Expr, "unable convert to IR");
        return nullptr;
    }
    std::cout<<RhsExpr->toString()<<std::endl;
            dumpir2("codegenMemExpr");

    return RhsVal;
}


Value *IRCodegenVisitor::codegenIndexExpr(ast::Expression &Expr) {
    dumpir1("codegenIndexExpr");
    ast::Ast *&LhsExpr = Expr.getLhs();
    ast::Ast *&IdxExpr = Expr.getRhs();
    Value *Var = codeGenStmt(LhsExpr);
    Type *I64 = Type::getInt64Ty(Context);

    if(!Var){
        err::err_out(&Expr, "unable convert to IR");
        return nullptr;
    }

    std::vector<Value *>Indices;
    Type *VTy = nullptr;
    if(LhsExpr->getTypeInfo()->isPointerTy()) {
        VTy = getTypeUsingStmtTypeInfo(Expr.getTypeInfo());
        Value *Idx = codeGenStmt(IdxExpr);
        if(!Idx) {
            err::err_out(&Expr, "unable convert index expression to IR");
            return nullptr;
        }

        Idx = LoadValue(IdxExpr, Idx, getType(Idx, IdxExpr));
        if(!Idx) {
            err::err_out(&Expr, "unable convert index expression to IR");
            return nullptr;
        }

        if(Idx->getType()->getIntegerBitWidth() != 64) {
            Idx = Builder.CreateSExt(Idx, I64);
        }

        Var = LoadValue(LhsExpr, Var, Var->getType());
        if(!Var) {
            err::err_out(&Expr, "unable convert index expression to IR");
            return nullptr;
        }

        return Builder.CreateInBoundsGEP(VTy, Var, {Idx});
    }else
        VTy = getType(Var, LhsExpr);

    if(VTy->isArrayTy())
        Indices.push_back(ConstantInt::get(I64, 0));

    Value *Idx = codeGenStmt(IdxExpr);
    if(!Idx) {
        err::err_out(&Expr, "unable convert index expression to IR");
        return nullptr;
    }

    Idx = LoadValue(IdxExpr, Idx, getType(Idx, IdxExpr));
    if(!Idx) {
        err::err_out(&Expr, "unable convert index expression to IR");
        return nullptr;
    }

    if(Idx->getType()->getIntegerBitWidth() != 64) {
        Idx = Builder.CreateSExt(Idx, I64);
    }

    Indices.push_back(Idx);

    Value *Val = Builder.CreateInBoundsGEP(VTy, Var, Indices);
        dumpir2("codegenIndexExpr");
    return Val;
}

Value *IRCodegenVisitor::codeGenExtCall(ast::Expression &Expr) {
    dumpir1(__func__);
    std::string str = static_cast<ast::Identifier *>(Expr.getLhs())->getLexeme().getStr();
    if(str == "print") {
        return codeGenPrintf(static_cast<ast::FieldExpr *>(Expr.getRhs()));
    }else if(str == "scan") {
        return codeGenScanf(static_cast<ast::FieldExpr *>(Expr.getRhs()));   
    }else if(str == "make") {
        return codeGenMalloc(static_cast<ast::FieldExpr *>(Expr.getRhs()));   
    }else if(str == "del") {
        return codeGenFree(static_cast<ast::FieldExpr *>(Expr.getRhs()));
    }   
    dumpir2(__func__);
    return nullptr;
}

Value *IRCodegenVisitor::codeGenExpression(ast::Expression *AstNode, Value *Alloca) {
    dumpir1("Expression");
    switch (AstNode->getExprID())
    {
    case ast::Expression::KMemExpr:
        return codegenMemExpr(*AstNode);
    case ast::Expression::KBinaryExpr:
        return codegenBinaryExpr(*AstNode);
    case ast::Expression::KAsExpr:
        return codegenCastExpr(*AstNode);
    case ast::Expression::KCallExpr:
        return codegenCallExpr(*AstNode, Alloca);
    case ast::Expression::KExtCallExpr:
        return codeGenExtCall(*AstNode);
    case ast::Expression::KIndexExpr:
        return codegenIndexExpr(*AstNode);
    case ast::Expression::KStructExpr:
        return codegenStructExpr(*AstNode, Alloca);
    default:
        break;
    }
    dumpir2(__func__);
    return nullptr;
}

}
