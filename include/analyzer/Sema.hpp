#pragma once
#include"AstVisitor.hpp"
// #include"../parser/type.hpp"
#include"symbol_table.hpp"
// #include"../Module.hpp"
#include"ValCheck.hpp"
#include"../Context.hpp"
// #include"analyzer/StmtVisitor.hpp"
// #include"parser/type.hpp"
// #include"analyzer/symbol_table.hpp"

namespace ast{
class MethodHandler{
public:
    inline bool Has(const String &n) { return Impls.find(n) != Impls.end(); }
    inline void insert(const String &n, FunctionProto *Fn) noexcept { Impls.insert({n, Fn}); }
    inline FunctionProto *getImpl(const String &n) noexcept { return Impls.find(n) != Impls.end()?Impls[n]:nullptr; }
private:
    Map<String, FunctionProto *>Impls;
};

class FieldValHandler{
public:
    inline bool Has(const String &n) { return Vals.find(n) != Vals.end(); }
    inline void insert(const String &n, Ast *Val) noexcept { Vals.insert({n, Val}); }
    inline Ast *getTag(const String &n) noexcept { return Vals.find(n) != Vals.end()?Vals[n]:nullptr; }
private:
    Map<String, Ast *>Vals;
};

template<typename T>
class FValueTable{
public:
    inline bool Has(const String &n) { return Vals.find(n) != Vals.end(); }
    inline void insert(const String &n, T *Val) noexcept { Vals.insert({n, Val}); }
    inline T *getTag(const String &n) noexcept { return Vals.find(n) != Vals.end()?Vals[n]:nullptr; }
private:
    Map<String, T *>Vals;
};


class TypeChecker {
private:
    MethodHandler MT;
    FieldValHandler TagF;
    Map<String, NumericLiteral *>Tag;
    Context &mgr;
    Module *RootMod;
    ValChecker valpass;
    Type *TyForConst{nullptr};
    bool isConst{false};
    bool isConstF{false};
    bool BranchAllow{false};

    String mangle_name(String str, String modid, Ast *stmt);

    void dumpSema(String msg){
        std::cout<<"step :: "<<"entering in -> "<<msg<<" "<<std::endl;
    }
    void dumpSema2(String msg){
        std::cout<<"step :: "<<"returning from -> "<<msg<<" "<<std::endl;
    }

    bool CheckTypeCast(Ast *Node, Type *&from, Type *&to);
    bool TypeCorel(Type *&Ty, Type *&To, Ast *Expr, bool Const = false);

    Ast *getConstVal(Ast *Val, Ast **SrcPtr);

    constexpr bool isAddressableValue(Ast *Expr) const noexcept {
        Ast *Decl = Expr->getDecl();
        if(!Decl || !Decl->Is(NodeVarStm)) {
            return false;
        }
        return true;
    }


    constexpr bool isValue(Ast *Expr, bool ConstAllowed = true) const noexcept {
        Ast *Decl = Expr->getDecl();
        if(!Decl) {
            if(!ConstAllowed) {
                return false;
            }
            if(Expr->IsConst() || Expr->IsTydConst()) {
                return true;
            }
        }
        if(Decl->Is(NodeVarStm) || Decl->Is(NodeFNStm) || Decl->Is(NodeFnProto)) {
            return true;
        }
        return false;
    }

    constexpr bool isTy(Ast *Expr) const noexcept {
        if(Expr->Is(NodeIdent)) {
            Ast *Decl = Expr->getDecl();
            if(!Decl) {
                return false;
            }
            if(!Decl->Is(NodeStructStm) && !Decl->Is(NodeEnum)) {
                return false;
            }
        }else if(!(Expr->Is(NodeVoid) || Expr->Is(NodeArray) || Expr->Is(NodePreDefTy) || (Expr->Is(NodePrefix) && as<PrefixExpr>(Expr)->IsType()) || Expr->Is(NodeFnTy))) {
            return false;
        }
        return false;
    }

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
    TypeChecker(Context &_mgr, Module *_mod)
    :mgr(_mgr), RootMod(_mod), valpass(mgr) {}
    ~TypeChecker() {}

    bool visit(Ast *Stmt, Ast **Base, Type *Ty = nullptr);
    bool Analyze(Ast *tree);
    bool Analyze(Module *Mod);
    // bool CheckTypeAt(String s);

};





}


