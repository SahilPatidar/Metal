#include "../../include/codegen/Asm.hpp"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/Host.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRPrintingPasses.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/Support/raw_ostream.h"


#include "llvm/IR/Value.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"


#include<iostream>




namespace codegen {
using namespace llvm;
void runOptimisingPasses(Module &TheModule) {
  std::unique_ptr<llvm::legacy::FunctionPassManager> functionPassManager =
      std::make_unique<llvm::legacy::FunctionPassManager>(&TheModule);

  // Promote allocas to registers.
  functionPassManager->add(llvm::createPromoteMemoryToRegisterPass());
  // Do simple "peephole" optimizations
  functionPassManager->add(llvm::createInstructionCombiningPass());
  // Reassociate expressions.
  functionPassManager->add(llvm::createReassociatePass());
  // Eliminate Common SubExpressions.
  functionPassManager->add(llvm::createGVNPass());
  // Simplify the control flow graph (deleting unreachable blocks etc).
  functionPassManager->add(llvm::createCFGSimplificationPass());

  functionPassManager->doInitialization();

  for (auto &function : TheModule) {
    // llvm::Function *llvmFun =
        // TheModule.getFunction(llvm::StringRef(function->functionName));
    functionPassManager->run(function);
  }


  llvm::Function *llvmMainFun = TheModule.getFunction(llvm::StringRef("main"));
  functionPassManager->run(*llvmMainFun);
}
void LLVMIRToAsm(Module &TheModule) {
  runOptimisingPasses(TheModule);
    InitializeAllTargetInfos();
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmParsers();
  InitializeAllAsmPrinters();

  auto TargetTriple = sys::getDefaultTargetTriple();
  TheModule.setTargetTriple(TargetTriple);

  std::string Error;
  std::cout<<TargetTriple<<std::endl;
  auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

  // Print an error and exit if we couldn't find the requested target.
  // This generally occurs if we've forgotten to initialise the
  // TargetRegistry or we have a bogus target triple.
  if (!Target) {
    errs() << Error;
    exit(1);
  }

  auto CPU = "generic";
  auto Features = "";

  TargetOptions opt;
  auto RM = std::optional<Reloc::Model>();
  auto TheTargetMachine =
      Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

  TheModule.setDataLayout(TheTargetMachine->createDataLayout());

  auto Filename = "../test/func.asm";
  std::error_code EC;
  raw_fd_ostream dest(Filename, EC, sys::fs::OF_None);

  if (EC) {
    errs() << "Could not open file: " << EC.message();
    return;
  }

  legacy::PassManager pass;

  if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, llvm::CodeGenFileType::AssemblyFile)) {
    errs() << "TheTargetMachine can't emit a file of this type";
    return;
  }

  pass.run(TheModule);
  dest.flush();

  outs() << "Wrote " << Filename << "\n";
}

} // namespace codegen
