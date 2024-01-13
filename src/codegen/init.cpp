#include<llvm/IR/Module.h>
#include<llvm/IR/Verifier.h>
#include"../include/codegen/LLVMCodeGen.hpp"
#include"../include/codegen/Asm.hpp"
#include"../include/utils/File.hpp"
#include"../include/Module.hpp"
#include"../include/Context.hpp"
#include"llvm/Linker/Linker.h"

namespace codegen{
static bool codegenS(ast::Module *M, codegen::IRCodegenVisitor &CodeGen) {
    for(auto &SM: M->getSubMods()) {
        if(!codegenS(SM.second, CodeGen)) {
            return false;
        }
    }
    if(!CodeGen.codeGen(M->getAst())) {
        return false;
    }
    return true;
}


bool InitCodegen(ast::Module *M) {
   llvm::LLVMContext Context;
   llvm::IRBuilder<> Builder(Context);
   llvm::Module TheModule("main", Context);
   codegen::IRCodegenVisitor CodeGen(Context, TheModule, Builder);
   if(!codegenS(M, CodeGen)) {
        return false;
   }
      llvm::verifyModule(TheModule);

   std::error_code err;
   llvm::raw_fd_ostream OS("../test/func.ir", err);
   if(err)
      std::cerr<<"error : unable to convert to ir"<<std::endl;

   TheModule.dump();
   codegen::LLVMIRToAsm(TheModule, M->getPath());
   TheModule.dump();
   return true;
}

}
