#include"../../include/codegen/LLVMCodeGen.hpp"
#include<llvm/IR/ConstantFold.h>
#include<llvm/IR/Constant.h>
#include<llvm/IR/DerivedTypes.h>
#include<llvm/IR/BasicBlock.h>
#include<llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include "llvm/IR/CFG.h"
#include<iostream>
#include<stdlib.h>

#include"../../include/Error.hpp"
#include"../../include/Module.hpp"
#include"../../include/parser/type.hpp"

namespace codegen{

Value *IRCodegenVisitor::codeGenStmt(ast::Ast *AstNode, Value *Alloca) {
    // curMod = AstNode->getStmtLoc()->getMod();
    switch(AstNode->getStmtTy())
    {
    case ast::NodeFnProto: return codeGenFnProto(static_cast<ast::FunctionProto *>(AstNode));
    case ast::NodeNewStmt: return codeGenNewStmt(static_cast<ast::NewStmt *>(AstNode));
    case ast::NodeDelStmt: return codeGenDelStmt(static_cast<ast::DelStmt *>(AstNode));
    case ast::NodeFNStm: return codeGenFunctionDef(static_cast<ast::FunctionDef *>(AstNode));
    case ast::NodeBlockStm: return codeGenBlockStmt(static_cast<ast::BlockStmt *>(AstNode));
    case ast::NodeNumLit: return codeGenNumericLiteral(static_cast<ast::NumericLiteral *>(AstNode));
    case ast::NodeBoolLit: return codeGenBoolLiteral(static_cast<ast::BoolLiteral *>(AstNode));
    case ast::NodeFloatLit: return codeGenFloatLiteral(static_cast<ast::FloatLiteral *>(AstNode));
    case ast::NodeStrLit: return codeGenStringLiteral(static_cast<ast::StringLiteral *>(AstNode));
    case ast::NodeNullLit: return codeGenNullLiteral(static_cast<ast::NullLiteral *>(AstNode));
    case ast::NodeIdent: return codeGenIdentifier(static_cast<ast::Identifier *>(AstNode));
    case ast::NodeEnum: return codeGenEnumExpr(static_cast<ast::EnumExpr *>(AstNode));
    case ast::NodeExpr: return codeGenExpression(static_cast<ast::Expression *>(AstNode), Alloca);
    case ast::NodePrefix: return codeGenPrefixExpr(static_cast<ast::PrefixExpr *>(AstNode));
    case ast::NodeField: return codegenFieldExpr(static_cast<ast::FieldExpr *>(AstNode), Alloca);
    case ast::NodeGroupExpr: return codeGenGroupedExpr(static_cast<ast::GroupedExpr *>(AstNode));

    case ast::NodeIfStm: return codeGenIfStmt(static_cast<ast::IfStmt *>(AstNode));
    case ast::NodeWhileStm: return codeGenWhileLoop(static_cast<ast::WhileLoop *>(AstNode));
    case ast::NodeForStm: return codeGenForLoop(static_cast<ast::ForLoop *>(AstNode));
    case ast::NodeVarStm: return codeGenVarStmt(static_cast<ast::VarStmt *>(AstNode));
    case ast::NodeRetStm: return codeGenReturnStmt(static_cast<ast::ReturnStmt *>(AstNode));
    case ast::NodeBranchStm: return codeGenBranchStmt(static_cast<ast::BranchStmt *>(AstNode));
    case ast::NodeStructStm: return codeGenStructStmt(static_cast<ast::StructStmt *>(AstNode));
    // case ast::NodeImpl: return Constant::getNullValue(Type::getInt32Ty(Context));
    case ast::NodeImpl: return codeGenMethod(static_cast<ast::Method *>(AstNode));
    case ast::NodeUseStmt: return Constant::getNullValue(Type::getInt32Ty(Context));
    // case ast::NodeUseStmt: return codeGenImportValue(static_cast<ast::UseStmt *>(AstNode));;
    default:
        return nullptr;
        break;
    }

    return nullptr;
}

Constant *IRCodegenVisitor::codeGenConst(ast::Ast *AstNode) {
    // curMod = AstNode->getStmtLoc()->getMod();
    switch(AstNode->getStmtTy())
    {
    case ast::NodeNumLit: return codeGenNumericLiteral(static_cast<ast::NumericLiteral *>(AstNode));
    case ast::NodeBoolLit: return codeGenBoolLiteral(static_cast<ast::BoolLiteral *>(AstNode));
    case ast::NodeFloatLit: return codeGenFloatLiteral(static_cast<ast::FloatLiteral *>(AstNode));
    case ast::NodeStrLit: return codeGenStringLiteral(static_cast<ast::StringLiteral *>(AstNode));
    case ast::NodeNullLit: return codeGenNullLiteral(static_cast<ast::NullLiteral *>(AstNode));
    case ast::NodeField: 
    {
        Value *V = codegenFieldExpr(static_cast<ast::FieldExpr *>(AstNode));
        if(!V) {
            break;
        }
        return static_cast<Constant *>(V);
    }
    case ast::NodeExpr:
    {
        Value *V = nullptr;
        if(static_cast<ast::Expression *>(AstNode)->ExprTy() == ast::KStructExpr) 
            V = codeGenExpression(static_cast<ast::Expression *>(AstNode));
        if(!V) {
            break;
        }
        return static_cast<Constant *>(V);
    }
    default:
        break;
    }

    return nullptr;
}

Value *IRCodegenVisitor::codeGen(ast::Ast *tree) {
    IntrinsicFnCodegen();
    return codeGenStmt(tree);
}



Value *IRCodegenVisitor::codeGenImportStmt(ast::Ast *Stmt) {
            dumpir1(__func__);
std::cout<<Stmt->toString()<<std::endl;
    switch (Stmt->getStmtTy())
    {
    case ast::NodeVarStm:
        return codeGenVarStmt(static_cast<ast::VarStmt *>(Stmt));
    case ast::NodeFNStm:
        return codeGenFnProto(static_cast<ast::FunctionDef *>(Stmt)->getFnProto());
    case ast::NodeFnProto:
        return codeGenFnProto(static_cast<ast::FunctionProto *>(Stmt));
    case ast::NodeStructStm:
    {
        ast::StructStmt *Struct = static_cast<ast::StructStmt *>(Stmt);
        std::string SName = Struct->getName().getStr();
        StructType *StTy = StructType::create(Context, StringRef(SName));
        if(!StTy) {
            err::err_out(Struct, "unable convert to IR");
            return nullptr;
        }
        NamedTypes[SName] = StTy;
        TypeMap.insert({Struct->getTypeInfo()->getuId(), StTy});

        if(Struct->getImpl()) {
            std::vector<ast::Ast*>&MT = Struct->getImpl()->getImpl();
            for(auto &Impl: MT) {
                Value *FnVal = codeGenImportStmt(Impl);
                if(!FnVal){
                    err::err_out(Struct, "unable convert to IR");
                    return nullptr;
                }
            }
        }
        return Constant::getNullValue(Type::getInt32Ty(Context));
    }
    default:
        break;
    }
        dumpir2(__func__);

    return nullptr;
}

Value *IRCodegenVisitor::codeGenImportValue(ast::UseStmt *Imported) {
    dumpir1(__func__);
    ast::Ast *Import = Imported->getPath();
    
    if(Import->getStmtLoc()->getMod() != Imported->getStmtLoc()->getMod()) {
        ast::BlockStmt *B = static_cast<ast::BlockStmt *>(Import->getStmtLoc()->getMod()->getTree());
        for(auto &S: B->getStmts()) {
            if(!codeGenImportStmt(S)) {
                return nullptr;
            }
        }
        return Constant::getNullValue(Type::getInt32Ty(Context));
    }else{
        return codeGenImportStmt(Import->getDecl());
    }
    dumpir2(__func__);
    return nullptr;
}


PHINode *IRCodegenVisitor::GenPHI(Value *Val, Type *Ty) {    
    dumpir1(__func__);
    BasicBlock *BB = Builder.GetInsertBlock();
    PHINode *PHI = Builder.CreatePHI(Ty, pred_size(BB));
    BB->getParent()->dump();
    for(auto P: predecessors(BB)) {
        auto I = &P->back();
        Value *V = nullptr;
        if(BranchInst *BI = dyn_cast<BranchInst>(I)) {
            if(BI->isConditional()) {
                BasicBlock *TB = BI->getSuccessor(0);
                BasicBlock *FB = BI->getSuccessor(1);
                if(TB == BB) {
                    V = ConstantInt::getTrue(Context);
                }else if(FB == BB) {
                    V = ConstantInt::getFalse(Context);
                }
            }else {
                if (P->size() >= 2) {
                    // Get an iterator to the last instruction in the basic block.
                    BasicBlock::iterator LastInstr = --(P->end());

                    // Move the iterator to the second-to-last instruction.
                    --LastInstr;

                    // Access the second-to-last instruction.
                    Instruction *secondToLastValue = &(*LastInstr);

                    V = dyn_cast<Value>(secondToLastValue);
                }else {
                    V = ConstantInt::getTrue(Context);
                }
            }
        }else {
            V = dyn_cast<Value>(&(*(--(P->end()))));
        }
        PHI->addIncoming(V, P);
    } 
        dumpir2(__func__);

    return PHI;
}
Value *IRCodegenVisitor::LoadValue(ast::Ast *Expr, Value *Val, Type *Ty) {    
    dumpir1(__func__);
    if(!Val){
        return nullptr;
    }

    if(Val->getValueID() == 30) {
        return GenPHI(Val, Ty);
    }

    if(Val->getValueID() == Value::ConstantPointerNullVal) {
        return Val;
    }
    if(Val->getValueID() == Value::ConstantArrayVal) {
        return Val;
    }

    if((Expr->Is(ast::NodePrefix) && static_cast<ast::PrefixExpr *>(Expr)->getOp().getTokType() == AND)) {
        return Val;
    }
    if(Expr->Is(ast::NodeStrLit)) {
        return Val;
    }
    
    if(Expr->IsConst() || Expr->IsTydConst()) {
        return Val;
    }

    if(Ty->isPointerTy()) {
        if(AllocaInst *A = dyn_cast<AllocaInst>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }else if(GetElementPtrInst *GEP = dyn_cast<GetElementPtrInst>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }else if(GlobalVariable *L = dyn_cast<GlobalVariable>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }else if(LoadInst *L = dyn_cast<LoadInst>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }

    }
    else if(Val->getType()->isPointerTy()) {
        if(AllocaInst *A = dyn_cast<AllocaInst>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }else if(CallInst *C = dyn_cast<CallInst>(Val)) {
            return Val;
        }else if(LoadInst *L = dyn_cast<LoadInst>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }else if(GlobalVariable *L = dyn_cast<GlobalVariable>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }else if(GetElementPtrInst *GEP = dyn_cast<GetElementPtrInst>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }else if(ConstantExpr *GEP = dyn_cast<ConstantExpr>(Val)) {
            return Builder.CreateLoad(Ty, Val);
        }

    }

    dumpir2(__func__);
    return Val;
}


Type *IRCodegenVisitor::getType(Value *Val, ast::Ast *Expr) {
    dumpir1(__func__);
    if((Expr->Is(ast::NodePrefix) && static_cast<ast::PrefixExpr *>(Expr)->getOp().getTokType() == AND)) {
        return Val->getType();
    }
    // if(AllocaInst *A = dyn_cast<AllocaInst>(Val)) {
    //     return A->getAllocatedType();
    // }

    if(Val->getType()->isPointerTy())
        return getTypeUsingStmtTypeInfo(Expr->getTypeInfo());
    dumpir2(__func__);
    return Val->getType();
}


Value *IRCodegenVisitor::StoreValue(Value *Val, Value *Ptr, Type *Ty, Type *ValTy) {
    dumpir1(__func__);
    if(ValTy->isFunctionTy()) {
        return Builder.CreateStore(Val, Ptr);
    }
    dumpir2(__func__);
    return Builder.CreateStore(Val, Ptr);
}


Value *IRCodegenVisitor::codeGenMemCpy(Type *Ty, Value *Ptr, Value *Val) {
    Function *memcpyFunc = TheModule.getFunction("llvm.memcpy.p0i8.p0i8.i64");
    Value *TySize = ConstantInt::get(Type::getInt64Ty(Context), 0);
    return Builder.CreateCall(memcpyFunc, {Ptr, Val, TySize, ConstantInt::getFalse(Context)});
}


Value *IRCodegenVisitor::getTypeSize(Type *Ty) {
    return ConstantInt::get(Type::getInt64Ty(Context), TheModule.getDataLayout().getTypeAllocSize(Ty));
}

Value *IRCodegenVisitor::getTypeSizeInBit(Type *Ty) {
    return ConstantInt::get(Type::getInt64Ty(Context), TheModule.getDataLayout().getTypeAllocSizeInBits(Ty));
}

}
