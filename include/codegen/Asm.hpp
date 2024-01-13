#pragma once
#include"llvm/IR/Module.h"

namespace codegen{
    using namespace llvm;
    void LLVMIRToAsm(Module &TheModule, std::string sourcePath);
}