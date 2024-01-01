#include"../../include/codegen/LLVMCodeGen.hpp"
#include<llvm/IR/DerivedTypes.h>
#include<llvm/IR/BasicBlock.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include"../../include/Error.hpp"
#include"../../include/parser/type.hpp"
#include<iostream>
#include<stdlib.h>

namespace codegen{

Value *IRCodegenVisitor::codeGenNewStmt(ast::NewStmt *AstNode) {
    dumpir1(__func__);

    // llvm::Function *malloc = TheModule.getFunction("malloc");
    llvm::Function *malloc = TheModule.getFunction("malloc");
    if(!malloc) {
        Type *VoidPtr = Builder.getInt8PtrTy();
        FunctionType *mallocType = FunctionType::get(VoidPtr, {Builder.getInt64Ty()}, false);
        malloc = Function::Create(mallocType, Function::ExternalLinkage, "malloc", &TheModule);
        malloc->setCallingConv(CallingConv::C);
        ResMgr.addInfo("malloc", malloc);
    }
    Type *Ty = codeGenTy(AstNode->getTy());
    if(!Ty) {
        err::err_out(AstNode->getTy(), "unable to convert type to ir");
        return nullptr;
    }
    Value *TySize = getTypeSize(Ty);
    if(!TySize){
        err::err_out(AstNode->getSize(), "unable to get size of type");
        return nullptr;
    }

    llvm::Value *Size = codeGenStmt(AstNode->getSize());
    if(!Size) {
        err::err_out(AstNode->getSize(), "unable to convert free function call to ir");
        return nullptr;
    }
    if(!Size->getType()->isIntegerTy()) {
        Size = Builder.CreateLoad(getType(Size, AstNode->getSize()), Size);
    }

    if(!Size->getType()->isIntegerTy(64)) {
        Size = Builder.CreateSExt(Size, Type::getInt64Ty(Context));
    }

    dumpir2(__func__);
    return Builder.CreateCall(malloc, {Builder.CreateMul(TySize, Size)});
}

Value *IRCodegenVisitor::codeGenDelStmt(ast::DelStmt *AstNode) {
    dumpir1(__func__);
    ast::Ast *VPtr = AstNode->getPtr();
    llvm::Function *free = TheModule.getFunction("free");
    if(!free) {
        Type *VoidPtr = Builder.getInt8PtrTy();
        FunctionType *freefnType = FunctionType::get(Builder.getVoidTy(), {VoidPtr}, false);
        free = Function::Create(freefnType, Function::ExternalLinkage, "free", TheModule);
        free->setCallingConv(CallingConv::C);
        ResMgr.addInfo("free", free);
    }
    llvm::Value *argVal = codeGenStmt(VPtr);
    if(!argVal) {
        err::err_out(VPtr, "unable to convert free function call to ir");
        return nullptr;
    }

    argVal = Builder.CreateLoad(argVal->getType(), argVal);
    dumpir2(__func__);
    return Builder.CreateCall(free, {argVal});
}


Value *IRCodegenVisitor::codeGenBlockStmt(ast::BlockStmt *AstNode, BasicBlock *BB) {
    dumpir1("BlockStmt");
    std::vector<ast::Ast *>Stmts = AstNode->getStmts();
    if(Stmts.empty()) {
        if(BB) {
            return Builder.CreateBr(BB);
        }
        return Constant::getNullValue(Type::getInt32Ty(Context));
    }
    bool HasBranchOrRet = false;
    Value *SVal = nullptr;
    for(auto &S :Stmts) {
        SVal = codeGenStmt(S);
        if(!SVal) {
            return nullptr;
        }
        if(S->Is(ast::NodeBranchStm) || S->Is(ast::NodeRetStm)) {
            HasBranchOrRet = true;
            break;
        }
    }
    // if any branch and ret inst between no need to insert br inst
    if(!HasBranchOrRet && BB) {
        return Builder.CreateBr(BB);
    }
    dumpir2("BlockStmt");
    return SVal;
}

Value *IRCodegenVisitor::codeGenVarStmt(ast::VarStmt *AstNode) {
    dumpir1("VarStmt");
    ast::Ast *StmtVal = AstNode->getVal();
    std::string VarN = AstNode->getVar().getStr();
    Type *Ty = nullptr;
    Value *Val = nullptr;
    AllocaInst *Var = nullptr;
    ast::Ast *StmtTy = AstNode->getType();

    if(StmtTy) {
        Ty = codeGenTy(StmtTy);
    }else {
        Ty = getTypeUsingStmtTypeInfo(AstNode->getTypeInfo());
    }

    if(!Ty) {
        err::err_out(AstNode, "unable to contvert var stmt type to ir");
        return nullptr;
    }

    if(AstNode->IsGlobVar()) {
        isConstF = true;
        Constant *V = nullptr;
        if(StmtVal) {
            V = codeGenConst(StmtVal);
            if(!V) {
                err::err_out(AstNode, "unable to contvert var stmt val to ir");
                return nullptr;
            }
        }

        GlobalVariable *GVR = new GlobalVariable(
                                    TheModule, 
                                    Ty, 
                                    !AstNode->HasMut(), 
                                    GlobalValue::ExternalLinkage, 
                                    V, 
                                    VarN);
        ResMgr.addInfo(VarN, GVR, true);               
        isConstF = false;
        return GVR;
    }

    Var = CreateEntryBlockAlloca(Builder.GetInsertBlock()->getParent(), Ty);
    if(!Var){
        err::err_out(AstNode, "unable to contvert var stmt to ir");
        return nullptr;
    }
    if(StmtVal) {
        Val = codeGenStmt(StmtVal, Var);
        if(!Val) {
            err::err_out(AstNode, "unable to contvert var stmt val to ir");
            return nullptr;
        }
    }
   
    ResMgr.addInfo(VarN, Var, !ResMgr.HasFunc());
    if(StmtVal && (Var != Val))
        return StoreValue(LoadValue(StmtVal, Val, Ty), Var, Ty, getType(Val, StmtVal));
    // if(StmtVal && !StmtVal->Is(ast::NodeField) && !(StmtVal->Is(ast::NodeExpr) && static_cast<ast::Expression *>(StmtVal)->ExprTy() == ast::KStructExpr))
    //     return StoreValue(LoadValue(StmtVal, Val, Ty), Var, Ty, getType(Val, StmtVal));
    dumpir2(__func__);
    return Var;
}


Value *IRCodegenVisitor::codeGenStructStmt(ast::StructStmt *AstNode) {
    dumpir1("StructStmt");
    std::string SName = AstNode->getName().getStr();
    StructType *StTy = StructType::create(Context, StringRef(SName));
    if(!StTy) {
        err::err_out(AstNode, "unable convert to IR");
        return nullptr;
    }
    std::vector<Type *>ele;
    NamedTypes[SName] = StTy;
    
    TypeMap.insert({AstNode->getTypeInfo()->getuId(), StTy});

    std::vector<ast::VarStmt*>&FieldVars = AstNode->getfield();
    for(size_t i = 0, siz = FieldVars.size(); i < siz; i++) {
        ast::VarStmt *FieldVar = FieldVars[i];
        ast::Ast *Ty = FieldVar->getType();
        ele.push_back(codeGenTy(Ty));
        if(!ele.back()) {
            return nullptr;
        }
    }
    if(!ele.empty())
        StTy->setBody(ele);
    return Constant::getNullValue(Type::getInt32Ty(Context));
}

Value *IRCodegenVisitor::codeGenReturnStmt(ast::ReturnStmt *AstNode) {
    dumpir1("ReturnStmt");
    if(AstNode->getRetValue()){
        Value *RetVal = codeGenStmt(AstNode->getRetValue());
        if(!RetVal) {
            err::err_out(AstNode, "unable convert return value to IR");
            return nullptr;
        }
        return Builder.CreateRet(LoadValue(AstNode->getRetValue(), RetVal, Builder.GetInsertBlock()->getParent()->getReturnType()));
    }
    return Builder.CreateRetVoid();
}


Value *IRCodegenVisitor::codeGenBranchStmt(ast::BranchStmt *AstNode) {
    dumpir1("BranchStmt");
    if(AstNode->getLexeme().getTokTy() == lex::BREAK)
        return Builder.CreateBr(LoopEnd.back());
    return Builder.CreateBr(LoopBagin.back());
}


Value *IRCodegenVisitor::codegenCondExpr(ast::Ast *Expr, BasicBlock *BB1, BasicBlock *BB2) {
    putTrueBB(BB1);
    putFalseBB(BB2);
    Value *Cond = codeGenStmt(Expr);
    dropFalseBB();
    dropTrueBB();
    if(!Cond) {
        err::err_out(Expr, "failed to convert conditional expression to IR");
        return nullptr;
    }
    if(Cond->getValueID() == 30) {
        return Cond;
    }
    Cond = LoadValue(Expr, Cond, Type::getInt1Ty(Context));
    
    Builder.CreateCondBr(Cond, BB1, BB2);
    return Cond;
}


Value *IRCodegenVisitor::codeGenIfStmt(ast::IfStmt *AstNode) {
    dumpir1("IfStmt");
    ResMgr.Push_Stack();
    ast::Ast *CondV = AstNode->getCondV();
    ast::Ast *&ElBlk = AstNode->getElBlock();

    Function *TheFunction = Builder.GetInsertBlock()->getParent();

    BasicBlock *TrueBlock = BasicBlock::Create(Context, "if");
    BasicBlock *FalseBlock = BasicBlock::Create(Context, "else");
    BasicBlock *EndBlock = BasicBlock::Create(Context, "end");

    Value *Cond = nullptr;
    if(ElBlk) 
        Cond = codegenCondExpr(CondV, TrueBlock, FalseBlock);
    else
        Cond = codegenCondExpr(CondV, TrueBlock, EndBlock);

    if(!Cond) {
        return nullptr;
    }


    TheFunction->insert(TheFunction->end(), TrueBlock);
    Builder.SetInsertPoint(TrueBlock);
    
    Value *ThenVal = codeGenBlockStmt(AstNode->getIfBlock(), EndBlock);
    if(!ThenVal) {
        err::err_out(AstNode, "unable convert then val to IR");
        return nullptr;
    }


    TrueBlock = Builder.GetInsertBlock();
    Value *ElseVal = nullptr;
    if(ElBlk) {
        TheFunction->insert(TheFunction->end(), FalseBlock);
        Builder.SetInsertPoint(FalseBlock);
        if(ElBlk->Is(ast::NodeBlockStm)) {
            ElseVal = codeGenBlockStmt(static_cast<ast::BlockStmt *>(ElBlk), EndBlock);
        }else{
            ElseVal = codeGenIfStmt(static_cast<ast::IfStmt *>(ElBlk));
            Builder.CreateBr(EndBlock);
        }
        if(!ElseVal) {
            err::err_out(AstNode, "unable convert else val to IR");
            return nullptr;
        }
        FalseBlock = Builder.GetInsertBlock();
    }

    TheFunction->insert(TheFunction->end(), EndBlock);
    Builder.SetInsertPoint(EndBlock);

    if (ThenVal->getType() == llvm::Type::getVoidTy(Context)) {
        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(Context));
    }

