#pragma once
#include"AstVisitor.hpp"

// #include"analyzer/AstVisitor.hpp"
// #include"parser/type.hpp"
// #include"analyzer/symbol_table.hpp"

namespace ast{


class ValChecker: public AstVisitor {
private:
    Context &mgr;
    // std::vector<VALUE *>LocalVal;
    bool mustConst{false};
    bool IsReturnStmt{false};
    bool IsBreakStmt{false};
    bool IsContinueStmt{false};
public:
    bool visit(BlockStmt *AstNode, Ast** Base);
    bool visit(FunctionDef *AstNode, Ast** Base);
    bool visit(WhileLoop *AstNode, Ast** Base);
    bool visit(ForLoop *AstNode, Ast** Base);
    bool visit(StructStmt *AstNode, Ast** Base);
    bool visit(EnumExpr *AstNode, Ast** Base);
    bool visit(BranchStmt *AstNode, Ast** Base);
    bool visit(VarStmt *AstNode, Ast** Base);
    bool visit(IfStmt *AstNode, Ast** Base);
    bool visit(UseStmt *AstNode, Ast** Base);
    bool visit(ReturnStmt *AstNode, Ast** Base);
    bool visit(Method  *AstNode, Ast** Base);
    bool visit(GroupedExpr *AstNode, Ast** Base);
    bool visit(FieldExpr *AstNode, Ast** Base) ;
    bool visit(Expression *AstNode, Ast** Base);
    bool visit(PrefixExpr *AstNode, Ast** Base);

    bool visit(Array *AstNode, Ast** Base);
    bool visit(PremitiveType *AstNode, Ast** Base);
    bool visit(Identifier *AstNode, Ast** Base);
    bool visit(FnType  *AstNode, Ast **Base);
    bool visit(FloatLiteral *AstNode, Ast** Base);
    bool visit(BoolLiteral *AstNode, Ast** Base);
    bool visit(NumericLiteral *AstNode, Ast** Base);
    bool visit(NullLiteral *AstNode, Ast** Base);
    bool visit(StringLiteral *AstNode, Ast** Base);
    bool visit(Ast *AstNode, Ast **Base);

    ValChecker(Context &_mgr)
    :mgr(_mgr) {}
    ~ValChecker(){}

};



}


