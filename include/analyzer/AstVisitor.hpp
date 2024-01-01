#pragma once

#include"../parser/Ast.hpp"
// #include"parser/Ast.hpp"
namespace ast{
class AstVisitor{
public:
    virtual ~AstVisitor() = default;

protected:
    virtual bool visit(NewStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(DelStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(BlockStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(FunctionDef *AstNode, Ast **Base){ return false; }
    virtual bool visit(WhileLoop *AstNode, Ast **Base){ return false; }
    virtual bool visit(ForLoop *AstNode, Ast **Base){ return false; };
    virtual bool visit(StructStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(Method *AstNode, Ast **Base){ return false; }
    virtual bool visit(BranchStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(VarStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(IfStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(UseStmt *AstNode, Ast **Base){ return false; }
    virtual bool visit(EnumExpr *AstNode, Ast **Base){ return false; }
    virtual bool visit(ReturnStmt *AstNode, Ast **Base){ return false; }
    
    virtual bool visit(GroupedExpr *AstNode, Ast **Base){ return false; }
    virtual bool visit(FieldExpr *AstNode, Ast **Base){ return false; }
    virtual bool visit(Expression *AstNode, Ast **Base){ return false; }
    virtual bool visit(PrefixExpr *AstNode, Ast **Base){ return false; }
    
    virtual bool visit(Array *AstNode, Ast **Base) { return false; }
    virtual bool visit(FnType *AstNode, Ast **Base) { return false; }
    virtual bool visit(PremitiveType *AstNode, Ast **Base){ return false; }
    virtual bool visit(Identifier *AstNode, Ast **Base){ return false; }
    

    virtual bool visit(FloatLiteral *AstNode, Ast **Base){ return false; }
    virtual bool visit(BoolLiteral *AstNode, Ast **Base){ return false; }
    virtual bool visit(NumericLiteral *AstNode, Ast **Base){ return false; }
    virtual bool visit(NullLiteral *AstNode, Ast **Base){ return false; }
    virtual bool visit(StringLiteral *AstNode, Ast **Base){ return false; }
    
    //virtual bool visit(const TypeState   *AstNode, Ast **Base ){ return false; }
    //virtual bool visit(const EnumLitral   *AstNode, Ast **Base ){ return false; }
};

}