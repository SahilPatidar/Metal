#pragma once
#include"AstVisitor.hpp"
// #include"../parser/type.hpp"
#include"symbol_table.hpp"
// #include"../Module.hpp"
#include"../ResMgr.hpp"
#include"Table.hpp"
#include"Extern.hpp"
// #include"analyzer/AstVisitor.hpp"
// #include"parser/type.hpp"
// #include"analyzer/symbol_table.hpp"

namespace ast{


class Resolve{
private:
    ResourceMgr &mgr;
    Module *RootModule;
    Table<Ast *>STable;
    Module *ThisModule{nullptr};
    FunctionDef *Func{nullptr};
    std::map<std::string, Module*> Mods;
    ExternHandler ExtHandler;
    bool ScopeOnly{false};

    enum Valid{
        Ty,
        Val,
        None,
    };

    // bool check_path(Ast **source, Expression *AstNode, Module *&mod, Ast *&Node);

    std::string mangle_name(std::string str, std::string modid, Ast *stmt);

    Ast *getModItem(Module *mod, std::string ID);

    bool visit(NewStmt *AstNode, Ast **Base);
    bool visit(DelStmt *AstNode, Ast **Base);
    bool visit(Extern *AstNode, Ast **Base);
    bool visit(BlockStmt *AstNode, Ast **Base);
    bool visit(FunctionDef  *AstNode, Ast **Base);
    bool visit(FunctionProto  *AstNode, Ast **Base);
    bool visit(WhileLoop  *AstNode, Ast **Base);
    bool visit(ForLoop  *AstNode, Ast **Base);
    bool visit(StructStmt  *AstNode, Ast **Base);
    bool visit(Method  *AstNode, Ast **Base);
    bool visit(EnumExpr  *AstNode, Ast **Base);
    bool visit(BranchStmt  *AstNode, Ast **Base);
    bool visit(VarStmt  *AstNode, Ast **Base);
    bool visit(IfStmt  *AstNode, Ast **Base);
    bool visit(UseStmt  *AstNode, Ast **Base);
    bool visit(ReturnStmt  *AstNode, Ast **Base);
    
    bool visit(GroupedExpr  *AstNode, Ast **Base);
    bool visit(Expression  *AstNode, Ast **Base);
    bool visit(FieldExpr  *AstNode, Ast **Base);
    bool visit(PrefixExpr  *AstNode, Ast **Base);

    bool visit(UserDefinedTy *AstNode, Ast **Base);
    bool visit(Array  *AstNode, Ast **Base);
    bool visit(Void  *AstNode, Ast **Base);
    bool visit(FnType  *AstNode, Ast **Base);
    bool visit(PremitiveType  *AstNode, Ast **Base);
    bool visit(Identifier  *AstNode, Ast **Base);

    bool visit(FloatLiteral  *AstNode, Ast **Base);
    bool visit(BoolLiteral  *AstNode, Ast **Base);
    bool visit(NumericLiteral  *AstNode, Ast **Base);
    bool visit(NullLiteral  *AstNode, Ast **Base);
    bool visit(StringLiteral  *AstNode, Ast **Base);
public:
    Resolve(ResourceMgr &_mgr, Module *_RMod)
    :mgr(_mgr), RootModule(_RMod), STable() {}
    ~Resolve() {}

    bool visitTy(Ast *AstNode, Ast **Base);
    bool visitVal(Ast *AstNode, Ast **Base);
    bool visit(Ast *AstNode, Ast **Base, Valid Is = None);
    bool resolve(Ast **AstNode);
    // Type* getType() {}
};



}


