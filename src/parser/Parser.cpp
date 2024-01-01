
#include"../../include/parser/Parser.hpp"
#include"../../include/parser/Ast.hpp"
#include"../../include/Module.hpp"
#include"../../include/Error.hpp"
// #include"parser/Parser.hpp"
// #include"Error.hpp"

namespace parser
{
using namespace ast;

bool Parser::parse(Ast *&tree) {
    ParserHelper P(modctx->getLexeme());
    P.dump(__func__);
    BlockStmt *stmts = nullptr;
    if(!ParseBlock(P, stmts, true)){
        return false;
    }
    tree = stmts;
    std::vector<Ast *> &Stmts = static_cast<BlockStmt *>(stmts)->getStmts();
    for(Ast *&S :Stmts){
        std::string stmtId = "";
        std::cout<<S->getStmtTy()<<std::endl;
        switch(S->getStmtTy()) {
        case NodeStructStm: stmtId = static_cast<StructStmt *>(S)->getName().getStr(); break;
        case NodeFNStm: stmtId = static_cast<FunctionDef *>(S)->getFnProto()->getFuncName().getStr(); break;
        case NodeVarStm: stmtId = static_cast<VarStmt *>(S)->getVar().getStr(); break;
        case NodeEnum: stmtId = static_cast<EnumExpr *>(S)->getName().getStr(); break;
        case NodeExtern: stmtId = static_cast<Extern *>(S)->getID().getStr(); break;
        default:
            break;
        } 
        std::cout<<stmtId<<std::endl;
        if(stmtId.empty()){
            continue;
        }   
        modctx->insertModItem(stmtId, &S);
    }
    P.dump2(__func__);
    return true;
}

bool Parser::ParseBlock(ParserHelper &P, BlockStmt *&ResNode, bool IsTop){
    P.dump(__func__);
    std::vector<Ast*>stmts;
    Lexeme &tok = P.peek_l();
    ResNode = nullptr;
    Ast *stmt = nullptr;
    while(!P.check(FEOF)&&!P.check(RBRACE)) {
        bool isSemiCol = false;        
        switch(P.peek_tt()) {
        case EXTERN:
        {
            if(!ParseExtern(P, stmt)){ return false; }
            isSemiCol = true;
        }
            break;
        case DEL:
        {
            if(!ParseDelStmt(P, stmt)){ return false; }
            isSemiCol = true;
        }
            break;
        case IF:
            if(!ParseIfStmt(P, stmt)){ return false; }
            break;
        case FOR:
            if(P.checkNH(IN, 2)){
                if(!ParseForInStmt(P, stmt)) { return false; }
            }else{
                if(!ParseForStmt(P, stmt)) { return false; }
            }
            break;
        case FN:
        {
            if(!ParseFuncDef(P, stmt)){
                return false;
            }
        }
            break;
        case LET:
        case CONST:
        {
            if(!ParseVarStmt(P, stmt)){ return false; }
            if(IsTop)
                static_cast<VarStmt *>(stmt)->setGVar();
            isSemiCol = true;
        }
            break;
        case STRUCT:
            if(!ParseStructStmt(P, stmt)){ return false;} 
            break;
        case METHOD:
        {
            if(!ParseMethod(P, stmt)){
                return false;
            }
        }
            break;
        case ENUM:
        {
            if(!ParseEnumStmt(P, stmt)){
                return false;
            }
        }
            break;
        case MOD:
        {
            if(!ParseMod(P, stmt)){ return false; }
            continue;
        }
        break;
        case WHILE:
            if(!ParseWhileStmt(P, stmt)){ return false; }
            break;
            break;
        case RETURN:
            if(!ParseReturnStmt(P, stmt)){ return false; }
            isSemiCol = true;
            break;

        case CONTINUE:
        case BREAK:
        {
            Lexeme &tok = P.peek_l();
            stmt = BranchStmt::Create(mgr, tok.getLoc(), P.peek_l());
            P.next();
            isSemiCol = true;
        }
            break;
        case USE:
            if(!ParseUseStmt(P, stmt)) { return false;}
            isSemiCol = true;
            break;
        
        default:
            if(IsTop) {
                err::err_out(P.peek_l().getLoc(), "invalid global stmt");
                return false;
            }
            if(!ParseExpr(P, stmt)) { return false;}
            isSemiCol = true;
            break;
        }

        if(isSemiCol&&!P.checkn(SCOL)){
            err::err_out(P.peek_l().getLoc(), "expected ';' found - ", P.peek_l().getStr());
            return false;
        }
        if(!isSemiCol&&P.check(SCOL)){
            err::err_out(P.peek_l().getLoc(), "unexpected ';' found - ", P.peek_l().getStr());
            return false;
        }
        stmts.push_back(stmt);
    }

    ResNode = BlockStmt::Create(mgr, tok.getLoc(), stmts);
    P.dump2(__func__);
    return true;
}


bool Parser::ParseNewStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &Tok = P.peek_l();
    if(!P.checkn(NEW)) {
        err::err_out(P.peek_l().getLoc(), "expected 'new' found - ", P.peek_l().getStr());
        return false;
    }
    if(!P.checkn(LPAREN)) {
        err::err_out(P.peek_l().getLoc(), "expected '(' found - ", P.peek_l().getStr());
        return false;
    }

    if(P.check(RPAREN)) {
        err::err_out(P.peek_l().getLoc(), "expected 'expression' found - ", P.peek_l().getStr());
        return false;
    }
    Ast *Expr = nullptr;
    if(!ParseExpr(P, Expr)){
        return false;
    }

    if(!P.checkn(COMMA)) {
        err::err_out(P.peek_l().getLoc(), "expected ',' found - ", P.peek_l().getStr());
        return false;
    }

    Ast *Ty = nullptr;
    if(!ParseType(P, Ty)){
        return false;
    }

    if(!P.checkn(RPAREN)) {
        err::err_out(P.peek_l().getLoc(), "expected '(' found - ", P.peek_l().getStr());
        return false;
    }

    ResNode = NewStmt::Create(mgr, Tok.getLoc(), Ty, Expr);
    P.dump2(__func__);
    return true;
}

