#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<sstream>
#include<map>
#include<filesystem>
#include<llvm/IR/Module.h>
#include<llvm/IR/Verifier.h>
#include"../include/codegen/LLVMCodeGen.hpp"
#include"../include/codegen/Asm.hpp"
#include"../include/utils/File.hpp"
#include"../include/Module.hpp"
#include"../include/ResMgr.hpp"


using namespace ast;


int main(int argc, char *argv[]){
    if(argc < 1){
        printf("too few args");
        return EXIT_FAILURE;
    }
   // std::string path = "../test/HeapSort.mt";
   // std::string path = "../test/String.mt";
   // std::string path = "../test/Tri.mt";
   // std::string path = "../test/Enum.mt";
   // std::string path = "../test/t2.mt";
   // std::string path = "../test/array.mt";
   // std::string path = "../test/RedBlackTree.mt";
   // std::string path = "../test/tbttest.mt";
   // std::string path = "../test/Struct.mt";
   // std::string path = "../test/Graph.mt";
   // std::string path = "../test/Queue.mt";
   // std::string path = "../test/BinarySearchTree.mt";
   std::string path = argv[1];
   ModuleInfo modinfo = {};
   if(!CreateModInfoByAbsPath(path, modinfo)){
      std::cout<<"unable to build modinfo"<<std::endl;
      return 0;
   }
   ResourceMgr Mgr;
   Module *M = Mgr.CreateMod(modinfo);
   ModuleHelper MH(M);
   // if(!M->LexSrc()||!M->ParseToken()){
   //    std::cout<<"unable to build mod"<<std::endl;
   //    return 0;
   // }

   if(!MH.LexSrc(Mgr)){
      std::cout<<"unable to build lex of mod"<<std::endl;
      return 1;
   }

   if(!MH.ParseToken(Mgr)){
      std::cout<<"unable to build parse tree of mod"<<std::endl;
      return 1;
   }

   M->printTree();
   if(!MH.ResolveAst(Mgr, M)) {
      std::cout<<"unable resolve"<<std::endl;
      return 1;
   }
   if(!MH.SemaAst(Mgr, M)){
      std::cout<<"unable analyze"<<std::endl;
      return 1;
   }

   if(!codegen::InitCodegen(M)){
      return 1;
   }
   // llvm::LLVMContext Context;
   // llvm::IRBuilder<> Builder(Context);
   // llvm::Module TheModule("main", Context);
   // codegen::IRCodegenVisitor CodeGen(Context, TheModule, Builder);
   // if(!CodeGen.codeGen(M->getTree())) {
   //    return 1;
   // }
   //    llvm::verifyModule(TheModule);

   // std::error_code err;
   // llvm::raw_fd_ostream OS("../test/func.ir", err);
   // if(err)
   //    std::cerr<<"error : unable to convert to ir"<<std::endl;

   // TheModule.dump();
   // codegen::LLVMIRToAsm(TheModule);
   // TheModule.dump();

   return 0;
}