    if (ElseVal && (ElseVal->getType() == llvm::Type::getVoidTy(Context) ||
      (ThenVal->getType() != ElseVal->getType()))) {
        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(Context));
    }

    PHINode *PHI = Builder.CreatePHI(ThenVal->getType(), ElseVal?2:1, "iftmp");
    if(!PHI) {
        err::err_out(AstNode, "unable to convert if stmt to ir");
        return nullptr;
    }
    PHI->addIncoming(ThenVal, TrueBlock);
    if(ElseVal)
        PHI->addIncoming(ElseVal, FalseBlock);
    ResMgr.Pop_Stack();
    dumpir2(__func__);
    return PHI;
}


Value *IRCodegenVisitor::codeGenForLoop(ast::ForLoop *AstNode) {
    dumpir1("ForLoop");
    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *CondBlock = BasicBlock::Create(Context, "cond");
    BasicBlock *LoopBB = BasicBlock::Create(Context, "loopbody");
    BasicBlock *LoopEndBB = BasicBlock::Create(Context, "endloop");
    ResMgr.Push_Stack();
    if(AstNode->getVar()) {
        Value *Init = codeGenStmt(AstNode->getVar());
        if(!Init) {
            err::err_out(AstNode, "unable convert var to IR");
            return nullptr;
        }
    }
    LoopBagin.push_back(CondBlock);
    LoopEnd.push_back(LoopEndBB);
    Builder.CreateBr(CondBlock);
    TheFunction->insert(TheFunction->end(), CondBlock);
    Builder.SetInsertPoint(CondBlock);
    if(AstNode->getCond()) {
        Value *Cond = codegenCondExpr(AstNode->getCond(), LoopBB, LoopEndBB);
        if(!Cond) {
            return nullptr;
        }
    }else {
        Builder.CreateBr(LoopBB);
    }
    
    
    TheFunction->insert(TheFunction->end(), LoopBB);
    Builder.SetInsertPoint(LoopBB);

    bool HasBranchOrRet = false;
    if(!AstNode->getBlock()->getStmts().empty()) {
        for(auto &Expr: AstNode->getBlock()->getStmts()) {
            Value *Val = codeGenStmt(Expr);
            if(!Val) {
                err::err_out(AstNode, "unable convert loop body to IR");
                return nullptr;
            }
            if(Expr->Is(ast::NodeBranchStm) || Expr->Is(ast::NodeRetStm)) {
                HasBranchOrRet = true;
                break;
            }
        }
    }  
    if(AstNode->getIncr()) {
        Value *Incr = codeGenStmt(AstNode->getIncr());
        if(!Incr) {
            err::err_out(AstNode, "unable convert incr to IR");
            return nullptr;
        }
    }
    if(!HasBranchOrRet)
        Builder.CreateBr(CondBlock);
    LoopBagin.pop_back();
    LoopEnd.pop_back();
    TheFunction->insert(TheFunction->end(), LoopEndBB);
    Builder.SetInsertPoint(LoopEndBB);
    ResMgr.Pop_Stack();
    return Constant::getNullValue(Type::getInt32Ty(Context));
}