bool Parser::ParseDelStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &Tok = P.peek_l();
    if(!P.checkn(DEL)) {
        err::err_out(P.peek_l().getLoc(), "expected 'del' found - ", P.peek_l().getStr());
        return false;
    }

    if(!P.checkn(LPAREN)) {
        err::err_out(P.peek_l().getLoc(), "expected '(' found - ", P.peek_l().getStr());
        return false;
    }

    if(P.check(RPAREN)) {
        err::err_out(P.peek_l().getLoc(), "expected 'expression' found - ", P.peek_l().getStr());
        return false;
    }
    Ast *Expr = nullptr;
    if(!ParseExpr(P, Expr)){
        return false;
    }

    if(!P.checkn(RPAREN)) {
        err::err_out(P.peek_l().getLoc(), "expected '(' found - ", P.peek_l().getStr());
        return false;
    }

    ResNode = DelStmt::Create(mgr, Tok.getLoc(), Expr);
    P.dump2(__func__);
    return true;
}

bool Parser::ParseSubBlock(ParserHelper &P, BlockStmt *&ResNode) {
    P.dump(__func__);
    if(!P.checkn(LBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected '{' found - ", P.peek_l().getStr());
        return false;
    }
    if(!ParseBlock(P,ResNode)){
        return false;
    }
    if(!P.checkn(RBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected '}' found - ", P.peek_l().getStr());
        return false;
    }
        P.dump2(__func__);

    return true;
}

bool Parser::ParseUseStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    P.next();
    Ast *ident = nullptr;
    Ast *path = nullptr;

    if(!ParsePath(P,path)) {
        return false;
    }
    if(!path){
        err::err_out(P.peek_l().getLoc(), "expected {ident::ident} found");
        return false;
    }


    if(P.checkn(AS)) {
        if(!P.check(IDEN)||!ParseIdentifier(P,ident)) {
            return false;
        }

        path = Expression::Create(mgr, tok.getLoc(), path, ident, KAsExpr);
    }



    ResNode = UseStmt::Create(mgr, tok.getLoc(), path);
        P.dump2(__func__);

    return true;
}


bool Parser::ParseMod(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    P.next();
    if(!P.check(IDEN)) {
        err::err_out(P.peek_l().getLoc(), "expected `mod identifier` found");
        return false;
    }

    // ModuleInfo modinfo = {};
    // if(!CreateModInfoByMod(path, P.peek_l().getStr(), modinfo)){
    //     ///@todo
    //     return false;
    // }
    Module *M = ModuleHelper::CreateMod(mgr, P.peek_l().getStr(), modctx);
    ModuleHelper MH(M);
    if(M == nullptr){
        err::err_out(P.peek_l().getLoc(), "mod aleardy build - ");
        return false;
    }
    if(!MH.LexSrc(mgr)){
        return false;
    }
    if(!MH.ParseToken(mgr)){
        return false;
    }
        P.dump2(__func__);
    P.next();
    if(!P.checkn(SCOL)){
        err::err_out(P.peek_l().getLoc(), "expected ';' found - ", P.peek_l().getStr());
        return false;
    }
    return true;
}

bool Parser::ParsePath(ParserHelper &P, Ast *&ResNode){
    P.dump(__func__);
    Lexeme &tok = P.peek_l();
    Ast* lhs = nullptr;
    if(!P.check(IDEN)||!ParseIdentifier(P, lhs)){
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found");
        return false;
    }
    Ast *rhs = nullptr;
    ResNode = nullptr;
    while(P.check(COLCOL)){
        Lexeme &op = P.peek_l();
        P.next();
        if(P.check(COL)&&P.checkh(LT)){
            break;
        }
        if(!P.check(IDEN)||!ParseIdentifier(P, rhs)){
            err::err_out(P.peek_l().getLoc(), "expected 'identifier' found");
            return false;
        }
        if(rhs == nullptr) {
            err::err_out(P.peek_l().getLoc(), "invalid expression");
            return false;
        }
        lhs = Expression::Create(mgr, op.getLoc(), lhs, op.getTok(), rhs, KPathExpr);
        rhs = nullptr;
    }
    ResNode = lhs;
    P.dump2(__func__);
    return true;
}


bool Parser::ParseMethod(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    Ast* Assoc = nullptr;
    std::vector<Ast*> Impl;
    P.next();
    if(!P.check(IDEN)){
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' with method statement found - ", P.peek_l().getStr());
        return false;
    }
    
    Ast* Ty = nullptr;
    if(!ParseType(P,Ty)){
        return false;
    }

    if(!P.checkn(LBRACE)) {
        err::err_out(P.peek_l().getLoc(), "expected '{' found - ", P.peek_l().getStr());
        return false;
    }

    if(!P.check(FN)) {
        err::err_out(P.peek_l().getLoc(), "expected 'fn' found - ", P.peek_l().getStr());
        return false;
    }

    while(P.check(FN)) {
        Ast* fn = nullptr;
        if(!ParseFuncDef(P, fn)) {
            return false;
        }
        Impl.push_back(fn);
    }

    if(!P.checkn(RBRACE)) {
        err::err_out(P.peek_l().getLoc(), "expected '}' found - ", P.peek_l().getStr());
        return false;
    }
    ResNode = Method::Create(mgr, tok.getLoc(), Ty, Assoc, Impl);
        P.dump2(__func__);

    return true;
}


bool Parser::ParseWhileStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    Ast* Cond = nullptr;
    BlockStmt* Blk = nullptr;
    P.next();
    if(P.check(LBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected condition expression found - ", P.peek_l().getStr());
        return false;
    }
    if(!ParseExpr(P, Cond)) {
        return false;
    }
    if(!ParseSubBlock(P,Blk)){
        return false;
    }
    ResNode = WhileLoop::Create(mgr, tok.getLoc(), Cond, Blk);
        P.dump2(__func__);

    return true;
}


bool Parser::ParseReturnStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    Lexeme &tok = P.peek_l();
    Ast* val = nullptr;
    P.next();

    if(!P.check(SCOL)){
        if(!ParseExpr(P, val)) {
            return false;
        }
    }
    ResNode = ReturnStmt::Create(mgr, tok.getLoc(), val);
    P.dump2(__func__);

    return true;
}


