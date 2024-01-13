#pragma once
#include<iostream>
#include<vector>
#include"IncHeader.hpp"
#include"Core.hpp"

namespace ast{
class StmtLoc;

// reference from scribe language
class Context{
private:    
    Vec<Module*>mod;
    Vec<Ast*>stmt;
    Vec<StmtLoc*>loc;
    Vec<VALUE*>val;
    Vec<Type*>type;
public:
    Context() {}
    ~Context();


    template<typename T, typename... Args> T *CreateStmt(Args... args)
	{
		T *res = new T(args...);
        stmt.push_back(res);
		return res;
	} 

    template<typename T, typename... Args> T *CreateTy(Args... args)
	{
		T *res = new T(args...);
        type.push_back(res);
		return res;
	} 

    template<typename T, typename... Args> T *CreateVal(Args... args)
	{
		T *res = new T(args...);
        val.push_back(res);
		return res;
	} 

    Module *CreateMod(const ModuleInfo &_modinfo) noexcept;

    StmtLoc *getLoc(Module *_mod, int line, int col) noexcept;
    inline Module *getMod() const noexcept { return mod.back(); }

};


class StmtLoc{
public:
    StmtLoc(Module *_mod, int _line, int _col)
    : mod(_mod), line(_line), col(_col) {}
    ~StmtLoc(){}

    inline String getString() const noexcept {
        return std::to_string(line) + ":" + std::to_string(col);
    }
    
    inline int getCol() const noexcept {
        return col;
    }

    inline int getLine() const noexcept {
        return line;
    }
    inline Module* getMod() const noexcept {
        return mod;
    }

    static StmtLoc *Create(Context &mgr, Module *_mod, int _line, int _col) {
        return mgr.getLoc(_mod, _line, _col);
    }
private:
    Module *mod;
    int line;
    int col;
};

}
