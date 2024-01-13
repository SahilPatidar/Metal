#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"

#include"../analyzer/Value.hpp"
// #include"../analyzer/Value.hpp"
// #include"lex/lex.hpp"
// #include"analyzer/AstVisitor.hpp"
// #include"type.hpp"


namespace ast{

    enum NodeCategory{
        NodeBlockStm,
        NodeImport,
        NodeNumLit,
        NodeBoolLit,
        NodeFloatLit,
        NodeStrLit,
        NodeNullLit,
        NodeIdent,
        NodeEnum,
        NodePrefix,
        NodeField,
        NodeExtern,
        NodeGroupExpr,
        NodeExpr,

        NodePreDefTy,
        NodeArray,
        NodeFnTy,
        NodeUserDefTy,

        NodeIfStm,
        NodeWhileStm,
        NodeTypeStm,
        NodeForStm,
        NodeVarStm,
        NodeRetStm,
        NodeBranchStm,
        NodeStructStm,
        NodeImpl,
        NodeUseStmt,
        
        NodeCallExpr,
        NodeFNStm,
        NodeFnProto,

        NodeVoid,
        NodeNewStmt,
        NodeDelStmt
    };

    #define _GLOB 8
    #define _METHOD 32
    #define _EXTERN 16
    #define _VARG 64
    #define _FVAR 16
    #define _ASSOC 8 
    #define _CONST 4
    #define _MUT 2

    
    class Type;
    class Expression;
    class Ast {
    protected:
        const StmtLoc *loc;
        Type *type{nullptr};
        Type *castTo{nullptr};
        VALUE *value{nullptr};
        Ast *Decl{nullptr};
        bool Mangle{false};
        bool Mut{false};
        bool Const{false};
        bool TypedConst{false};
        bool Initialized{false};
        NodeCategory NodeTy;
    public:
        Ast(const StmtLoc *_Loc, NodeCategory _NodeTy)
        :loc(_Loc), NodeTy(_NodeTy) {}
        virtual ~Ast() = default;
        inline const StmtLoc *getStmtLoc() const noexcept { return loc; }

        inline void setMut() noexcept { Mut = true; }
        inline void setConst() noexcept { Const = true; }
        inline bool IsMut() const noexcept { return Mut; }
        inline bool IsConst() const noexcept { return Const; }

        inline void setTydConst() noexcept { TypedConst = true; }
        inline bool IsTydConst() const noexcept { return TypedConst; }
        inline bool IsInitialized() const noexcept { return Initialized; }
        inline void setInitialized() noexcept { Initialized = true; }

        inline void setDecl(Ast *_Decl) { Decl = _Decl; }
        inline Ast *&getDecl() noexcept { return Decl; }
        inline void setType(Type *_type) { type = _type; }
        inline void setValue(VALUE *_Value) { value = _Value; }
        inline void setTypeValue(Type *_type, VALUE *_Value) {
            type = _type;
            value = _Value; 
        }
        inline void setUpdateValue(VALUE *_Value) {
            if(value) value->updateValue(_Value);
            else value = _Value; 
        }
        inline Type*& getTypeInfo() noexcept { return type; }
        inline Type*& getcastTy() noexcept { return castTo; }
        inline VALUE* getValueInfo() noexcept { return value; }
        inline void setCastTo(Type *to) { 
            castTo = to;
        }
        inline bool isMangled() noexcept { return Mangle; }
        inline void setMangled() { Mangle = true; }

        virtual std::string toString() const = 0;
        inline bool Is(const NodeCategory &nty) const noexcept { return nty == NodeTy;}
        inline NodeCategory getStmtTy() const noexcept { return NodeTy;}
    };
   
    template<typename T> 
    Ast **asAst(T **data) {
        return (Ast **)data;
    }

    template<typename T>
    T **asAstRef(Ast **data) {
        return (T**)data;
    }