bool Parser::ParseType(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    bool variadic = false;
    Ast* type = nullptr;
    Lexeme &tok = P.peek_l();
    if(P.checkn(DOTDOT)) {
        variadic = true;
    }
    switch(P.peek_tt()){
        case LBRACK:
            if(!ParseArrayType(P,type)){
                return false;
            }
            break;
        case I8:
        case I16:
        case I32:
        case I64:
        case UI8:
        case UI16:
        case UI32:
        case UI64:
        case F32:
        case F64:
        case BOOL:
        {   
            type = PremitiveType::Create(mgr, tok.getLoc(), P.peek_l());
            P.next();
            break;
        }
        case FN:
        {
            P.next();
            if(!P.check(LPAREN)){
                err::err_out(P.peek_l().getLoc(), "expected '{' found - ", P.peek_l().getStr());
                return false;
            }else{
                P.next();
                std::vector<Ast*>tys;
                while(!P.check(RPAREN)){
                    Ast* ty = nullptr;
                    if(!ParseType(P,ty)) {
                        return false;
                    }
                    tys.push_back(ty);
                    if(!P.checkn(COMMA)) {
                        break;
                    }
                }
                if(!P.checkn(RPAREN)) {
                    err::err_out(P.peek_l().getLoc(), "expected ')' found - ", P.peek_l().getStr());
                    return false;
                }
                Ast* ret = nullptr;
                if(P.checkn(ARROW)){
                    if(ParseType(P, ret)){
                        ret = ret;
                    }
                }
                type = FnType::Create(mgr, tok.getLoc(), tys, ret);

            }
        }
            break;
        case IDEN:
        {
            if(!ParseSpecificType(P,type)){
                return false;
            }
            break;
        }
        case STAR:
        {
            bool isType  = true;
            Tok op = P.peek_t();
            P.next();
            bool mut = false;
            if(P.checkn(MUT)){
                mut = true;
            }else if(P.checkn(CONST)){
                mut = false;
            }else{
                err::err_out(P.peek_l().getLoc(), "expected {'const', 'mut'} found ->");
                return false;
            }

            if(!ParseType(P,type)){
                return false;
            }
            type = PrefixExpr::Create(mgr, tok.getLoc(), op, type, mut, isType);
        }
            break;
        break;
        default:
            err::err_out(P.peek_l().getLoc(), "expected '{type, i8, i32, ...}' found -");
            return false;
    }
    ResNode = type;
            P.dump2(__func__);
    return true;
}


bool Parser::ParseArrayType(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Ast *basety = nullptr;
    Lexeme &tok = P.peek_l();
    Ast *size;
    P.next();
    if(P.check(RBRACK)) {
        err::err_out(P.peek_l().getLoc(), "expected ']' found ->");
        return false;
    }
    if(!P.check(IDEN)&&!P.check(INT)) {
        err::err_out(P.peek_l().getLoc(), "expected expression found -");
        return false;
    }
    if(!ParseExpr(P, size)) {
        return false;
    }
    if(!P.checkn(RBRACK)) {
        err::err_out(P.peek_l().getLoc(), "expected ']' found ->");
        return false;
    }
    if(!ParseType(P,basety)){
        return false;
    }
    ResNode = Array::Create(mgr, tok.getLoc(), size, basety);
        P.dump2(__func__);

    return true;
}


bool Parser::ParseCall(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    Lexeme &tok = P.peek_l();
    ResNode = nullptr;
    std::vector<Ast*>args;

    if(!P.checkn(LPAREN)){
        err::err_out(P.peek_l().getLoc(), "expected '(' found - ", P.peek_l().getStr());
        return false;
    }

    while(!P.check(FEOF)&&!P.check(RPAREN)){
        Ast *expr = nullptr;
        if(!ParseExpr(P, expr)) {
            return false;
        }

        args.push_back(expr);
        if(!args.back()){
            return false;
        }

        if(!P.checkn(COMMA)) {
            break;
        }
    }

    if(!P.checkn(RPAREN)){
        err::err_out(P.peek_l().getLoc(), "expected ')' found - ", P.peek_l().getStr());
        return false;
    }
    ResNode = FieldExpr::Create(mgr, tok.getLoc(), args);
        P.dump2(__func__);

    return true;
}


bool Parser::ParseListExpr(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    P.next();
    std::vector<Ast*>List;
    while(!P.check(RBRACK)) {
        Ast *expr = nullptr;
        if(!ParseExpr(P, expr)){
            return false;
        }
        List.push_back(expr);
        if(!P.checkn(COMMA)){
            break;
        }
    }
    if(!P.checkn(RBRACK)){
        err::err_out(P.peek_l().getLoc(), "expected ']' found - ", P.peek_l().getStr());
        return false;
    }
    ResNode = FieldExpr::Create(mgr, tok.getLoc(), List);
        P.dump2(__func__);

    return true;
}


bool Parser::ParseExpr(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    int Precedance = 0;
    if(!ParseExpr1(P,ResNode,Precedance)){
        return false;
    }
        P.dump2(__func__);

    return true;
}


bool Parser::ParseExpr1(ParserHelper &P, Ast *&ResNode, int Precedance) { 
    P.dump(__func__);
    ResNode = nullptr;
    Ast* left = nullptr;
    Ast* right = nullptr;
    if(!ParseExpr2(P,left)){
        return false;
    }

    Lexeme &tok = P.peek_l();
    while(P.isBinaryOpr()||P.isAssnCombinedOpr()||P.check(ASN)) {
        Tok opr = P.peek_t();
        int CurPrecedance = P.preced(opr.getTokType());
        if(Precedance > CurPrecedance) {
            ResNode = left;
            return true;
        }
        P.next();
        if(!P.isAssnCombinedOpr()&&!P.check(ASN)) {
            CurPrecedance++;
        }
        if(!ParseExpr1(P, right, CurPrecedance)){
            return false;
        }
        if(right == nullptr){
            err::err_out(P.peek_l().getLoc(), "invalid expression - ");
            return false;
        }
        left = Expression::Create(mgr, tok.getLoc(), left, opr, right, KBinaryExpr);
        right = nullptr;
    }
    ResNode = left;
        P.dump2(__func__);
    return true;
}



bool Parser::ParseExpr2(ParserHelper &P, Ast *&ResNode) { 
    P.dump(__func__);
    Ast* LHS = nullptr;
    Ast* RHS = nullptr;
    ResNode = nullptr;
    if(!ParseExpr3(P, LHS)){
        return false;
    }
    Lexeme &tok = P.peek_l();
    if(P.check(IS)) {
         if(!LHS){
            err::err_out(P.peek_l().getLoc(), "invalid expression - ");
            return false;
        }
        Tok op = P.peek_t();
        P.next();
        if(!ParseType(P, RHS)){
            return false;
        }
        if(RHS == nullptr) {
            err::err_out(P.peek_l().getLoc(), "invalid expression");
            return false;
        }
        LHS = Expression::Create(mgr, tok.getLoc(), LHS, op, RHS, KIsExpr);
    }
    if(P.check(AS)) {
         if(!LHS){
            err::err_out(P.peek_l().getLoc(), "invalid expression - ");
            return false;
        }
        Tok op = P.peek_t();
        while(P.checkn(AS)){
            RHS = nullptr;
            if(!ParseType(P, RHS)){
                return false;
            }
            if(RHS == nullptr) {
                err::err_out(P.peek_l().getLoc(), "invalid expression");
                return false;
            }
            LHS = Expression::Create(mgr, tok.getLoc(), LHS,op,RHS, KAsExpr);
        }
    }
    ResNode = LHS;

        P.dump2(__func__);

    return true;
}


