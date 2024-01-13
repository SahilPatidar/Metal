#include"../include/Context.hpp"
#include"../include/parser/type.hpp"
#include"../include/analyzer/Value.hpp"
#include"../include/parser/Ast.hpp"
#include"../include/Module.hpp"

namespace ast{
Context::~Context() {
    
    while(!mod.empty()) {
        Module *M = mod.back();
        mod.pop_back();
        delete M;
    }

    while(!loc.empty()) {
        StmtLoc *L = loc.back();
        loc.pop_back();
        delete L;
    }

    while(!stmt.empty()) {
        Ast *S = stmt.back();
        stmt.pop_back();
        delete S;
    }
    
    while(!type.empty()) {
        Type *Ty = type.back();
        type.pop_back();
        delete Ty;
    }

    while(!val.empty()) {
        VALUE *V = val.back();
        val.pop_back();
        delete V;
    }

}

Module *Context::CreateMod(const ModuleInfo &_modinfo) noexcept {
    Module *M = new Module(_modinfo);
    mod.push_back(M);
    return M;
}

StmtLoc *Context::getLoc(Module *_mod, int line, int col) noexcept { 
    StmtLoc *T = new StmtLoc(_mod, line, col);
    loc.push_back(T);
    return T; 
}

}