#pragma once
#include"AstVisitor.hpp"
// #include"../parser/type.hpp"
#include"symbol_table.hpp"
// #include"../Module.hpp"
#include"ValCheck.hpp"
#include"../ResMgr.hpp"
// #include"analyzer/StmtVisitor.hpp"
// #include"parser/type.hpp"
// #include"analyzer/symbol_table.hpp"

namespace ast{
class MethodHandler{
public:
    inline bool Has(const std::string &n) { return Impls.find(n) != Impls.end(); }
    inline void insert(const std::string &n, FunctionProto *Fn) noexcept { Impls.insert({n, Fn}); }
    inline FunctionProto *getImpl(const std::string &n) noexcept { return Impls.find(n) != Impls.end()?Impls[n]:nullptr; }
private:
    std::map<std::string, FunctionProto *>Impls;
};

class FieldValHandler{
public:
    inline bool Has(const std::string &n) { return Vals.find(n) != Vals.end(); }
    inline void insert(const std::string &n, Ast *Val) noexcept { Vals.insert({n, Val}); }
    inline Ast *getTag(const std::string &n) noexcept { return Vals.find(n) != Vals.end()?Vals[n]:nullptr; }
private:
    std::map<std::string, Ast *>Vals;
};

template<typename T>
class FValueTable{
public:
    inline bool Has(const std::string &n) { return Vals.find(n) != Vals.end(); }
    inline void insert(const std::string &n, T *Val) noexcept { Vals.insert({n, Val}); }
    inline T *getTag(const std::string &n) noexcept { return Vals.find(n) != Vals.end()?Vals[n]:nullptr; }
private:
    std::map<std::string, T *>Vals;
};


class TypeChecker {
private:
    MethodHandler MT;
    FieldValHandler TagF;
    std::map<std::string, NumericLiteral *>Tag;
    ResourceMgr &mgr;
    Module *RootMod;
    ValChecker valpass;
    Type *TyForConst{nullptr};
    bool isConst{false};
    bool isConstF{false};
    bool BranchAllow{false};

    std::string mangle_name(std::string str, std::string modid, Ast *stmt);

    void dumpSema(std::string msg){
        std::cout<<"step :: "<<"entering in -> "<<msg<<" "<<std::endl;
    }
    void dumpSema2(std::string msg){
        std::cout<<"step :: "<<"returning from -> "<<msg<<" "<<std::endl;
    }

    bool CheckTypeCast(Ast *Node, Type *&from, Type *&to);
    bool TypeCorel(Type *&Ty, Type *&To, Ast *Expr, bool Const = false);

    Ast *getConstVal(Ast *Val, Ast **SrcPtr);

    bool CheckMethodCallExpr(Expression &Expr, Ast **Base);
    bool CheckCallerArg(Ast *Arg, Type *ParamTy);
    bool CheckBinaryExpr(Expression &Expr, Ast **Base);
    bool CheckStructExpr(Expression &Expr, Ast **Base);
    bool CheckCallExpr(Expression &Expr, Ast **Base);

    bool CheckExtCallExpr(Expression &Expr, Ast **Base);
    bool CheckPrintExtCall(Expression &Expr);
    bool CheckScanfExtCall(Expression &Expr);
    bool CheckExternFnCall(Expression &Expr);


    bool CheckCastExpr(Expression &Expr, Ast **Base);
    bool CheckIndexExpr(Expression &Expr, Ast **Base);
    bool CheckMemExpr(Expression &Expr, Ast **Base);
    bool CheckPathExpr(Expression &Expr, Ast **Base);
    bool CheckIsExpr(Expression &Expr, Ast **Base);
    bool CheckIndexOutOfBound(Ast *IdxVal, size_t DimSize);
    bool CheckPointerIndex(Expression &Expr);


    bool CheckIsInitialized(Ast *Expr, bool MustInit = false);
    void setInitialized(Ast *Expr);

    bool visit(FunctionProto  *Stmt, Ast **Base);
    bool visit(FunctionDef  *Stmt, Ast **Base);
    bool visit(WhileLoop  *Stmt, Ast **Base);
    bool visit(ForLoop  *Stmt, Ast **Base);
    bool visit(StructStmt  *Stmt, Ast **Base);
    bool visit(Method  *Stmt, Ast **Base);
    bool visit(EnumExpr  *Stmt, Ast **Base);
    bool visit(BranchStmt  *Stmt, Ast **Base);
    bool visit(VarStmt  *Stmt, Ast **Base);
    bool visit(IfStmt  *Stmt, Ast **Base);
    bool visit(UseStmt  *Stmt, Ast **Base);
    bool visit(ReturnStmt  *Stmt, Ast **Base);
    bool visit(BlockStmt  *Stmt, Ast **Base);
    bool visit(NewStmt  *Stmt, Ast **Base);
    bool visit(DelStmt  *Stmt, Ast **Base);
    
    bool visit(GroupedExpr  *Stmt, Ast **Base);
    bool visit(Expression  *Stmt, Ast **Base);
    bool visit(FieldExpr  *Stmt,  Ast **Base);
    bool visit(PrefixExpr  *Stmt, Ast **Base);

    bool visit(UserDefinedTy *Stmt, Ast **Base);
    bool visit(Array  *Stmt, Ast **Base);
    bool visit(FnType  *Stmt, Ast **Base);
    bool visit(PremitiveType  *Stmt, Ast **Base);
    bool visit(Void  *Stmt, Ast **Base);
    bool visit(Identifier  *Stmt, Ast **Base);

    bool visit(FloatLiteral  *Stmt, Ast **Base);
    bool visit(BoolLiteral  *Stmt, Ast **Base);
    bool visit(NumericLiteral  *Stmt, Ast **Base);
    bool visit(NullLiteral  *Stmt, Ast **Base);
    bool visit(StringLiteral  *Stmt, Ast **Base);
public:
    TypeChecker(ResourceMgr &_mgr, Module *_mod)
    :mgr(_mgr), RootMod(_mod), valpass(mgr) {}
    ~TypeChecker() {}

    bool visit(Ast *Stmt, Ast **Base, Type *Ty = nullptr);
    bool Analyze(Ast *tree);
    bool Analyze(Module *Mod);
    // bool CheckTypeAt(std::string s);

};





}