bool Parser::ParseExpr3(ParserHelper &P, Ast *&ResNode) { 
    P.dump(__func__);
    Lexeme &tok = P.peek_l();
    ResNode = nullptr;
    Ast* RHS = nullptr;
    int defCount = 0;
    std::vector<Lexeme>opr;
    while(P.isUnaryOpr()){
        opr.push_back(P.peek_l());
        if(P.check(AND)&&P.checkh(MUT)) {
            P.next();
            opr.push_back(P.peek_l());
        }
        P.next();
    }
    if(!ParseExpression(P, RHS)) {
        return false;
    }
    if(!RHS){
        err::err_out(P.peek_l().getLoc(), "invalid expression - ");
		return false;
    }
    if(opr.empty()){
        goto end;
    }

    if(RHS->getStmtTy() == NodeNumLit) {
        NumericLiteral *t = static_cast<NumericLiteral*>(RHS);
        while(!opr.empty() && (opr.front().getTokTy() == MINUS)){
            t->getLexeme().setDataInt(-t->getLexeme().getDataInt());
            opr.erase(opr.begin());
        }
    }else if(RHS->getStmtTy() == NodeFloatLit) { 
        FloatLiteral *t = static_cast<FloatLiteral*>(RHS);
        while(!opr.empty() && opr.front().getTokTy() == MINUS){
            t->getLexeme().setDataFlt(-t->getLexeme().getDataFlt());
            opr.erase(opr.begin());
        }
    }
    for(int i = 0, size = opr.size(); i < size; i++){
        if(opr[i].getTokTy() == AND){
            bool mut = false;
            Tok tok = opr[i].getTok();
            if(i + 1 < size && opr[i+1].getTokTy() == MUT) {
                mut = true;
                i++;
            }
            RHS = PrefixExpr::Create(mgr, opr[i].getLoc(), tok, RHS, mut, false);
            continue;
        }
        RHS = PrefixExpr::Create(mgr, opr[i].getLoc(), opr[i].getTok(), RHS, false, false);
    }

end:
    ResNode = RHS;
    P.dump2(__func__);

    return true;
}

bool Parser::ParseExtern(ParserHelper &P, Ast *&ResNode) {
    Lexeme &Tok = P.peek_l();
    P.next();
    bool isFn = P.check(FN);
    if(!P.checkn(FN) && !P.checkn(STRUCT)) {
        err::err_out(P.peek_l().getLoc(), "expected '{fn, struct}' found - ", P.peek_l().getStr());
        return false;
    }
    if(!P.check(IDEN)) {
        err::err_out(P.peek_l().getLoc(), "expected 'Identifier' found - ", P.peek_l().getStr());
        return false;
    }
    Lexeme &L = P.peek_l();
    P.next();
    ResNode = Extern::Create(mgr, Tok.getLoc(), L, isFn);
    return true;
}

bool Parser::ParseExtFnCall(ParserHelper &P, Ast *&ResNode) {
    Lexeme &tok = P.peek_l();
    ResNode = nullptr;
    Ast *Ident = nullptr;
    Ast *Field = nullptr;
    
    bool isszof = false;
    if(tok.getStr() == "szof") {
        isszof = true;
    }
    if(!ParseIdentifier(P, Ident)) {
        return false;
    }

    if(isszof)  {
        P.next();
        Ast *Ty = nullptr;
        if(!ParseType(P, Ty)){
            return false;
        }
        P.next();
        Field = FieldExpr::Create(mgr, P.peek_l().getLoc(), {Ty});
    }else
        if(!ParseCall(P, Field)) {
            return false;
        }

    ResNode = Expression::Create(mgr, tok.getLoc(), Ident, Field, KExtCallExpr);
    return true;
}

bool Parser::ParseExpression(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    Lexeme &tok = P.peek_l();
    ResNode = nullptr;
    Ast *lhs = nullptr;
    Ast *rhs = nullptr;
    if(P.check(NEW)) {
        if(!ParseNewStmt(P, lhs)) { 
            return false; 
        }
        goto end;
    }
    if(P.checkn(AT)) {
        if(!ParseExtFnCall(P, lhs)) {
            return false;
        } 
        goto end;
    }
    if(P.check(IDEN)||P.check(SELF)) {
        goto ident;
    }
    if(P.check(LBRACK)) {
        if(!ParseListExpr(P,lhs)){
            return false;
        }
    }else if(P.check(LPAREN)) {
        if(!ParseParenExpr(P,lhs)) {
            return false;
        }
        goto dot_arrow;
    }else if(P.peek_t().isLiteral()){
        if(!ParseLiteral(P,lhs)){
            return false;
        }
    }
    goto end;
ident:
    if(!ParseIdentifier(P,lhs)){
        return false;
    }

    if(!P.check(COLCOL)){
        goto struct_init;
    }

    while(P.check(COLCOL)) {
        Tok opr = P.peek_t();
        P.next();
        if(!P.check(IDEN)){
            err::err_out(P.peek_l().getLoc(), "expected 'identifier' found - ", P.peek_l().getStr());
            return false;
        }
        if(!ParseIdentifier(P,rhs)){
            return false;
        }
        lhs = Expression::Create(mgr, tok.getLoc(), lhs, opr, rhs, KPathExpr);
        rhs = nullptr;
    }

struct_init:
    if(!((P.check(COL)&&P.checkh(LT))||(P.check(LBRACE)&&P.checkh(IDEN)&&P.checkNH(COL,2)))) {
        goto dot_arrow;
    }
    if(lhs == nullptr || (lhs->getStmtTy() != NodeIdent && lhs->getStmtTy() != NodeExpr)) {
        err::err_out(P.peek_l().getLoc(), "invalid expression");
        return false;
    }
    if(P.check(COL))
        P.next();
        
    if(!ParseStructExpr(P,rhs)) {
        return false;
    }
    lhs = Expression::Create(mgr, tok.getLoc(),lhs, rhs, KStructExpr);
    rhs = nullptr;
    goto end;

dot_arrow:
    if(!P.check(DOT)&&!P.check(ARROW)){
        goto call_or_idx;
    }
    while(P.check(DOT)||P.check(ARROW)) {
        Tok opr = P.peek_t();
        P.next();
        if(!ParseIdentifier(P,rhs)){
            return false;
        }
        lhs = Expression::Create(mgr, tok.getLoc(), lhs, opr, rhs, KMemExpr);
        rhs = nullptr;
    }


call_or_idx:
    if(!P.check(LPAREN)&&!P.check(LBRACK)){
        goto end;
    }

    if(P.check(LPAREN)){
        if(!ParseCall(P,rhs)) {
            return false;
        }
        lhs = Expression::Create(mgr, tok.getLoc(),lhs, rhs, KCallExpr);
    }

    while(P.check(LBRACK)){
        if(!ParseArrayIndexExpr(P,rhs)){
            return false;
        }
        lhs = Expression::Create(mgr, tok.getLoc(),lhs, rhs, KIndexExpr);
    }
 
    if(P.check(DOT)||P.check(ARROW)){
        goto dot_arrow;
    }
end:
    ResNode = lhs;
    P.dump2(__func__);
    return true;
}