    class BlockStmt: public Ast {
    private:
        std::vector<Ast *> stmts;
    public:
        BlockStmt(const StmtLoc *_Loc,  const std::vector<Ast *> &_state)
        :Ast(_Loc, NodeCategory::NodeBlockStm), stmts(_state) {}
        ~BlockStmt() {}

        static BlockStmt *Create(Context &mgr, const StmtLoc *_Loc,  const std::vector<Ast *> &stmts);
        inline std::vector<Ast *>& getStmts() noexcept {return stmts;}
        inline bool empty() const noexcept { return stmts.empty(); }
        std::string toString() const;

    };


    class NewStmt: public Ast {
    public: 
        NewStmt(const StmtLoc *_loc, Ast *_Ty, Ast *_Size)
        :Ast(_loc, NodeNewStmt), Ty(_Ty), Size(_Size) {}
        ~NewStmt(){}

        inline Ast *&getTy() noexcept { return Ty; }
        inline Ast *&getSize() noexcept { return Size; }
        static NewStmt *Create(Context &Mgr, const StmtLoc *_loc, Ast *_Ty, Ast *_Size);
        std::string toString() const;
    private:
        Ast *Ty;
        Ast *Size;
    };


    class DelStmt: public Ast {
    public: 
        DelStmt(const StmtLoc *_loc, Ast *_VPtr)
        :Ast(_loc, NodeDelStmt), VPtr(_VPtr) {}
        ~DelStmt() {}

        inline Ast *&getPtr() noexcept { return VPtr; }
        static DelStmt *Create(Context &Mgr, const StmtLoc *_loc, Ast *_VPtr);
        std::string toString() const;
    private:
        Ast *VPtr;
    };


    class NullLiteral: public Ast {
        private:
        Lexeme tok;
        public:
        NullLiteral(const StmtLoc *_Loc,  const Lexeme &_tok)
        :Ast(_Loc, NodeCategory::NodeNullLit), tok(_tok) {}
        ~NullLiteral() {}
        static NullLiteral *Create(Context &mgr, const StmtLoc *_Loc,   const Lexeme &_tok);
        inline Lexeme& getLexeme() noexcept { return tok; }
        std::string toString() const;

    };

  
    class NumericLiteral: public Ast {
    private:
        Lexeme tok;
      //  std::string Int;
    public:
        NumericLiteral(const StmtLoc *_Loc, const Lexeme &_tok)
        :Ast(_Loc, NodeNumLit), tok(_tok) {}
        ~NumericLiteral() {}

        static NumericLiteral *Create(Context &mgr, const StmtLoc *_Loc,   const Lexeme &_tok);
        inline Lexeme& getLexeme() noexcept { return tok; };
        std::string toString() const;
    };


    class BoolLiteral: public Ast {
        private:
      //  std::string val;
        Lexeme tok;
        public:
        BoolLiteral(const StmtLoc *_Loc,  const Lexeme &_tok)
        :Ast(_Loc, NodeCategory::NodeBoolLit), tok(_tok) {}
        ~BoolLiteral() {}

        static BoolLiteral *Create(Context &mgr, const StmtLoc *_Loc,   const Lexeme &_tok);
        //std::string value() const;
        inline Lexeme& getLexeme()  { return tok; }
        std::string toString() const;
    };
    

    class StringLiteral: public Ast {
        private:
        Lexeme tok;
        bool chr;

        public:
        StringLiteral(const StmtLoc *_Loc,  const Lexeme &_tok, bool _chr)
        :Ast(_Loc, NodeCategory::NodeStrLit), tok(_tok), chr(_chr) {}
        ~StringLiteral() {}

        static StringLiteral *Create(Context &mgr, const StmtLoc *_Loc,   const Lexeme &_tok, bool _chr);
        inline Lexeme& getLexeme() { return tok; }
        //std::string value() const{ return tok.data; }
        inline bool ischar() noexcept { return chr; }
        std::string toString() const;
    };



    class FloatLiteral: public Ast {
        private:
        Lexeme tok;

