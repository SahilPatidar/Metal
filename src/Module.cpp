#include"../include/Module.hpp"
#include"../include/Builder.hpp"
#include"../include/lex/lex.hpp"
#include"analyzer/Resolve.hpp"
#include"analyzer/Sema.hpp"
#include"../include/parser/Parser.hpp"
#include"../include/utils/File.hpp"

namespace ast{
   

Module::~Module() { }


void Module::printAsT() {
    if(AsT)
        std::cout<<AsT->toString()<<std::endl;
}


bool CreateModInfoByMod(std::string &path, const std::string &modname, ModuleInfo &ModInfo) {
    std::string src = "";
    std::string dir = path;
    std::string absp = path;
    if(!fs::get_sub_mod_src(path, modname, src, dir, absp)){
        return false;
    }

    ModInfo = (ModuleInfo){absp, dir, src, modname};
    return true;
}

bool CreateModInfoByAbsPath(std::string &path, ModuleInfo &ModInfo) {
    std::string src = "";
    std::string dir = path;
    std::string absp = path;
    std::string modname = "";
    if(!fs::get_root_mod_src(path, src, dir, modname)){
        return false;
    }

    ModInfo = (ModuleInfo){absp,dir,src, modname};
    return true;
}


/////////////////////////////////// ModuleHelper ///////////////////////////////////////////////////////

ModuleHelper::~ModuleHelper() {}


bool ModuleHelper::LexSrc(Context &mgr) {
    Lexer L(mgr, Mod, Mod->ModInfo.src, Mod->LXMs);
    int i = Mod->ModInfo.src.size();
    if(!L.Tokenize()){
        std::cout<<"failed to tokenize"<<std::endl;
        return false;
    }
    return true;
}

bool ModuleHelper::ParseToken(Context &mgr) {
    parser::Parser p(mgr, Mod);
    if(!p.parse(Mod->AsT)){
        std::cout<<"failed to parse"<<std::endl;
        return false;
    }
    return true;
}


bool ModuleHelper::ResolveAst(Context &mgr, Module *RMod) {
    Resolve R(mgr, RMod);
    for(auto &m: Mod->SubMods){
        ModuleHelper MH(m.second);
        if(!MH.ResolveAst(mgr, RMod)) {
            return false;
        }
    }
    if(!R.resolve(&Mod->AsT)){
        return false;
    }
    return true;
}


bool ModuleHelper::SemaAst(Context &mgr, Module *RMod) {
    TypeChecker TyC(mgr, RMod);
    if(!TyC.Analyze(RMod->AsT)){
        return false;
    }
    return true;
}


Module *ModuleHelper::CreateMod(Context &mgr, std::string modName, Module *PMod) {
    ModuleInfo ModInfo = {};
    std::string path = PMod->getDirPath();
    if(!CreateModInfoByMod(path, modName, ModInfo)){
        return nullptr;
    }
    Module *M = mgr.CreateMod(ModInfo);
    PMod->SubMods.insert({ModInfo.modname, M});
    if(M == nullptr){
        std::cout<<"failed to build module  - "<<modName<<std::endl;;
        return nullptr;
    }
    return M;
    }

}