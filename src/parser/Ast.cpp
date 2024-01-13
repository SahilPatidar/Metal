
#include"../../include/Context.hpp"
#include"../../include/parser/Ast.hpp"
// #include"parser/Ast.hpp"

namespace ast {

    NumericLiteral* NumericLiteral::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<NumericLiteral>(_loc, _tok);
    }


    std::string NumericLiteral::toString() const{
        return tok.getStr();
    }

    FloatLiteral* FloatLiteral::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<FloatLiteral>(_loc, _tok);
    }

    std::string FloatLiteral::toString() const{
        return tok.getStr();
    }

    BoolLiteral* BoolLiteral::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<BoolLiteral>(_loc, _tok);
    }

    std::string BoolLiteral::toString() const {
        return tok.getStr();
    }

    StringLiteral* StringLiteral::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok, bool _chr){
        return mgr.CreateStmt<StringLiteral>(_loc, _tok,_chr);
    }

    std::string StringLiteral::toString() const {
        return tok.getStr();
    }

    NullLiteral* NullLiteral::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<NullLiteral>(_loc, _tok);
    }

    std::string NullLiteral::toString() const {
        return tok.getStr();
    }


    Identifier* Identifier::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok, bool _isTy) {
        return mgr.CreateStmt<Identifier>(_loc, _tok, _isTy);
    }

    std::string Identifier::toString() const {
        return tok.getStr();
    }

    BlockStmt* BlockStmt::Create(Context &mgr, const StmtLoc *_loc,const std::vector<Ast *> &stmts) {
        return mgr.CreateStmt<BlockStmt>(_loc, stmts);
    }

    std::string BlockStmt::toString() const {
        std::string str = "";
        if(!stmts.empty())
            for(ssize_t i = 0, size = stmts.size(); i < size; i++){
                if(stmts[i] == nullptr){

                }
                str += stmts[i]->toString();
                str += "\n";
            }


        return str;
    }

    EnumExpr *EnumExpr::Create(Context &mgr, const StmtLoc *_loc,  const Lexeme &_Name, const std::vector<VarStmt *>&_Evals) {
        return mgr.CreateStmt<EnumExpr>(_loc, _Name, _Evals);
    }

    std::string EnumExpr::toString() const {
        std::string str = "enum ";
        str += Name.getStr();
        str += " {\n";
        if(!Evals.empty())
            for (ssize_t i = 0, siz = Evals.size(); i < siz; i++) {
                if (i)
                    str += ",\n";

                str += Evals[i]->getVar().getStr();
                if(Evals[i]->getVal()) {
                    str += " = ";
                    str += Evals[i]->getVal()->toString();
                }
            }
        str += "}\n";

        

        return str;
    }

    PremitiveType* PremitiveType::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok) {
        return mgr.CreateStmt<PremitiveType>(_loc, _tok);
    }

    std::string PremitiveType::toString() const {
        return tok.getStr();
    }


    VarStmt* VarStmt::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_var, Ast *_type, Ast *_val, int8_t _mask) {
        return mgr.CreateStmt<VarStmt>(_loc, _var, _type, _val, _mask);
    }

    std::string VarStmt::toString() const {
        std::string str = "let ";
        str += var.getStr();
        str += " : ";
        if(type != nullptr){
            str += type->toString();
        }
        if(val != nullptr){
            str += " = ";
            str += val->toString();
        }
        str += ";\n";
        

        return str;
    }

    Array* Array::Create(Context &mgr, const StmtLoc *_loc , Ast *_Size, Ast *_type) {
        return mgr.CreateStmt<Array>(_loc, _Size,_type);
    }

    std::string Array::toString() const {
        std::string str = "";
        str = "[";
        str += Size->toString();
        str += "]";
        str += Ty->toString();
        

        return str;
    }

     GroupedExpr* GroupedExpr::Create(Context &mgr, const StmtLoc *_loc, Ast *_expr) {
        return mgr.CreateStmt<GroupedExpr>(_loc, _expr);
    }

    std::string GroupedExpr::toString() const {
        std::string str = "(";
        str += expr->toString();
        str += ")";
        

        return str;
    }

    FnType* FnType::Create(Context &mgr, const StmtLoc *_loc, const std::vector<Ast *>&_ty, Ast *_ret) {
        return mgr.CreateStmt<FnType>(_loc, _ty,_ret);
    }
    
    std::string FnType::toString() const {
        std::string str = "fn";
        str += "(";
        if(!ty.empty()){
            for(int i = 0 ; i < ty.size(); i++){
                str += ty[i]->toString();
                str += ", ";
            }
        }
        str += ")";
        if(ret){
            str += "->";
            str += ret->toString();
        }
        

        return str;
    }

    PrefixExpr* PrefixExpr::Create(Context &mgr, const StmtLoc *_loc, Tok _op, Ast *_type, bool _Mut, bool _isType) {
        return mgr.CreateStmt<PrefixExpr>(_loc, _op, _type, _Mut, _isType);
    }
    
    std::string PrefixExpr::toString() const {
        std::string str = "";
        switch (op.getTokType())
        {
        case STAR:
            str += "*";
            break;
        case AND:
            str += "&";
            break;
        case MINUS:
            str += "-";
            break;
        case PLUS:
            str += "+";
            break;
        default:
            break;
        }
        // str += TokenMap[op.getTokType()];
        str += base->toString();
        

        return str;
    }
    
    ForLoop* ForLoop::Create(Context &mgr, const StmtLoc *_loc, Ast *_var, Ast *_cond, Ast *_incr, BlockStmt *_body ) {
        return mgr.CreateStmt<ForLoop>(_loc, _var,_cond,_incr,_body);
    }
    
    std::string ForLoop::toString() const {
        std::string str = "for ";
        if(var)
        str += var->toString();
        str += ";";
        if(cond)
        str += cond->toString();
        str += ";";
        if(incr)
        str += incr->toString();
        str += " {\n";
        if(body)
        str += body->toString();
        str += "}\n";
        

        return str;
    }

    WhileLoop* WhileLoop::Create(Context &mgr, const StmtLoc *_loc, Ast *_expr, BlockStmt *_body ) {
        return mgr.CreateStmt<WhileLoop>(_loc, _expr,_body);
    }

    std::string WhileLoop::toString() const {
        std::string str = "while ";
        str += expr->toString();
        str += " {\n";
        str += body->toString();
        str += "}\n";
        

        return str;
    }


    IfStmt* IfStmt::Create(Context &mgr, const StmtLoc *_loc, Ast *_cond , BlockStmt *_ifblock,
                             Ast *_elblock) {
        return mgr.CreateStmt<IfStmt>(_loc,_cond,_ifblock,_elblock);
    }
    
    std::string IfStmt::toString() const {
        std::string str = "if ";
        str += cond->toString();
        str += " {\n";
        str +=  ifblock->toString();
        str += " } ";
        if(elblock){
            str += "else ";
            str += " {\n";
            str += elblock->toString();
            str += " }\n";
        }
        

        return str;
    }

    Extern* Extern::Create(Context &mgr, const StmtLoc *_loc,  const Lexeme &_ID, bool isFn) {
        return mgr.CreateStmt<Extern>(_loc, _ID, isFn);
    }

    std::string Extern::toString() const {
        std::string str = "extern ";
        str += ID.getStr();
        return str;
    }

    Void* Void::Create(Context &mgr, const StmtLoc *_loc) {
        return mgr.CreateStmt<Void>(_loc);
    }

    std::string Void::toString() const {
        return "void";
    }

    BranchStmt* BranchStmt::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_tok) {
        return mgr.CreateStmt<BranchStmt>(_loc, _tok);
    }

    
    std::string BranchStmt::toString() const {
        return tok.getStr() + ";\n";
    }
    
    Expression *Expression::Create(Context &mgr, const StmtLoc *_loc, Ast *_LHS, Tok _op, Ast *_RHS,
                     ExprID _ExprTy) {
        return mgr.CreateStmt<Expression>(_loc, _LHS,_op,_RHS,_ExprTy);
    }
    Expression *Expression::Create(Context &mgr, const StmtLoc *_loc, Ast *_LHS, Ast *_RHS,
                ExprID _ExprTy) {
        return mgr.CreateStmt<Expression>(_loc, _LHS,_RHS,_ExprTy);
    }

    std::string Expression::toString() const {
        std::string str = "";
        str += LHS->toString();
        str += TokenMap[Op.getTokType()];
        str += RHS->toString();
        return str;
    }

    // GenericParam* GenericParam::Create(Context &mgr, const StmtLoc *_loc, std::vector<Ast*> &_memName) {
    //     return mgr.CreateStmt<GenericParam>(_loc, _memName);
    // }

    // std::string GenericParam::toString() const {
    //     std::string str = "<";
    //     if(!Param.empty())
    //         for(int i = 0; i < Param.size(); i++){
    //             if(i)
    //                 str += ", ";
    //             str += Param[i]->toString();
    //         }
    //     str += ">";
        
    //     return str;
    // }

    StructStmt* StructStmt::Create(Context &mgr, const StmtLoc *_loc, const Lexeme &_Ident,
                        std::vector<VarStmt*>&_field) {
        return mgr.CreateStmt<StructStmt>(_loc, _Ident, _field);
    }
    
    std::string StructStmt::toString() const {
        std::string str = "struct ";
        str += Ident.getStr();
        str += "{\n";
        for(int i = 0 ; i < field.size(); i++){
            str += field[i]->getVar().getStr();
            str += ": ";
            str += field[i]->getType()->toString();
            str += ",\n";
        }
        str += " };\n";
        

        return str;
    }

    FieldExpr *FieldExpr::Create(Context &mgr, const StmtLoc *_loc, const std::vector<Ast *>&_args) {
        return mgr.CreateStmt<FieldExpr>(_loc, _args);
    }
    
    std::string FieldExpr::toString() const {
        std::string str = " [ ";
        if(!args.empty())
            for(int i = 0 ; i < args.size(); i++){
                str += args[i]->toString();
                str += ",";
            }
        str += " ] ";
        

        return str;
    }

    FunctionProto* FunctionProto::Create(Context &mgr, const StmtLoc *_Loc, const Lexeme &_Name, const std::vector<VarStmt*> &_Param, Ast *_RetTy) {
        return mgr.CreateStmt<FunctionProto>(_Loc, _Name, _Param, _RetTy);
    }

    FunctionDef* FunctionDef::Create(Context &mgr, const StmtLoc *_Loc, FunctionProto *_FnProto, BlockStmt *_Block) {
        return mgr.CreateStmt<FunctionDef>(_Loc, _FnProto, _Block);
    }

    std::string FunctionProto::toString() const {
        std::string str = "fn ";
        str += Name.getStr();
        str += "(";
        if(!Param.empty()){
         
            for(ssize_t i = 0; i < Param.size(); i++){
                if(i)
                    str += ", ";
                str += Param[i]->getVar().getStr();
                if(Param[i]->getType()){
                    str += Param[i]->getType()->toString();
                }
            }
        }

        str += ") ";
        if(RetTy){
            str += " -> ";
            str += RetTy->toString();
        }

        return str;
    }
    std::string FunctionDef::toString() const {
        std::string str = FuncSig->toString();
        if(Block) {    
            str += " {\n";
            str += Block->toString();
            str += "}\n";
        }

        return str;
    }

     ReturnStmt* ReturnStmt::Create(Context &mgr, const StmtLoc *_loc, Ast *_val) {
        return mgr.CreateStmt<ReturnStmt>(_loc, _val);
    }


    std::string ReturnStmt::toString() const {
        std::string res = "return ";
        if(val)
            res += val->toString();
        res += ";\n";
        return res;
    }


    UserDefinedTy* UserDefinedTy::Create(Context &mgr, const StmtLoc *_loc, Ast* _Expr) {
        return mgr.CreateStmt<UserDefinedTy>(_loc, _Expr);
    }
    std::string UserDefinedTy::toString() const {
        std::string str = Expr->toString();
        // str += Param->toString();
        return str;
    }

    UseStmt* UseStmt::Create(Context &mgr, const StmtLoc *_loc, Ast *_path) {
        return mgr.CreateStmt<UseStmt>(_loc, _path);
    }
    std::string UseStmt::toString() const {
        std::string str = "use ";
        str += path->toString();
        str += ";";
        

        return str;
    }

    Method* Method::Create(Context &mgr, const StmtLoc *_loc, Ast *_Name, Ast *_AssociateTo, std::vector<Ast *>&_impl) {
        return mgr.CreateStmt<Method>(_loc, _Name, _AssociateTo, _impl);
    }
    std::string Method::toString() const {
        std::string str = "method ";
        str += Name->toString();
        str += " {\n";
        for(int i = 0; i < Impl.size(); i++){
            str += Impl[i]->toString();
        }
        str += " }\n";
        

        return str;
    }


    NewStmt *NewStmt::Create(Context &Mgr, const StmtLoc *_loc, Ast *_Ty, Ast *_Size) {
        return Mgr.CreateStmt<NewStmt>(_loc, _Ty, _Size);
    }

    std::string NewStmt::toString() const {
        std::string str = "new";
        str += "(";
        str += Ty->toString();
        str += Size->toString();
        str += ")";
        return str;
    }

    DelStmt *DelStmt::Create(Context &Mgr, const StmtLoc *_loc, Ast *_VPtr) {
        return Mgr.CreateStmt<DelStmt>(_loc, _VPtr);
    }

    std::string DelStmt::toString() const {
        std::string str = "";
        str += "(";
        str += VPtr->toString();
        str += ")";
        return str;
    }
}