bool Parser::ParseLiteral(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    switch (P.peek_tt())
    {
    case INT:
        ResNode = NumericLiteral::Create(mgr, tok.getLoc(), P.peek_l());
        break;
    case FLOAT:
        ResNode = FloatLiteral::Create(mgr, tok.getLoc(), P.peek_l());
        break;
    case STR:
        ResNode = StringLiteral::Create(mgr, tok.getLoc(), P.peek_l(), false);
        break;
    case CHAR:
        ResNode = StringLiteral::Create(mgr, tok.getLoc(), P.peek_l(), true);
        break;
    case TRUE:
    case FALSE:
        ResNode = BoolLiteral::Create(mgr, tok.getLoc(), P.peek_l());
        break;
    case NIL:
        ResNode = NullLiteral::Create(mgr, tok.getLoc(), P.peek_l());
        break;
    default:
        err::err_out(P.peek_l().getLoc(), "expected literal found - ", P.peek_l().getStr());
        return false;
    }
    P.next();
        P.dump2(__func__);

    return true;
}

bool Parser::ParseParenExpr(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    P.next();
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    Ast* expr = nullptr;
    if(P.check(RPAREN)){
        err::err_out(P.peek_l().getLoc(), "expected expression found - ", P.peek_l().getStr());
        return false;
    }
    if(!ParseExpr(P, expr)){
        return false;
    }

    if(!P.checkn(RPAREN)){
        err::err_out(P.peek_l().getLoc(), "expected ')' found - ", P.peek_l().getStr());
        return false;
    } 
    ResNode = GroupedExpr::Create(mgr, tok.getLoc(), expr);
            P.dump2(__func__);

    return true;
}

bool Parser::ParseIdentifier(ParserHelper &P, Ast *&ResNode){
    P.dump(__func__);
    ResNode = nullptr;
    bool HasSelf = false;
    Lexeme &tok = P.peek_l();
    if(tok.getTok().IsKeyword()){
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found keyword - ", P.peek_l().getStr());
        return false;
    }
    if(!P.check(IDEN) && !P.check(SELF)){
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found - ", P.peek_l().getStr());
        return false;
    }
    if(P.check(SELF)){
        HasSelf = true;
    }
    ResNode = Identifier::Create(mgr, tok.getLoc(), tok);
    P.next();
        P.dump2(__func__);

    return true;
}



