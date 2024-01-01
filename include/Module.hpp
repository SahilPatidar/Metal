#pragma once
#include<iostream>
#include<map>
#include<stack>
#include"lex/lex.hpp"
#include"ResMgr.hpp"
namespace ast{

/*
    lib.mt
        |           |---- mod3
        |---- mod2--|
        |           |---- mod4
        |
        |           |---- mod5
        |---- mod2--|
                    |---- mod6
                    
*/


// class Ast;
// class Ast;

struct ModuleInfo{
    std::string path;
    std::string dirpath;
    std::string src;
    std::string modname;
};


class Module{
private:
    std::map<std::string, Module* >submods;    
    ModuleInfo modinfo;
    std::vector<lex::Lexeme>lexeme;
    Ast *tree;
    std::map<std::string, Ast **>moditem;
    friend class ModuleHelper;
public:
    Module(const ModuleInfo _modinfo)
    : modinfo(_modinfo){
        tree = nullptr;
    }
    
    ~Module();

    inline const std::vector<lex::Lexeme> &getLexeme() const noexcept { return lexeme; }
    inline const std::map<std::string, Module*> &getSubMods() const { return submods; }
    inline Module* getSubMod(const std::string &s) {
        return submods.find(s) == submods.end()? 0: submods[s];
    }
    /// module info
    inline std::string getDirPath() const { return modinfo.dirpath; }
    inline std::string getPath() const { return modinfo.path; }
    inline std::string getSrc() const { return modinfo.src; }

    inline Ast *getTree() const { return tree; }

    inline std::string getModId() const { return modinfo.modname; }

    inline Ast **getModItems(const std::string &s) {
        return moditem.find(s) == moditem.end()? 0:moditem[s];
    }

    inline void insertModItem(std::string s, Ast **stmt) {
        if(moditem.find(s) != moditem.end()) {
            return;
        }
        moditem.insert({s, stmt});
    }

    inline bool HasStmt(const std::string &s) noexcept { return moditem.find(s) != moditem.end(); }

    inline const std::map<std::string, Ast **> &getModItems() const noexcept { return moditem; }
    void printTree();
};  


bool CreateModInfoByMod(std::string &path, const std::string &modname, ModuleInfo &modinfo);
bool CreateModInfoByAbsPath(std::string &path, ModuleInfo &modinfo);

class ModuleHelper{
public:
    ModuleHelper(Module *_Mod)
    :Mod(_Mod) {}

    ~ModuleHelper();

    bool LexSrc(ResourceMgr &mgr); 
    bool ParseToken(ResourceMgr &mgr);
    bool ResolveAst(ResourceMgr &mgr, Module *RMod);
    bool SemaAst(ResourceMgr &mgr, Module *RMod);
    static Module *CreateMod(ResourceMgr &mgr, std::string modName, Module *PMod);

private:
    Module *Mod;
};

}