Value *IRCodegenVisitor::codeGenMethod(ast::Method *AstNode) {
    dumpir1("Method");
    ResMgr.Push_Stack();
    Type *Ty = codeGenTy(AstNode->getName());
    if(!Ty || !Ty->isStructTy()) {
        err::err_out(AstNode, "unable convert to IR");
        return nullptr;
    }
    
    StructType *STTy = static_cast<StructType *>(Ty);
    std::vector<ast::Ast*>&MT = AstNode->getImpl();
    for(auto &Impl: MT) {
        Value *FnVal = codeGenStmt(Impl);
        if(!FnVal){
            err::err_out(AstNode, "unable convert to IR");
            return nullptr;
        }
    }
    ResMgr.Pop_Stack();
    return Constant::getNullValue(Ty);
}

Value *IRCodegenVisitor::codeGenEnumExpr(ast::EnumExpr *AstNode) {
    dumpir1("EnumExpr");
    std::vector<ast::VarStmt *>&Vars = AstNode->getEVals();
    for(auto &Var :Vars) {
        std::string VarN = Var->getVar().getStr();
        Type* Ty = codeGenTy(Var->getType());
        Value *V = codeGenStmt(Var->getVal());
        if(!V) {
            err::err_out(AstNode, "unable convert to IR");
            return nullptr;
        }
        Constant * Val = static_cast<Constant *>(V);
        GlobalVariable *GVar = new GlobalVariable(
                                    TheModule, 
                                    Ty, 
                                    true, 
                                    GlobalValue::ExternalLinkage, 
                                    Val, 
                                    VarN);
        ResMgr.addInfo(VarN, V, !ResMgr.HasFunc());
    }
    return Constant::getNullValue(Type::getInt32Ty(Context));
}

