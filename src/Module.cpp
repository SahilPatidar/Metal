#include"../include/Module.hpp"
#include"../include/Builder.hpp"
#include"../include/lex/lex.hpp"
#include"analyzer/Resolve.hpp"
#include"analyzer/Sema.hpp"
#include"../include/parser/Parser.hpp"
#include"../include/utils/File.hpp"

namespace ast{
   

Module::~Module() { }


void Module::printTree() {
    if(tree)
        std::cout<<tree->toString()<<std::endl;
}


bool CreateModInfoByMod(std::string &path, const std::string &modname, ModuleInfo &modinfo) {
    std::string src = "";
    std::string dir = path;
    std::string absp = path;
    if(!fs::get_sub_mod_src(path, modname, src, dir, absp)){
        return false;
    }

    modinfo = (ModuleInfo){absp, dir, src, modname};
    return true;
}

bool CreateModInfoByAbsPath(std::string &path, ModuleInfo &modinfo) {
    std::string src = "";
    std::string dir = path;
    std::string absp = path;
    std::string modname = "";
    if(!fs::get_root_mod_src(path, src, dir, modname)){
        return false;
    }

    modinfo = (ModuleInfo){absp,dir,src, modname};
    return true;
}


/////////////////////////////////// ModuleHelper ///////////////////////////////////////////////////////

ModuleHelper::~ModuleHelper() {}


bool ModuleHelper::LexSrc(ResourceMgr &mgr) {
    lex::Lexer L(mgr, Mod);
    int i = Mod->modinfo.src.size();
    if(!L.tokenizer(Mod->modinfo.src, Mod->lexeme, 0, i)){
        std::cout<<"faild to tokenize"<<std::endl;
        return false;
    }
    return true;
}

bool ModuleHelper::ParseToken(ResourceMgr &mgr) {
    parser::Parser p(mgr, Mod);
    if(!p.parse(Mod->tree)){
        std::cout<<"faild to parse"<<std::endl;
        return false;
    }
    return true;
}


bool ModuleHelper::ResolveAst(ResourceMgr &mgr, Module *RMod) {
    Resolve R(mgr, RMod);
    for(auto &m: Mod->submods){
        ModuleHelper MH(m.second);
        if(!MH.ResolveAst(mgr, RMod)) {
            return false;
        }
    }
    if(!R.resolve(&Mod->tree)){
        return false;
    }
    return true;
}


bool ModuleHelper::SemaAst(ResourceMgr &mgr, Module *RMod) {
    TypeChecker TyC(mgr, RMod);
    // for(auto &m: Mod->submods){
    //     ModuleHelper MH(m.second);
    //     if(!MH.SemaAst(mgr, RMod)) {
    //         return false;
    //     }
    // }
    if(!TyC.Analyze(RMod->tree)){
        return false;
    }
    return true;
}


Module *ModuleHelper::CreateMod(ResourceMgr &mgr, std::string modName, Module *PMod) {
    ModuleInfo modinfo = {};
    std::string path = PMod->getDirPath();
    if(!CreateModInfoByMod(path, modName, modinfo)){
        return nullptr;
    }
    Module * M = mgr.CreateMod(modinfo);
    PMod->submods.insert({modinfo.modname, M});
    if(M == nullptr){
        std::cout<<"failed to build mod  - "<<modName<<std::endl;;
        return nullptr;
    }
    return M;
    }

}