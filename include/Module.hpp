#pragma once
#include<iostream>
#include<map>
#include<stack>
#include"lex/lex.hpp"
#include"Context.hpp"
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

struct ModuleInfo{
    String path;
    String dirpath;
    String src;
    String modname;
};


class Module{
private:
    Map<String, Module* >SubMods;    
    ModuleInfo ModInfo;
    Vec<Lexeme>LXMs;
    Ast *AsT;
    Map<String, Ast **>ModItems;
    friend class ModuleHelper;
public:
    Module(const ModuleInfo _ModInfo)
    : ModInfo(_ModInfo){
        AsT = nullptr;
    }
    
    ~Module();

    inline const Vec<Lexeme> &getLexeme() const noexcept { return LXMs; }
    inline const Map<String, Module*> &getSubMods() const { return SubMods; }
    inline Module* getSubMod(const String &s) {
        return SubMods.find(s) == SubMods.end()? nullptr: SubMods[s];
    }
    /// module info
    inline String getDirPath() const { return ModInfo.dirpath; }
    inline String getPath() const { return ModInfo.path; }
    inline String getSrc() const { return ModInfo.src; }

    inline Ast *getAst() const { return AsT; }

    inline String getModId() const { return ModInfo.modname; }

    inline Ast **getModItemss(const String &s) {
        return ModItems.find(s) == ModItems.end()? nullptr:ModItems[s];
    }

    inline void insertModItem(String S, Ast **_Stmt) {
        if(ModItems.find(S) != ModItems.end()) {
            return;
        }
        ModItems.insert({S, _Stmt});
    }

    inline bool HasStmt(const String &S) noexcept { return ModItems.find(S) != ModItems.end(); }

    inline const Map<String, Ast **> &getModItemss() const noexcept { return ModItems; }
    void printAsT();
};  


bool CreateModInfoByMod(String &path, const String &modname, ModuleInfo &ModInfo);
bool CreateModInfoByAbsPath(String &path, ModuleInfo &ModInfo);

class ModuleHelper{
public:
    ModuleHelper(Module *_Mod)
    :Mod(_Mod) {}

    ~ModuleHelper();

    bool LexSrc(Context &mgr); 
    bool ParseToken(Context &mgr);
    bool ResolveAst(Context &mgr, Module *RMod);
    bool SemaAst(Context &mgr, Module *RMod);
    static Module *CreateMod(Context &mgr, String modName, Module *PMod);

private:
    Module *Mod;
};

}
