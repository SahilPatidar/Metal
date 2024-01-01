
#include"../../include/ResMgr.hpp"
#include"../../include/parser/Ast.hpp"
// #include"parser/Ast.hpp"

namespace ast {

    NumericLiteral* NumericLiteral::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<NumericLiteral>(_loc, _tok);
    }


    std::string NumericLiteral::toString() const{
        std::cout<<"entring - NumericLiteral"<<__func__<<std::endl;
        return tok.getStr();
    }

    FloatLiteral* FloatLiteral::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<FloatLiteral>(_loc, _tok);
    }

    std::string FloatLiteral::toString() const{
        std::cout<<"entring - FloatLiteral"<<__func__<<std::endl;
        return tok.getStr();
    }

    BoolLiteral* BoolLiteral::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<BoolLiteral>(_loc, _tok);
    }

    std::string BoolLiteral::toString() const {
        std::cout<<"entring - BoolLiteral"<<__func__<<std::endl;
        return tok.getStr();
    }

    StringLiteral* StringLiteral::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok, bool _chr){
        return mgr.CreateStmt<StringLiteral>(_loc, _tok,_chr);
    }

    std::string StringLiteral::toString() const {
        std::cout<<"entring - StringLiteral"<<__func__<<std::endl;
        return tok.getStr();
    }

    NullLiteral* NullLiteral::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok){
        return mgr.CreateStmt<NullLiteral>(_loc, _tok);
    }

    std::string NullLiteral::toString() const {
        std::cout<<"entring - NullLiteral"<<__func__<<std::endl;
        return tok.getStr();
    }


    Identifier* Identifier::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok, bool _isTy) {
        return mgr.CreateStmt<Identifier>(_loc, _tok, _isTy);
    }

    std::string Identifier::toString() const {
        std::cout<<"entring - Identifier;"<<__func__<<std::endl;
        return tok.getStr();
    }

    BlockStmt* BlockStmt::Create(ResourceMgr &mgr, const StmtLoc *_loc,const std::vector<Ast *> &stmts) {
        return mgr.CreateStmt<BlockStmt>(_loc, stmts);
    }

    std::string BlockStmt::toString() const {
        std::cout<<"entring - BlockStmt"<<__func__<<std::endl;
        std::string str = "";
        if(!stmts.empty())
            for(ssize_t i = 0, size = stmts.size(); i < size; i++){
                if(stmts[i] == nullptr){

                std::cout<<"hattttt"<<size<<__func__<<std::endl;
                }
                str += stmts[i]->toString();
                str += "\n";
            }

                std::cout<<"returning - BlockStmt"<<__func__<<std::endl;

        return str;
    }

    EnumExpr *EnumExpr::Create(ResourceMgr &mgr, const StmtLoc *_loc,  const Lexeme &_Name, const std::vector<VarStmt *>&_Evals) {
        return mgr.CreateStmt<EnumExpr>(_loc, _Name, _Evals);
    }

    std::string EnumExpr::toString() const {
        std::cout<<"entring - EnumExpr"<<__func__<<std::endl;
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

        
                std::cout<<"returning - EnumExpr"<<__func__<<std::endl;

        return str;
    }

    PremitiveType* PremitiveType::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok) {
        return mgr.CreateStmt<PremitiveType>(_loc, _tok);
    }

    std::string PremitiveType::toString() const {
        std::cout<<"entring - PreDefineType"<<__func__<<std::endl;
        return tok.getStr();
    }


    VarStmt* VarStmt::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_var, Ast *_type, Ast *_val, int8_t _mask) {
        return mgr.CreateStmt<VarStmt>(_loc, _var, _type, _val, _mask);
    }

    std::string VarStmt::toString() const {
        std::cout<<"entring - VarStmt"<<__func__<<std::endl;
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
        
                std::cout<<"returning - VarStmt"<<__func__<<std::endl;

        return str;
    }

    Array* Array::Create(ResourceMgr &mgr, const StmtLoc *_loc , Ast *_Size, Ast *_type) {
        return mgr.CreateStmt<Array>(_loc, _Size,_type);
    }

    std::string Array::toString() const {
        std::cout<<"entring - Array"<<__func__<<std::endl;
        std::string str = "";
        str = "[";
        str += Size->toString();
        str += "]";
        str += Ty->toString();
        
                std::cout<<"returning - Array"<<__func__<<std::endl;

        return str;
    }

     GroupedExpr* GroupedExpr::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_expr) {
        return mgr.CreateStmt<GroupedExpr>(_loc, _expr);
    }

    std::string GroupedExpr::toString() const {
        std::cout<<"entring - GroupedExpr"<<__func__<<std::endl;
        std::string str = "(";
        str += expr->toString();
        str += ")";
        
                std::cout<<"returning - GroupedExpr"<<__func__<<std::endl;

        return str;
    }

    FnType* FnType::Create(ResourceMgr &mgr, const StmtLoc *_loc, const std::vector<Ast *>&_ty, Ast *_ret) {
        return mgr.CreateStmt<FnType>(_loc, _ty,_ret);
    }
    
    std::string FnType::toString() const {
        std::cout<<"entring - FnType"<<__func__<<std::endl;
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
        
                std::cout<<"returning - FnType"<<__func__<<std::endl;

        return str;
    }

    PrefixExpr* PrefixExpr::Create(ResourceMgr &mgr, const StmtLoc *_loc, Tok _op, Ast *_type, bool _Mut, bool _isType) {
        return mgr.CreateStmt<PrefixExpr>(_loc, _op, _type, _Mut, _isType);
    }
    
    std::string PrefixExpr::toString() const {
        std::cout<<"entring - PrefixExpr"<<__func__<<std::endl;
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
        // str += lex::TokenMap[op.getTokType()];
        str += base->toString();
        
                std::cout<<"returning - PrefixExpr"<<__func__<<std::endl;

        return str;
    }
    
    ForLoop* ForLoop::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_var, Ast *_cond, Ast *_incr, BlockStmt *_body ) {
        return mgr.CreateStmt<ForLoop>(_loc, _var,_cond,_incr,_body);
    }
    
    std::string ForLoop::toString() const {
        std::cout<<"entring - ForLoop"<<__func__<<std::endl;
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
        
                std::cout<<"returning - ForLoop"<<__func__<<std::endl;

        return str;
    }

    WhileLoop* WhileLoop::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_expr, BlockStmt *_body ) {
        return mgr.CreateStmt<WhileLoop>(_loc, _expr,_body);
    }

    std::string WhileLoop::toString() const {
        std::cout<<"entring - WhileLoop"<<__func__<<std::endl;
        std::string str = "while ";
        str += expr->toString();
        str += " {\n";
        str += body->toString();
        str += "}\n";
        
                std::cout<<"returning - WhileLoop"<<__func__<<std::endl;

        return str;
    }


    IfStmt* IfStmt::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_cond , BlockStmt *_ifblock,
                             Ast *_elblock) {
        return mgr.CreateStmt<IfStmt>(_loc,_cond,_ifblock,_elblock);
    }
    
    std::string IfStmt::toString() const {
        std::cout<<"entring - IfStmt"<<__func__<<std::endl;
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
        
                std::cout<<"returning - IfStmt"<<__func__<<std::endl;

        return str;
    }

    Extern* Extern::Create(ResourceMgr &mgr, const StmtLoc *_loc,  const Lexeme &_ID, bool isFn) {
        return mgr.CreateStmt<Extern>(_loc, _ID, isFn);
    }

    std::string Extern::toString() const {
        std::string str = "extern ";
        str += ID.getStr();
        return str;
    }

    Void* Void::Create(ResourceMgr &mgr, const StmtLoc *_loc) {
        return mgr.CreateStmt<Void>(_loc);
    }

    std::string Void::toString() const {
        return "void";
    }

    BranchStmt* BranchStmt::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_tok) {
        return mgr.CreateStmt<BranchStmt>(_loc, _tok);
    }

    
    std::string BranchStmt::toString() const {
        std::cout<<"entring - BranchStmt"<<__func__<<std::endl;
        return tok.getStr() + ";\n";
    }
    
    Expression *Expression::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_LHS, Tok _op, Ast *_RHS,
                     KExpr _Kexpr) {
        return mgr.CreateStmt<Expression>(_loc, _LHS,_op,_RHS,_Kexpr);
    }
    Expression *Expression::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_LHS, Ast *_RHS,
                KExpr _Kexpr) {
        return mgr.CreateStmt<Expression>(_loc, _LHS,_RHS,_Kexpr);
    }

    std::string Expression::toString() const {
        std::cout<<"entring - Expression"<<__func__<<std::endl;
        std::string str = "";
        str += LHS->toString();
        str += lex::TokenMap[Op.getTokType()];
        str += RHS->toString();
        std::cout<<"returning - Expression"<<__func__<<std::endl;
        return str;
    }

    // GenericParam* GenericParam::Create(ResourceMgr &mgr, const StmtLoc *_loc, std::vector<Ast*> &_memName) {
    //     return mgr.CreateStmt<GenericParam>(_loc, _memName);
    // }

    // std::string GenericParam::toString() const {
    //     std::cout<<"entring - GenericParam"<<__func__<<std::endl;
    //     std::string str = "<";
    //     if(!Param.empty())
    //         for(int i = 0; i < Param.size(); i++){
    //             if(i)
    //                 str += ", ";
    //             str += Param[i]->toString();
    //         }
    //     str += ">";
        
    //     std::cout<<"returning - GenericParam"<<__func__<<std::endl;
    //     return str;
    // }

    StructStmt* StructStmt::Create(ResourceMgr &mgr, const StmtLoc *_loc, const Lexeme &_Ident,
                        std::vector<VarStmt*>&_field) {
        return mgr.CreateStmt<StructStmt>(_loc, _Ident, _field);
    }
    
    std::string StructStmt::toString() const {
        std::cout<<"entring - StructStmt"<<__func__<<std::endl;
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
        
                std::cout<<"returning - StructStmt"<<__func__<<std::endl;

        return str;
    }

    FieldExpr *FieldExpr::Create(ResourceMgr &mgr, const StmtLoc *_loc, const std::vector<Ast *>&_args) {
        return mgr.CreateStmt<FieldExpr>(_loc, _args);
    }
    
    std::string FieldExpr::toString() const {
        std::cout<<"entring - ListExpr"<<__func__<<std::endl;
        std::string str = " [ ";
        if(!args.empty())
            for(int i = 0 ; i < args.size(); i++){
                str += args[i]->toString();
                str += ",";
            }
        str += " ] ";
        
                std::cout<<"returning - ListExpr"<<__func__<<std::endl;

        return str;
    }

    FunctionProto* FunctionProto::Create(ResourceMgr &mgr, const StmtLoc *_Loc, const Lexeme &_Name, const std::vector<VarStmt*> &_Param, Ast *_RetTy) {
        return mgr.CreateStmt<FunctionProto>(_Loc, _Name, _Param, _RetTy);
    }

    FunctionDef* FunctionDef::Create(ResourceMgr &mgr, const StmtLoc *_Loc, FunctionProto *_FnProto, BlockStmt *_Block) {
        return mgr.CreateStmt<FunctionDef>(_Loc, _FnProto, _Block);
    }

    std::string FunctionProto::toString() const {
        std::cout<<"entring - Functionproto"<<__func__<<std::endl;
        std::string str = "fn ";
        str += Name.getStr();
        str += "(";
        if(!Param.empty()){
         
            for(ssize_t i = 0; i < Param.size(); i++){
                if(i)
                    str += ", ";
                str += Param[i]->getVar().getStr();
                if(Param[i]->getType()){
                    str += ": ";
                    str += Param[i]->getType()->toString();
                }
            }
        }

        str += ") ";
        if(RetTy){
            str += " -> ";
            str += RetTy->toString();
        }
                std::cout<<"returning - Functionproto"<<__func__<<std::endl;

        return str;
    }
    std::string FunctionDef::toString() const {
        std::cout<<"entring - FunctionDef"<<__func__<<std::endl;
        std::string str = FuncSig->toString();
        if(Block) {    
            str += " {\n";
            str += Block->toString();
            str += "}\n";
        }
            std::cout<<"returning - FunctionDef"<<__func__<<std::endl;

        return str;
    }

     ReturnStmt* ReturnStmt::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_val) {
        return mgr.CreateStmt<ReturnStmt>(_loc, _val);
    }


    std::string ReturnStmt::toString() const {
        std::cout<<"entring - ReturnStmt"<<__func__<<std::endl;
        std::string res = "return ";
        if(val)
            res += val->toString();
        res += ";\n";
        std::cout<<"returing - ReturnStmt"<<__func__<<std::endl;
        return res;
    }


    UserDefinedTy* UserDefinedTy::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast* _Expr) {
        return mgr.CreateStmt<UserDefinedTy>(_loc, _Expr);
    }
    std::string UserDefinedTy::toString() const {
        std::cout<<"entring - UserDefinedTy"<<__func__<<std::endl;
        std::string str = Expr->toString();
        // str += Param->toString();
        std::cout<<"returning - UserDefinedTy"<<__func__<<std::endl;
        return str;
    }

    UseStmt* UseStmt::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_path) {
        return mgr.CreateStmt<UseStmt>(_loc, _path);
    }
    std::string UseStmt::toString() const {
        std::cout<<"entring - UseStmt"<<__func__<<std::endl;
        std::string str = "use ";
        str += path->toString();
        str += ";";
        
                std::cout<<"returning - UseStmt"<<__func__<<std::endl;

        return str;
    }

    Method* Method::Create(ResourceMgr &mgr, const StmtLoc *_loc, Ast *_Name, Ast *_AssociateTo, std::vector<Ast *>&_impl) {
        return mgr.CreateStmt<Method>(_loc, _Name, _AssociateTo, _impl);
    }
    std::string Method::toString() const {
        std::cout<<"entring - Method"<<__func__<<std::endl;
        std::string str = "method ";
        str += Name->toString();
        str += " {\n";
        for(int i = 0; i < Impl.size(); i++){
            str += Impl[i]->toString();
        }
        str += " }\n";
        
                std::cout<<"returning - Method"<<__func__<<std::endl;

        return str;
    }


    NewStmt *NewStmt::Create(ResourceMgr &Mgr, const StmtLoc *_loc, Ast *_Ty, Ast *_Size) {
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

    DelStmt *DelStmt::Create(ResourceMgr &Mgr, const StmtLoc *_loc, Ast *_VPtr) {
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
