#include"../../include/codegen/LLVMCodeGen.hpp"
#include<llvm/IR/DerivedTypes.h>
#include<llvm/IR/BasicBlock.h>
#include<llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include "llvm/IR/Verifier.h"
#include"../../include/Error.hpp"
#include"../../include/parser/type.hpp"
#include<iostream>
#include<stdlib.h>

namespace codegen{
AllocaInst *IRCodegenVisitor::CreateEntryBlockAlloca(Function *TheFunction,
                                          Argument &Arg) {
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                   TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(Arg.getType(), nullptr, Arg.getName());
}
AllocaInst *IRCodegenVisitor::CreateEntryBlockAlloca(Function *TheFunction,
                                          Type *Ty) {
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                   TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(Ty);
}

FunctionType *IRCodegenVisitor::codegenFunctionType(ast::FunctionProto &FunctionProto) {
    Type *RetType = nullptr;
    ast::Ast *Ret = FunctionProto.getResultType();
    if(Ret && !Ret->Is(ast::NodeVoid))
        RetType = codeGenTy(Ret);
    else
        RetType = Type::getVoidTy(Context);
    if(!RetType) {
        err::err_out(&FunctionProto, "unable convert to IR");
        return nullptr;
    }
 
    std::vector<Type *> ParamTy;
    std::vector<ast::VarStmt *> &Param = FunctionProto.getParameter();
    bool isVararg = false;
    if(FunctionProto.isVariadic()) {
        isVararg = true;
    }
    for(size_t i = 0, siz = Param.size(); i < siz; i++) {
        ast::VarStmt *FieldVar = Param[i];
        ParamTy.push_back(codeGenTy(FieldVar->getType()));
        
        if(!ParamTy.back()) {
            return nullptr;
        }
    }
    return FunctionType::get(RetType, ParamTy, isVararg);
}


Value *IRCodegenVisitor::codeGenFunctionDef(ast::FunctionDef *FuncStmt) {
    dumpir1("FunctionDef");
    ResMgr.Push_Func();
    std::vector<Type *> ParamTy;
    ast::FunctionProto *FnProto = FuncStmt->getFnProto();
    std::string FuncN = FnProto->getFuncName().getStr();
    std::vector<ast::VarStmt *> &Param = FnProto->getParameter();
    Function *Func = TheModule.getFunction(FuncN);
    if(!Func) {
        FunctionType *FuncTy = codegenFunctionType(*FnProto);
        Func = Function::Create(FuncTy, FnProto->IsMemberFunc()?Function::LinkOnceODRLinkage :Function::ExternalLinkage, (Twine)FuncN, &TheModule);
    }
    // FunctionType *FuncTy = codegenFunctionType(*FnProto);
    // Function *Func = Function::Create(FuncTy, FnProto->IsMemberFunc()?Function::LinkOnceODRLinkage :Function::ExternalLinkage, (Twine)FuncN, &TheModule);
    ResMgr.addInfo(FuncN, Func, true);
    if(Param.size() != Func->arg_size()) {
        err::err_out(FuncStmt, "unable convert to IR");
        return nullptr;
    }
    Function::arg_iterator Arg = Func->arg_begin();
    size_t i = 0;
    BasicBlock *EntryBlock = BasicBlock::Create(Context, "entry", Func);
    Builder.SetInsertPoint(EntryBlock);

    for(auto &Arg: Func->args()) {
        Arg.setName(Param[i]->getVar().getStr());
        AllocaInst *V = CreateEntryBlockAlloca(Func, Arg);
        if(!V){
            err::err_out(FuncStmt, "unable convert to IR");
            return nullptr;
        }
        Builder.CreateStore(&Arg, V);
        ResMgr.addInfo(Param[i]->getVar().getStr(), V);
        i++;
    }

    std::vector<ast::Ast *>&Stmts = FuncStmt->getFuncBlock()->getStmts();
    int s = Stmts.size();

    for(auto &S :Stmts) {
        if(!codeGenStmt(S)) {
            return nullptr;
        }
    }

    if(s == 0 || (s != 0 && !Stmts[s-1]->Is(ast::NodeRetStm))) {
        Builder.CreateRetVoid();
    }

    ResMgr.Pop_Func();
    dumpir2(__func__);
    return Func;
}

Value *IRCodegenVisitor::codeGenFnProto(ast::FunctionProto *FnProto) {
    dumpir1("codeGenFnProto");
    std::string FN = FnProto->getFuncName().getStr();
    if(ResMgr.Has(FN)) {
        return ResMgr.getInfo(FN);
    }
    FunctionType *FnTy = codegenFunctionType(*FnProto);
    Function *Fn = Function::Create(FnTy, FnProto->IsMemberFunc()?Function::LinkOnceODRLinkage :Function::ExternalLinkage, FnProto->getFuncName().getStr(), &TheModule);
    if(FnProto->isExtern())
        Fn->setCallingConv(CallingConv::C);
    ResMgr.addInfo(FnProto->getFuncName().getStr(), Fn, true);
    dumpir2("codeGenFnProto");
    return Fn;
}

}