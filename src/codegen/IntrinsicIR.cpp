#include"../../include/codegen/LLVMCodeGen.hpp"
#include<llvm/IR/ConstantFold.h>
#include<llvm/IR/Constant.h>
#include<llvm/IR/DerivedTypes.h>
#include<llvm/IR/BasicBlock.h>
#include<llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include"../../include/Error.hpp"
#include<iostream>
#include<stdlib.h>
#include "llvm/IR/Intrinsics.h"


namespace codegen{

Value *IRCodegenVisitor::codeGenPrintf(ast::FieldExpr *ArgF) {
  dumpir1(__func__);
  std::vector<ast::Ast *>args = ArgF->getArgs();
  llvm::Function *printf = TheModule.getFunction("printf");
  std::vector<llvm::Value *> printfArgs;
  std::cout<<static_cast<ast::StringLiteral *>(args[0])->getLexeme().getStr().c_str()<<std::endl;
  printfArgs.push_back(Builder.CreateGlobalStringPtr(static_cast<ast::StringLiteral *>(args[0])->getLexeme().getStr().c_str()));
  if(args.size() > 1)
    for (size_t i = 1, size = args.size(); i < size; i++) {
      llvm::Value *argVal = codeGenStmt(args[i]);
      if (argVal == nullptr) {
        err::err_out(args[i], "unable to convert printf to ir");
        return nullptr;
      }

        Type *VTy =  getType(argVal, args[i]);
        if(VTy->isArrayTy()) {
          Type *I64 = Type::getInt64Ty(Context);
          argVal = Builder.CreateInBoundsGEP(VTy, argVal, {ConstantInt::get(I64, 0), ConstantInt::get(I64, 0)});
        }else
          argVal = LoadValue(args[i], argVal, getType(argVal, args[i]));

      printfArgs.push_back(argVal);
    }

  dumpir2(__func__);
  return Builder.CreateCall(printf, printfArgs);
}

Value *IRCodegenVisitor::codeGenScanf(ast::FieldExpr *ArgF) {
  dumpir1(__func__);
  std::vector<ast::Ast *>args = ArgF->getArgs();
  llvm::Function *scanf = TheModule.getFunction("scanf");
  std::vector<llvm::Value *> scanfArgs;
  std::cout<<static_cast<ast::StringLiteral *>(args[0])->getLexeme().getStr().c_str()<<std::endl;
  scanfArgs.push_back(Builder.CreateGlobalStringPtr(static_cast<ast::StringLiteral *>(args[0])->getLexeme().getStr().c_str()));
  if(args.size() > 1)
    for (size_t i = 1, size = args.size(); i < size; i++) {
      llvm::Value *argVal = codeGenStmt(args[i]);
      if (argVal == nullptr) {
        err::err_out(args[i], "unable to convert printf to ir");
        return nullptr;
      }

      scanfArgs.push_back(argVal);
    }
  dumpir2(__func__);
  return Builder.CreateCall(scanf, scanfArgs);
}

Value *IRCodegenVisitor::codeGenMalloc(ast::FieldExpr *ArgF) {
  dumpir1(__func__);
  std::vector<ast::Ast *>args = ArgF->getArgs();
  llvm::Function *malloc = TheModule.getFunction("malloc");
  llvm::Value *argVal = codeGenStmt(args[0]);
  if(!argVal) {
    err::err_out(args[0], "unable to convert free function call to ir");
      return nullptr;
  }
  dumpir2(__func__);
  return Builder.CreateCall(malloc, {argVal});
}

Value *IRCodegenVisitor::codeGenFree(ast::FieldExpr *ArgF) {
  dumpir1(__func__);
  std::vector<ast::Ast *>args = ArgF->getArgs();
  llvm::Function *free = TheModule.getFunction("free");
  llvm::Value *argVal = codeGenStmt(args[0]);
  if(!argVal) {
    err::err_out(args[0], "unable to convert free function call to ir");
      return nullptr;
  }
  dumpir2(__func__);
  return Builder.CreateCall(free, {argVal});
}


void IRCodegenVisitor::IntrinsicFnCodegen() {
    // void ptr
    // Type *VoidPtr = Builder.getInt8PtrTy();

    // /// scanf
    // FunctionType *scanfType = FunctionType::get(Builder.getInt32Ty(), {Builder.getInt8Ty()->getPointerTo()}, true);
    // Function *scanfFunc = Function::Create(scanfType, Function::ExternalLinkage, "scanf", TheModule);
    // scanfFunc->setCallingConv(CallingConv::C);
    
    // /// printf
    // FunctionType *printfType = FunctionType::get(Builder.getInt32Ty(), llvm::Type::getInt8Ty(Context)->getPointerTo(), true);
    // Function *printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", TheModule);
    // printfFunc->setCallingConv(CallingConv::C);

    // /// malloc
    // FunctionType *mallocType = FunctionType::get(VoidPtr, {Builder.getInt64Ty()}, false);
    // Function *mallocFunc = Function::Create(mallocType, Function::ExternalLinkage, "malloc", TheModule);
    // // Function *mallocFunc = Function::Create(mallocType, Function::ExternalLinkage, "malloc", TheModule);
    // mallocFunc->setCallingConv(CallingConv::C);

    // /// memcpy
    // FunctionType *memcpyType = FunctionType::get(Type::getVoidTy(Context), {VoidPtr, VoidPtr, Builder.getInt64Ty(), Type::getInt1Ty(Context)}, false);
    // Function *memcpyFunc = Function::Create(memcpyType, Function::ExternalLinkage, "llvm.memcpy.p0i8.p0i8.i64", TheModule);
    // memcpyFunc->setCallingConv(CallingConv::C);

    // /// free
    // FunctionType *freefnType = FunctionType::get(Builder.getVoidTy(), {VoidPtr}, false);
    // Function *freeFunc = Function::Create(freefnType, Function::ExternalLinkage, "free", TheModule);
    // freeFunc->setCallingConv(CallingConv::C);
}

}