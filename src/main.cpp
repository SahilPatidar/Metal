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
#include"../include/Context.hpp"

using namespace ast;


int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("too few args");
        return EXIT_FAILURE;
    }

   std::string filePath = argv[1];
   ModuleInfo modinfo = {};
   if(!CreateModInfoByAbsPath(filePath, modinfo)){
      return 0;
   }
   Context Mgr;
   Module *M = Mgr.CreateMod(modinfo);
   ModuleHelper MH(M);

   if(!MH.LexSrc(Mgr)){
      return 1;
   }

   if(!MH.ParseToken(Mgr)){
      return 1;
   }

   if(!MH.ResolveAst(Mgr, M)) {
      return 1;
   }
   if(!MH.SemaAst(Mgr, M)){
      return 1;
   }

   if(!codegen::InitCodegen(M)){
      return 1;
   }

   std::string Filename = "out.asm";
  size_t lastSlashPos = filePath.find_last_of("/\\");
  std::string outFile = "";
  if (lastSlashPos != std::string::npos) 
      outFile = filePath.substr(0, lastSlashPos) + "/out";

  std::string clangCommand = "clang -o " + outFile + " " + Filename;
  FILE *pipe = popen(clangCommand.c_str(), "r");
  if (!pipe) {
      std::cerr << "Error executing clang." << std::endl;
      return 1;
  }

  std::array<char, 256> buffer;
  std::string result;
  while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
      result += buffer.data();
  }

  int clangResult = pclose(pipe);

//   if (clangResult == 0) {
      // Remove the assembly file
//       if (std::remove(Filename) == 0) {
//           std::cout << "Assembly file removed successfully." << std::endl;
//       } else {
//           std::cerr << "Error removing assembly file." << std::endl;
//       }
//   } else {
//       std::cerr << "Error executing clang. Return code: " << clangResult << "\nOutput:\n" << result << std::endl;
//   }
   return 0;
}