bool Parser::ParseStructExpr(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    bool isDecl = false;
    Lexeme &tok = P.peek_l();
    ResNode =  nullptr;
    std::vector<Ast*> Vals;

    if(!P.checkn(LBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected '{' found - ", P.peek_l().getStr());
        return false;
    }

    
    while(!P.check(RBRACE)){
        Ast *expr = nullptr; 
        Lexeme &tok = P.peek_l();
        if(!P.check(IDEN)){
            err::err_out(P.peek_l().getLoc(), "expected 'identifier' found - ", P.peek_l().getStr());
            return false;
        }
        Lexeme &var = P.peek_l();
        P.next();
        if(!P.checkn(COL)){
            err::err_out(P.peek_l().getLoc(), "expected ':' found - ", P.peek_l().getStr());
            return false;
        }
        if(!ParseExpr(P, expr)){
            return false;
        }
        if(expr == nullptr){
            return false;
        }
        Vals.push_back(VarStmt::Create(mgr, tok.getLoc(), var, nullptr, expr, false));
        if(!P.checkn(COMMA)){
            break;
        }
    }

    if(!P.checkn(RBRACE)) {
        err::err_out(P.peek_l().getLoc(), "expected '}' found - ", P.peek_l().getStr());
        return false;
    }

    ResNode = FieldExpr::Create(mgr, tok.getLoc(), Vals);
    P.dump2(__func__);
    return true;
}

bool Parser::ParseArrayIndexExpr(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    Lexeme &tok = P.peek_l();
    ResNode = nullptr;
    Ast *IndexVal = nullptr;

    if(!P.checkn(LBRACK)){
        err::err_out(P.peek_l().getLoc(), "expected '[' found - ", P.peek_l().getStr());
        return false;
    }

    if(P.check(RBRACK)){
        err::err_out(P.peek_l().getLoc(), "expected index expression found - ", P.peek_l().getStr());
        return false;
    }

    if(!ParseExpr(P, IndexVal)){
        return false;
    }

    if(!P.checkn(RBRACK)){
        err::err_out(P.peek_l().getLoc(), "expected ']' found - ", P.peek_l().getStr());
        return false;
    }

    ResNode = IndexVal;
        P.dump2(__func__);

       return true;
}

bool Parser::ParseSpecificType(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    Ast *expr = nullptr;
    Lexeme &tok = P.peek_l();
    if(P.check(IDEN) && P.checkh(COLCOL)){
        if(!ParsePath(P,expr)){
            return false;
        }
        goto end;
    }

    if(!P.check(IDEN)){
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found -");
        return false;
    }
    expr = Identifier::Create(mgr, tok.getLoc(), P.peek_l(), true);
    P.next();
end:
    P.dump2(__func__);
    ResNode = expr;
    return true;
}

bool Parser::ParseEnumStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    std::vector<VarStmt*>Evals;
    if(!P.checkn(ENUM)){
        err::err_out(P.peek_l().getLoc(), "expected 'enum' keyword found -");
        return false;
    }
    if(!P.check(IDEN)) {
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found -");
        return false;
    }
    Lexeme &Name = P.peek_l();
    P.next();
    Ast *Ty = nullptr;
    if(P.checkn(COL)) {
        if(!ParseType(P, Ty)) {
            return false;
        }
    }else{
        Ty = PremitiveType::Create(mgr, P.peek_l().getLoc(), Lexeme(P.peek_l().getLoc(), "i32", I32));
    }

    if(!P.checkn(LBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected '{' found - ", P.peek_l().getStr());
        return false;
    }
    if(P.check(RBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected expression found - ", P.peek_l().getStr());
        return false;
    }

    while(P.check(IDEN)){
        Lexeme &Var = P.peek_l();
        P.next();
        Ast* Val = nullptr;
        if(P.checkn(ASN)){
            if(!ParseExpr(P, Val)){
                return false;
            }
            if(Val == nullptr){
                err::err_out(P.peek_l().getLoc(), "expected 'expression' found - ", P.peek_l().getStr());
                return false;
            }
        }
        Evals.push_back(VarStmt::Create(mgr, tok.getLoc(), Var, Ty, Val, _CONST));
        if(!P.checkn(COMMA)){
            break;
        }
    }

    if(!P.checkn(RBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected '}' found - ", P.peek_l().getStr());
        return false;
    }
    ResNode = EnumExpr::Create(mgr, tok.getLoc(), Name, Evals);
        P.dump2(__func__);
    return true;
}


bool Parser::ParseStructStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    std::vector<VarStmt*> field;
    if(!P.checkn(STRUCT)) {
        err::err_out(P.peek_l().getLoc(), "expected keyword 'struct' found ->");
        return false;
    }

    if(!P.check(IDEN)) {
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found ->");
        return false;
    }
    const Lexeme &ident = P.peek_l();
    P.next();


    if(!P.checkn(LBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected field expression '{' found - ", P.peek_l().getStr());
        return false;
    }

    while(!P.check(FEOF)&&P.check(IDEN)){
        int8_t mask = _FVAR;
        Lexeme &tok = P.peek_l();
        mask = mask|_MUT;
        if(!P.check(IDEN)){
            err::err_out(P.peek_l().getLoc(), "expected 'identifier' found - ", P.peek_l().getStr());
            return false;
        }
        Lexeme &var = P.peek_l();
        P.next();

        Ast* ty = nullptr;
        if(!ParseType(P,ty)){
            err::err_out(P.peek_l().getLoc(), "expected struct field 'type' found - ", P.peek_l().getStr());
            return false;
        }
        field.push_back(VarStmt::Create(mgr, tok.getLoc(), var, ty, nullptr, mask));
        if(!P.checkn(COMMA)){
            break;
        }
    }

    if(!P.checkn(RBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected '}' found - ", P.peek_l().getStr());
        return false;
    }

    ResNode = StructStmt::Create(mgr, tok.getLoc(), ident, field);
    P.dump2(__func__);

       return true;
}




bool Parser::ParseFuncDef(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    std::vector<VarStmt*>param;
    Ast* retval = nullptr;
    BlockStmt* Block = nullptr;
    int mask = 0;
    if(!P.checkn(FN)) {
        err::err_out(P.peek_l().getLoc(), "expected keyword 'fn' found ->\'");
        return false;
    }
    if(!P.check(IDEN)){
        err::err_out(P.peek_l().getLoc(), "expected 'Identifier' with function defination found ->\'");
        return false;
    }   
    Lexeme &name = P.peek_l();
    P.next();

    if(!P.checkn(LPAREN)) {
        err::err_out(P.peek_l().getLoc(), "expected function expression (parameters : type) found - ", P.peek_l().getStr());
        return false;
    }

    if( P.check(SELF) || (P.check(MUT) && P.checkh(SELF))) {
        int8_t mask = _FVAR;
        bool isSelf = false;
        if(P.checkn(MUT)) {
            mask |= _MUT;
        }
        
        Lexeme &ident = P.peek_l();
        if(P.checkn(SELF)) {
            isSelf = true;
        }

        Ast *ty = nullptr;
        if(!isSelf && !ParseType(P,ty)) {
            return false;
        }
        param.push_back(VarStmt::Create(mgr, ident.getLoc(), ident, ty, nullptr, mask));
        P.checkn(COMMA);
    }
    while(P.check(IDEN) || P.check(MUT)) {
        int8_t mask = _FVAR;
        if(P.checkn(MUT)) {
            mask |= _MUT;
        }

        if(!P.check(IDEN)){
            err::err_out(P.peek_l().getLoc(), "expected 'identifier' found -> \'");
            return false;
        }
        
        Lexeme &ident = P.peek_l();
        P.next();

        Ast *ty = nullptr;
        if(!ParseType(P,ty)) {
            return false;
        }

        param.push_back(VarStmt::Create(mgr, ident.getLoc(), ident, ty, nullptr, mask));
        
        if(!P.checkn(COMMA)) {
            break;
        }

    }

    if(!P.checkn(RPAREN)){
        err::err_out(P.peek_l().getLoc(), "expected ')' found - ", P.peek_l().getStr());
        return false;
    }

    if(P.checkn(ARROW)){
        if(!ParseType(P, retval)){
            err::err_out(P.peek_l().getLoc(), "expected 'type' found - ", P.peek_l().getStr());
            return false;
        }
    }

    if(P.check(LBRACE)) {
        if(!ParseSubBlock(P, Block)){
            return false;
        }
    }else{
        err::err_out(P.peek_l().getLoc(), "expected function body expression '{}' found - ", P.peek_l().getStr());
        return false;
    }

    FunctionProto *FuncProto = FunctionProto::Create(mgr, tok.getLoc(), name, param, retval);
    ResNode = FunctionDef::Create(mgr, tok.getLoc(), FuncProto, Block);
    P.dump2(__func__);
    return true;
}

bool Parser::ParseIfStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    if(!P.checkn(IF)){
        err::err_out(P.peek_l().getLoc(), "expected 'if' found - ", P.peek_l().getStr());   
        return false;
    }
    Ast* condition = nullptr;
    BlockStmt *if_ = nullptr;
    Ast* else_ = nullptr;

    if(P.check(LBRACE)) {
        err::err_out(P.peek_l().getLoc(), "expected 'condition' found - ", P.peek_l().getStr());
        return false;
    }

    if(!ParseExpr(P, condition)){
        return false;
    }

    if(!ParseSubBlock(P,if_)){
        return false;
    }


    if(P.checkn(ELSE)) {
        switch(P.peek_tt()){
            case IF:
                if(!ParseIfStmt(P,else_)){
                    return false;
                }
                break;
            case LBRACE:
            {
                BlockStmt *block = nullptr;
                if(!ParseSubBlock(P,block)){
                    return false;
                }
                else_ = block;
            }
                break;
            default:
                err::err_out(P.peek_l().getLoc(), "invalid else expression - ");
                return false;

        }
    }
    ResNode = IfStmt::Create(mgr, tok.getLoc(), condition, if_, else_);
    P.dump2(__func__);

    return true;
}

bool Parser::ParseForStmt(ParserHelper &P, Ast *&ResNode){
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    Ast* var = nullptr;
    Ast* cond = nullptr;
    Ast* incr = nullptr;
    BlockStmt* body = nullptr;
    if(!P.checkn(FOR)) {
        err::err_out(P.peek_l().getLoc(), "expected keyword 'for' found - ", P.peek_l().getStr());
        return false;
    }

    if(P.checkn(SCOL)){
        goto cond;
    }
    if(P.check(LET)){
        if(!ParseVarStmt(P, var)){
            return false;
        }
    }else{
        if(!ParseExpr(P, var)){
            return false;
        }
    }
    
    if(!P.checkn(SCOL)){
        err::err_out(P.peek_l().getLoc(), "expected for expression ';' found - ", P.peek_l().getStr());
        return false;
    }
cond:
    if(P.checkn(SCOL)){
        goto incr;
    }
    if(!ParseExpr(P, cond)){
        return false;
    }

    if(!P.checkn(SCOL)){
        err::err_out(P.peek_l().getLoc(), "expected for expression ';' found - ", P.peek_l().getStr());
        return false;
    }

incr:
    if(P.check(LBRACE)){
        goto incr;
    }
    if(!ParseExpr(P, incr)){
        return false;
    }

body:

    if(!ParseSubBlock(P,body)){
        return false;
    }

    ResNode = ForLoop::Create(mgr, tok.getLoc(), var, cond, incr, body);
        P.dump2(__func__);

    return true;
}


// ref from rust lang and scribe
bool Parser::ParseForInStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    Lexeme &tok = P.peek_l();
    Ast* in = nullptr;
    Ast* var = nullptr;
    Ast* cond = nullptr;
    Ast* incr = nullptr;
    BlockStmt* body = nullptr;
    bool isLet = false;
    // bool isBrace = true;
    if(!P.checkn(FOR)) {
        err::err_out(P.peek_l().getLoc(), "expected keyword 'for' found - ", P.peek_l().getStr());
        return false;
    }

    // if(P.checkn(LET)){
    //     isLet = true;
    // }
    
    // if(isLet && !P.checkn(MUT)) {
    //     err::err_out(P.peek_l().getLoc(), "expected keyword mut found - ", P.peek_l().getStr());
    //     return false;
    // }

    if(!P.check(IDEN)){
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found - ", P.peek_l().getStr());
        return false;
    }

    Lexeme &var_tok = P.peek_l();
    P.next();

    if(!P.checkn(IN)){
        err::err_out(P.peek_l().getLoc(), "expected keyword 'in' found - ", P.peek_l().getStr());
        return false;
    }
    // 0..1 , iter

    if(P.check(LBRACE)){
        err::err_out(P.peek_l().getLoc(), "expected 'expression' found - ", P.peek_l().getStr());
        return false;
    }

    if(!ParseExpr(P,in)) {
        err::err_out(P.peek_l().getLoc(), "for-in use only { 1..5..1 , .iter()} -> ");
        return false;
    }

    if(P.checkn(DOTDOT)){

    // if(P.check(INT)) {
        Ast *from = in;
        Ast *to = nullptr;
        Ast *intlit = nullptr;
        // from = NumericLiteral::Create(mgr, tok.getLoc(), P.peek_l());
        // P.next();

        // if(!P.checkn(DOTDOT)){
        //     err::err_out(P.peek_l().getLoc(), "expected for-in expression '..' found - ", P.peek_l().getStr());
        //     return false;
        // }

        // if(!P.check(INT)){
        //     err::err_out(P.peek_l().getLoc(), "expected for-in expression integer after '..' found - ", P.peek_l().getStr());
        //     return false;
        // }
        // to = NumericLiteral::Create(mgr, tok.getLoc(), P.peek_l());;
        // P.next();
        if(!ParseExpr(P, to)) {
            return false;
        }

        if(P.checkn(DOTDOT)){
            // if(!P.check(INT)){
            //     err::err_out(P.peek_l().getLoc(), "expected for-in expression integer after '..' found - ", P.peek_l().getStr());
            //     return false;
            // }

            // intlit = NumericLiteral::Create(mgr, tok.getLoc(), P.peek_l());;
            // P.next();
            if(!ParseExpr(P, intlit)) {
                return false;
            }
        }else{
            Lexeme t = Lexeme(P.peek_l().getLoc(), "1", (int64_t)1, INT);
            intlit = NumericLiteral::Create(mgr, tok.getLoc(), t);
        }
        

        if(!ParseSubBlock(P,body)){
            return false;
        }

        Identifier *ident = Identifier::Create(mgr, tok.getLoc(), var_tok);

        var = VarStmt::Create(mgr, tok.getLoc(), var_tok, nullptr, from, _MUT);
        cond = Expression::Create(mgr, tok.getLoc(), ident, LT, to,KBinaryExpr);
        incr = Expression::Create(mgr, tok.getLoc(), ident, ASN_PLUS, intlit,KBinaryExpr);
        ResNode = ForLoop::Create(mgr, tok.getLoc(), var, cond, incr, body);
        return true; 

    }else{    
        // if(!ParseExpr(P,in)) {
        //     err::err_out(P.peek_l().getLoc(), "for-in use only { 1..5..1 , .iter()} -> ");
        //     return false;
        // }

        if(!ParseSubBlock(P,body)){
            return false;
        }
        
        ///<iterVar> = <vector.iter()>
        Lexeme iter_var_tok = Lexeme(var_tok.getLoc(), "iterVar", IDEN);
        Lexeme iter__tempvar__tok = Lexeme(var_tok.getLoc(), "_"+var_tok.getStr(), IDEN);
        Lexeme iter_begin_tok = Lexeme(var_tok.getLoc(), "begin", IDEN);
        Lexeme iter_end_tok = Lexeme(var_tok.getLoc(), "end", IDEN);
        Lexeme iter_next_tok = Lexeme(var_tok.getLoc(), "next", IDEN);
        Lexeme iter_at_tok = Lexeme(var_tok.getLoc(), "at", IDEN);

        Identifier* iter_begin_Iden = Identifier::Create(mgr, tok.getLoc(), iter_begin_tok);
        Identifier* iter_end_Iden = Identifier::Create(mgr, tok.getLoc(), iter_end_tok);
        Identifier* iter_next_Iden = Identifier::Create(mgr, tok.getLoc(), iter_next_tok);
        Identifier* iter_at_Iden = Identifier::Create(mgr, tok.getLoc(), iter_at_tok);

        Identifier* iter_tempvar_ident = Identifier::Create(mgr, tok.getLoc(), iter__tempvar__tok);
        Identifier* iter_var_ident = Identifier::Create(mgr, tok.getLoc(), iter_var_tok);
        
        VarStmt* iter_decl = VarStmt::Create(mgr, tok.getLoc(), iter_var_tok, nullptr, in, _MUT);
    
        FieldExpr* begin_call_args = FieldExpr::Create(mgr, tok.getLoc(), {});
        Expression* begin_call = Expression::Create(mgr, tok.getLoc(), iter_begin_Iden, begin_call_args, KCallExpr);
        Expression* iter_dot_begin_call = Expression::Create(mgr, tok.getLoc(), iter_var_ident, DOT, begin_call, KMemExpr);
        var = VarStmt::Create(mgr, tok.getLoc(), iter__tempvar__tok, nullptr, iter_dot_begin_call, _MUT);

        ///<_temp> != <iterVar.end()>
        FieldExpr* end_call_args = FieldExpr::Create(mgr, tok.getLoc(), {});
        Expression* end_call = Expression::Create(mgr, tok.getLoc(), iter_end_Iden, end_call_args, KCallExpr);
        Ast* iter_end_call = Expression::Create(mgr, tok.getLoc(), iter_var_ident, DOT, end_call, KMemExpr);
        cond = Expression::Create(mgr, tok.getLoc(), iter_tempvar_ident, NEQL, iter_end_call, KBinaryExpr);


        ///<iterVar.next(_temp)>
        FieldExpr* nextcall_args = FieldExpr::Create(mgr, tok.getLoc(), {iter_tempvar_ident});
        Expression* nextcall = Expression::Create(mgr, tok.getLoc(), iter_next_Iden, nextcall_args, KCallExpr);
        Expression* iternext = Expression::Create(mgr, tok.getLoc(), iter_var_ident, DOT, nextcall, KMemExpr);
        incr = Expression::Create(mgr, tok.getLoc(), iter_tempvar_ident, ASN, iternext, KBinaryExpr);


        ///<var = _iterVar.at()>
        FieldExpr* at_call_args = FieldExpr::Create(mgr, tok.getLoc(), {iter_tempvar_ident});
        Expression* at_call = Expression::Create(mgr, tok.getLoc(), iter_at_Iden, at_call_args, KCallExpr);
        Expression* iter_at_call = Expression::Create(mgr, tok.getLoc(), iter_var_ident, DOT, at_call, KMemExpr);
        VarStmt* inside_loop_var_decl = VarStmt::Create(mgr, tok.getLoc(), var_tok, nullptr, iter_at_call, _MUT);

        

        body->getStmts().insert(body->getStmts().begin(), inside_loop_var_decl);
        ResNode = ForLoop::Create(mgr, tok.getLoc(), var, cond, incr, body);
                P.dump2(__func__);
        std::vector<Ast*>b = {iter_decl, ResNode};
        ResNode = BlockStmt::Create(mgr, tok.getLoc(), b);
    }
        P.dump2(__func__);

    return true;
}

bool Parser::ParseVarStmt(ParserHelper &P, Ast *&ResNode) {
    P.dump(__func__);
    ResNode = nullptr;
    bool isty = false;
    bool isval = false;
    bool isConst = false;
    bool isLet = false;
    bool isStatic = false;
    int8_t mask = 0;

    Lexeme &tok = P.peek_l();
    if(P.checkn(LET)){
        isLet = true;
    }else if(P.checkn(CONST)){
        isConst = true;
        mask |= _CONST;
    }else{
        err::err_out(P.peek_l().getLoc(), "expected {const, let, static} found - ", P.peek_l().getStr());
        return false;
    }
    if(isConst&&P.check(MUT)){
        err::err_out(P.peek_l().getLoc(), "const cannot be used with - ");
        return false;
    }
    if(P.checkn(MUT))
        mask |= _MUT;

    if(!P.check(IDEN)){
        err::err_out(P.peek_l().getLoc(), "expected 'identifier' found - ", P.peek_l().getStr());
        return false;
    }
    Lexeme &Var = P.peek_l();
    P.next();
    Ast* Ty = nullptr;
    Ast* Val = nullptr;


    if(P.check(SCOL)){
        err::err_out(P.peek_l().getLoc(), "invalid variable declaration");
        return false;
    }

    if(P.check(ASN)){
        goto val;
    }
    
    isty = true;
    if(!ParseType(P,Ty)){
        return false;
    }

val:  
    if(P.peek_l().getTok().IsAssnCombinedOP()){
        err::err_out(P.peek_l().getLoc(), "invalid variable declaration - didn't initialized");
        return false;
    }
    if(!P.checkn(ASN)){
        goto done;
    }
    isval = true;
    if(!ParseExpr(P, Val)){
            return false;
    }

done:
    if(!isval && !isty){
        err::err_out(P.peek_l().getLoc(), "invalid variable declaration - no type or value set");
        return false;
    }

check:
    if(isConst) {
        if(!isval) {
            err::err_out(P.peek_l().getLoc(), "free constant item without body - ");
    
            return false;
        }
        if(!isty) {
            err::err_out(P.peek_l().getLoc(), "missing type for `const` item - ");
    
            return false;
        }
    }

    ResNode = VarStmt::Create(mgr, tok.getLoc(), Var, Ty, Val, mask);
        P.dump2(__func__);

    return true;
}
} // namespace parser