        public:
        FloatLiteral(const StmtLoc *_Loc,  const Lexeme &_tok)
        :Ast(_Loc, NodeCategory::NodeFloatLit), tok(_tok) {}
        ~FloatLiteral() {}
        static FloatLiteral *Create(Context &mgr, const StmtLoc *_Loc,   const Lexeme &_tok);
        inline Lexeme& getLexeme() noexcept { return tok; }
        //std::string value() const { return tok.data; }
        std::string toString() const;
        
    };

    class Void: public Ast {
    public:
        Void(const StmtLoc *_Loc)
        :Ast(_Loc, NodeCategory::NodeVoid) {}
        ~Void() {}
        static Void *Create(Context &mgr, const StmtLoc *_Loc);
        std::string toString() const;
    };

    class Identifier: public Ast {
        private:
        Lexeme tok;
        bool isTy;
        public:
        Identifier(const StmtLoc *_Loc,  const Lexeme &_tok, bool _isTy)
        :Ast(_Loc, NodeCategory::NodeIdent), tok(_tok), isTy(_isTy) {}
        ~Identifier() {}

        static Identifier *Create(Context &mgr, const StmtLoc *_Loc,  const Lexeme &_tok, bool _isTy = false);
        inline Lexeme& getLexeme() noexcept { return tok; }
        inline std::string getIdent() noexcept { return tok.getStr(); }
        inline bool HasSelf() noexcept { return tok.getTokTy() == Token_type::SELF; }
        inline bool IsTy() const noexcept { return isTy; }
        std::string toString() const;
    };

    class VarStmt: public Ast {
        private:
        Lexeme var;
        Ast * type;
        Ast * val;
        int8_t mask{0};
        public:

        VarStmt(const StmtLoc *_Loc,  Lexeme &_var, Ast *_type, Ast *_Val, int8_t _mask)
        :Ast(_Loc, NodeCategory::NodeVarStm), var(_var), type(_type), val(_Val), mask(_mask) {}
        ~VarStmt() {}



        static VarStmt *Create(Context &mgr, const StmtLoc *_Loc, const Lexeme &_var, Ast *_type, Ast *_Val, int8_t _mask);
        // inline const Lexeme &getLexeme() {return tok;}
        inline Lexeme &getVar() noexcept {return var;}
        inline Ast *&getType() {return type;}
        inline Ast *&getVal() {return val;}
        inline bool HasMut() const noexcept { return mask&_MUT; }
        inline bool IsConst() const noexcept { return mask&_CONST; }
        inline bool IsFieldVar() const noexcept { return mask&_FVAR; }
        inline bool IsGlobVar() const noexcept { return mask&_GLOB; }
        inline void setGVar() noexcept {  mask|=_GLOB; }
        std::string toString() const;
        
    };

    class UseStmt: public Ast {
        private:
        Ast *path;
        public:
        UseStmt(const StmtLoc *_Loc, Ast *_path)
        :Ast(_Loc, NodeCategory::NodeUseStmt), path(_path) {}
        ~UseStmt() {}

        static UseStmt *Create(Context &mgr, const StmtLoc *_Loc,  Ast *_path);
        inline Ast *&getPath() { return path; }
        std::string toString() const;
        
    };


    class EnumExpr: public Ast {
        private:
        Lexeme Name;
        std::vector<VarStmt *>Evals;
        public:
        EnumExpr(const StmtLoc *_Loc,  const Lexeme &_Name, const std::vector<VarStmt *>&_Evals)
        :Ast(_Loc, NodeCategory::NodeEnum), Name(_Name), Evals(_Evals) {}
        ~EnumExpr() {}

        static EnumExpr *Create(Context &mgr, const StmtLoc *_Loc,  const Lexeme &_Name, const std::vector<VarStmt *>&_Evals);
        inline Lexeme& getName() noexcept { return Name; }
        inline std::vector<VarStmt *> &getEVals() noexcept { return Evals; }
        std::string toString() const;
        
    };

