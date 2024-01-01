#pragma once
#include"../ResMgr.hpp"
#include"../parser/Ast.hpp"
namespace ast { 
typedef bool (*IntrinsicFn)(ResourceMgr &Mgr, Expression *stmt, Ast **source, std::vector<Ast *> &args);
#define INTRINSIC(name) \
    bool Intrinsic##name(ResourceMgr &Mgr, Expression *Expr, Ast **source, std::vector<Ast *>&arg)



// INTRINSIC(sizOf);
// INTRINSIC(make);
INTRINSIC(print);
// INTRINSIC(sizOf);
// INTRINSIC(sizOf);
// INTRINSIC(sizOf);
// INTRINSIC(sizOf);
}