Value *IRCodegenVisitor::codeGenWhileLoop(ast::WhileLoop *AstNode) {
    dumpir1("WhileLoop");
    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *CondBlock = BasicBlock::Create(Context, "cond");
    BasicBlock *LoopBlock = BasicBlock::Create(Context, "loop");
    BasicBlock *EndBlock = BasicBlock::Create(Context, "end");

    ResMgr.Push_Stack();
    ///Condition
    Builder.CreateBr(CondBlock);
    TheFunction->insert(TheFunction->end(), CondBlock);
    Builder.SetInsertPoint(CondBlock);
    
    Value *Cond = codegenCondExpr(AstNode->getCond(), LoopBlock, EndBlock);
    if(!Cond){
        return nullptr;
    }
    // Builder.CreateCondBr(Cond, LoopBlock, EndBlock);

    ///Loop block
    LoopBagin.push_back(CondBlock); 
    LoopEnd.push_back(EndBlock); 
    TheFunction->insert(TheFunction->end(), LoopBlock);
    Builder.SetInsertPoint(LoopBlock);
    // Value *blk = nullptr;             
    Value *blk = codeGenBlockStmt(AstNode->getBlock(), CondBlock);             
    // auto &Stmts = AstNode->getBlock()->getStmts();
    // for(auto &E: Stmts) {
    //     blk = codeGenStmt(E);
        if(!blk) {
            err::err_out(AstNode, "unable convert to IR");
            return nullptr;
        } 
    // }

    // LoopBlock = Builder.GetInsertBlock();
    // Builder.CreateBr(CondBlock);

    LoopBagin.pop_back(); 
    LoopEnd.pop_back(); 
    TheFunction->insert(TheFunction->end(), EndBlock);
    Builder.SetInsertPoint(EndBlock);
    ResMgr.Pop_Stack();
    return Constant::getNullValue(Type::getInt32Ty(Context));
}

}