    class Method: public Ast {
    private:
        Ast *Name;
        Ast *AssociateTo;
        std::vector<Ast *>Impl;
    public:
        Method(const StmtLoc *_Loc, Ast *_Name, Ast *_AssociateTo, std::vector<Ast *>&_impl)
        :Ast(_Loc, NodeCategory::NodeImpl), Name(_Name), AssociateTo(_AssociateTo), Impl(_impl) {}
        ~Method() {}

        static Method *Create(Context &mgr, const StmtLoc *_Loc,  Ast *_Name, Ast *_AssociateTo, std::vector<Ast *>&_impl);
        inline Ast *&getName() noexcept { return Name; }
        inline Ast *&getAssociativity() { return AssociateTo; }
        inline std::vector<Ast *>& getImpl() { return Impl; }
        std::string toString() const;
        
    };

    class Extern: public Ast {
    public:
        Extern(const StmtLoc *_Loc, const Lexeme &_ID, bool isFn)
        :Ast(_Loc, NodeExtern), ID(_ID) {}
        ~Extern() {}

        static Extern *Create(Context &mgr, const StmtLoc *_Loc, const Lexeme &_ID, bool isFn);
        inline Lexeme &getID() noexcept {return ID;}
        inline bool IsFn() const noexcept {return isFn;}
        inline bool IsStruct() const noexcept {return !isFn;}
        std::string toString() const;
    private:
        Lexeme ID;
        bool isFn;
    };


    class PremitiveType: public Ast{
        private:
        Lexeme tok;
        public:
        PremitiveType(const StmtLoc *_Loc,  const Lexeme &_tok)
        :Ast(_Loc, NodeCategory::NodePreDefTy), tok(_tok) {}
        ~PremitiveType() {}

        static PremitiveType *Create(Context &mgr, const StmtLoc *_Loc,   const Lexeme &_tok);
        inline Lexeme &getLexeme() noexcept { return tok; }
        inline Tok getType() const noexcept { return tok.getTok(); }
        inline const Token_type getTType() const noexcept { return tok.getTokTy(); }

        std::string toString() const;
        

    };

    


    class PrefixExpr: public Ast{
        private:
        Tok op;
        Ast * base;
        bool Mut;
        bool isType;
        public:
        PrefixExpr(const StmtLoc *_Loc, Tok _op, Ast *_Type, bool _Mut, bool _isType)
        :Ast(_Loc, NodeCategory::NodePrefix), op(_op), base(_Type), Mut(_Mut), isType(_isType) {}
        ~PrefixExpr() {}

        static PrefixExpr *Create(Context &mgr, const StmtLoc *_Loc, Tok _op, Ast *_Type, bool _Mut, bool _isType);
        inline const Tok &getOp() const noexcept { return op; }
        inline Ast *&getBase()  { return base; }
        inline bool IsType() const noexcept { return isType; }
        inline bool HasMut() const noexcept { return Mut; }
        std::string toString() const;

    };

    class Expression: public Ast{
        public:
        enum ExprID{
            KCallExpr,
            KIndexExpr,
            KStructExpr,
            KBinaryExpr,
            KMemExpr,
            KPathExpr,
            KAsExpr,
            KIsExpr,
            KExtCallExpr,
        };
        #define isExpr(N, Ty)          \
            bool is##N() const noexcept { return ExprTy == Ty; }                   

        isExpr(CastExpr, KAsExpr)
        isExpr(StructExpr, KStructExpr)
        isExpr(CallExpr, KCallExpr)
        isExpr(ExtCallExpr, KExtCallExpr)
        isExpr(BinExpr, KBinaryExpr)
        isExpr(IndexExpr, KIndexExpr)
        isExpr(MemAccessExpr, KMemExpr)
        isExpr(IsExpr, KIsExpr)
        isExpr(PathExpr,  KPathExpr)

        private:
        Ast * LHS;
        Tok Op;
        Ast * RHS;
        ExprID ExprTy;
        public:
        explicit Expression(const StmtLoc *_Loc,  Ast *_LHS, Tok _op, Ast *_RHS,
                     ExprID _ExprTy)
        :Ast(_Loc, NodeCategory::NodeExpr), LHS(_LHS),Op(_op), RHS(_RHS), ExprTy(_ExprTy) {}
        explicit Expression(const StmtLoc *_Loc,  Ast *_LHS, Ast *_RHS,
                     ExprID _ExprTy)
        :Ast(_Loc, NodeCategory::NodeExpr), LHS(_LHS), Op({}), RHS(_RHS), ExprTy(_ExprTy) {}
        ~Expression() {}

        static Expression *Create(Context &mgr, const StmtLoc *_Loc, Ast *_LHS, Tok _op, Ast *_RHS,
                     ExprID _ExprTy);
        static Expression *Create(Context &mgr, const StmtLoc *_Loc, Ast *_LHS, Ast *_RHS,
                     ExprID _ExprTy);
        inline Ast *&getLhs()  {return LHS;}
        inline const Tok &getOp() const noexcept {return Op;}
        inline Ast *&getRhs()  {return RHS;}
        inline ExprID getExprID() const noexcept {return ExprTy;}
        std::string toString() const;

    };

    class GroupedExpr:public Ast {
        Ast * expr;
        public:
        GroupedExpr(const StmtLoc *_Loc,  Ast *_expr)
        :Ast(_Loc, NodeCategory::NodeGroupExpr), expr(_expr) {}
        ~GroupedExpr() {}

        static GroupedExpr *Create(Context &mgr, const StmtLoc *_Loc,   Ast *_expr);
        inline Ast *& getExpression()  { return expr; }
        std::string toString() const;
    
    };

    class FnType: public Ast {
        private:
        std::vector<Ast *> ty;
        Ast * ret;
       
        public:
        FnType(const StmtLoc *_Loc, const std::vector<Ast *>&_ty, Ast *_ret)
        :Ast(_Loc, NodeCategory::NodeFnTy), ty(_ty), ret(_ret) {}
        ~FnType() {}

        static FnType *Create(Context &mgr, const StmtLoc *_Loc, const std::vector<Ast *>&_ty, Ast *_ret);
        inline std::vector<Ast *> &getParamType() { return ty; }
        inline Ast *& getRetType()  { return ret; }
        std::string toString() const;
    
    };

    
    class Array: public Ast {
        private:
        Ast *Size;
        Ast *Ty;
        public:
        Array(const StmtLoc *_Loc, Ast *_Size, Ast *_Ty)
        :Ast(_Loc, NodeCategory::NodeArray), Size(_Size), Ty(_Ty) {}
        ~Array() {}

        static Array *Create(Context &mgr, const StmtLoc *_Loc, Ast *_Size, Ast *_Ty);
        inline Ast *&getArraySize() {return Size;}
        inline Ast *&getArrayTy() {return Ty;}
        std::string toString() const;

    };


    class WhileLoop: public Ast{
    private:
        Ast *expr;
        BlockStmt *body;

    public:
        WhileLoop(const StmtLoc *_Loc, Ast *_expr, BlockStmt *_body )
        :Ast(_Loc, NodeCategory::NodeWhileStm), expr(_expr), body(_body)  {}
        ~WhileLoop() {}

        static WhileLoop *Create(Context &mgr, const StmtLoc *_Loc,  Ast *_expr, BlockStmt *_body );
        inline Ast *&getCond()  { return expr; }
        inline BlockStmt *&getBlock()  { return body; }
        std::string toString() const;
    };


    class ForLoop: public Ast{
    private:
        Ast *var;
        Ast *cond;
        Ast *incr;
        BlockStmt *body;

    public:
        ForLoop(const StmtLoc *_Loc, Ast *_var, Ast *_cond, Ast *_incr, BlockStmt *_body )
        :Ast(_Loc, NodeCategory::NodeForStm), var(_var), cond(_cond), incr(_incr), body(_body)  {}
        ~ForLoop() {}

        static ForLoop *Create(Context &mgr, const StmtLoc *_Loc, Ast *_var, Ast *_cond, Ast *_incr, BlockStmt *_body );
        inline Ast *&getVar()  { return var; }
        inline Ast *&getCond()  { return cond; }
        inline Ast *&getIncr()  { return incr; }
        inline BlockStmt *&getBlock()  { return body; }
        std::string toString() const;
    };

    class IfStmt: public Ast{
    private:
        Ast *cond;
        BlockStmt *ifblock;
        Ast *elblock;
        
    public:
        IfStmt(const StmtLoc *_Loc, Ast *_cond , BlockStmt *_ifblock,
                             Ast *_elblock)
        :Ast(_Loc, NodeCategory::NodeIfStm), cond(_cond), ifblock(_ifblock), 
                        elblock(_elblock) {}
        ~IfStmt() {}

        static IfStmt *Create(Context &mgr, const StmtLoc *_Loc,  Ast *_cond , BlockStmt *_ifblock,
                             Ast *_elblock);
        inline const Ast *getCondV() const { return cond; }
        inline Ast *&getCondV()  { return cond; }
        inline BlockStmt *&getIfBlock()  { return ifblock; }
        inline const Ast *getElBlock() const { return  elblock; }
        inline Ast *&getElBlock() { return  elblock; }
        std::string toString() const;
    };



    class BranchStmt: public Ast {
    private:
        Lexeme tok;
    public:
        BranchStmt(const StmtLoc *_Loc,  const Lexeme &_tok)
        :Ast(_Loc, NodeCategory::NodeBranchStm), tok(_tok) {}
        ~BranchStmt() {}

        static BranchStmt *Create(Context &mgr, const StmtLoc *_Loc, const Lexeme &_tok);
        inline Lexeme &getLexeme() noexcept { return tok; }
        std::string toString() const;
        
        NodeCategory nodeCategory() const { return NodeCategory::NodeBranchStm; }
    };

    class UserDefinedTy: public Ast{
        private:
        Ast *Expr;
        // GenericParam *Param;

        //TypePtr typeinfo;
        public:
        UserDefinedTy(const StmtLoc *_Loc, Ast *_Expr)
        :Ast(_Loc, NodeCategory::NodeUserDefTy), Expr(_Expr)
        {}
        ~UserDefinedTy() {}

        static UserDefinedTy *Create(Context &mgr, const StmtLoc *_Loc, Ast *_Expr);
        inline Ast *&getExpr() { return Expr; }
        std::string toString() const;
        
        NodeCategory nodeCategory() const {return NodeCategory::NodeUserDefTy;}

    };
    

    class StructStmt: public Ast {
    private:
        Lexeme Ident;
        std::vector<VarStmt *> field; 
        Method *Impl{nullptr};
        bool Extern{false};
    public:
        StructStmt(const StmtLoc *_Loc, const Lexeme &_Ident, std::vector<VarStmt *>&_field)
        :Ast(_Loc, NodeCategory::NodeStructStm), Ident(_Ident), field(_field) {}
        ~StructStmt() {}


        static StructStmt *Create(Context &mgr, const StmtLoc *_Loc, const Lexeme &_Ident,
                        std::vector<VarStmt *>&_field);
    
        inline void setExtern() noexcept { Extern = true; }
        inline bool isExtern() noexcept { return Extern; }
        
        inline Lexeme &getName() noexcept { return Ident; }
        inline bool HasImpl() const noexcept { return Impl != nullptr; }
        inline Method *getImpl()  noexcept { return Impl; }
        inline void setImpl(Method *_Impl) noexcept {  Impl = _Impl; }
        inline std::vector<VarStmt *>& getfield() noexcept { return field; }
        std::string toString() const;

    };

    class FunctionProto: public Ast {
    private:
        Lexeme Name;
        std::vector<VarStmt *> Param;
        Ast * RetTy;
        int8_t mask{0};
    public:
        FunctionProto(const StmtLoc *_Loc, const Lexeme &_Name, const std::vector<VarStmt *> &_Param, Ast *_RetTy)
         :Ast(_Loc, NodeCategory::NodeFnProto), Name(_Name), Param(_Param), 
            RetTy(_RetTy) {}
        ~FunctionProto() {}

        inline void setExtern() noexcept { mask |= _EXTERN; }
        inline bool isExtern() noexcept { return mask&_EXTERN; }
        inline void setVariadic() noexcept { mask |= _VARG; }
        inline bool isVariadic() noexcept { return mask&_VARG; }
        inline bool IsMemberFunc() const noexcept{ return mask&_METHOD; }
        inline void setMemberFunc() noexcept{  mask = mask|_METHOD; }
        inline bool IsAssociateFunc() const noexcept{ return mask&_ASSOC; }
        inline void setAssociateFunc() noexcept{  mask = mask|_ASSOC; }

        static FunctionProto *Create(Context &mgr, const StmtLoc *_Loc,  const Lexeme &_Name, const std::vector<VarStmt *>&_Param, Ast *_RetTy);
        inline Lexeme &getFuncName() noexcept { return Name; }
        inline std::vector<VarStmt *>& getParameter() { return Param; }
        inline Ast *&getResultType() noexcept { return RetTy; }
        std::string toString() const;
    };


    class FunctionDef: public Ast {
    private:
        FunctionProto *FuncSig;
        BlockStmt *Block; 
        int8_t mask{0};
    public:
        FunctionDef(const StmtLoc *_Loc, FunctionProto *_FnSig, BlockStmt *_Block)
         :Ast(_Loc, NodeCategory::NodeFNStm), FuncSig(_FnSig), Block(_Block){}
        ~FunctionDef() {}


        static FunctionDef *Create(Context &mgr, const StmtLoc *_Loc, FunctionProto *_FnSig, BlockStmt *_Block);
        inline FunctionProto *getFnProto() const noexcept { return FuncSig; }
        inline BlockStmt *getFuncBlock() const noexcept { return Block; }
        // inline bool IsMemberFunc() const noexcept{ return mask&_METHOD; }
        // inline void setMemberFunc() noexcept{  mask = mask|_METHOD; }
        // inline bool IsAssociateFunc() const noexcept{ return mask&_ASSOC; }
        // inline void setAssociateFunc() noexcept{  mask = mask|_ASSOC; }
        std::string toString() const;
    };


    class ReturnStmt: public Ast {
        private:
        Ast * val;
        BlockStmt *Blk{nullptr};
        public:
        ReturnStmt(const StmtLoc *_Loc, Ast *_Val)
        :Ast(_Loc, NodeCategory::NodeRetStm), val(_Val) {}
        ~ReturnStmt() {}

        static ReturnStmt *Create(Context &mgr, const StmtLoc *_Loc, Ast *_Val);
        inline Ast *&getRetValue() noexcept { return val; }
        inline BlockStmt *&getFnBlk() noexcept {return Blk;}
        inline void setFnBlk(BlockStmt *_Blk) noexcept { Blk = _Blk;}
        std::string toString() const;
    };


    class FieldExpr: public Ast{
    private:
        std::vector<Ast *>args;
        bool Const{false};
    public:
        FieldExpr(const StmtLoc *_Loc,  const std::vector<Ast *>& _args)
        :Ast(_Loc, NodeCategory::NodeField), args(_args) {}
        ~FieldExpr() {}

        static FieldExpr *Create(Context &mgr, const StmtLoc *_Loc, const std::vector<Ast *>&_args);
        inline std::vector<Ast *> &getArgs() { return args; }
        inline void setC(bool _Const = true) noexcept { Const = _Const; }
        inline bool isCF() const noexcept { return Const; }
        std::string toString() const;
    };

}
