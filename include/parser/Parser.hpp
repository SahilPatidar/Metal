#pragma once
#include<iostream>
#include"Ast.hpp"
#include"../Context.hpp"
// #include"../Module.hpp"
#include"../lex/lex.hpp"


using namespace ast;
namespace parser{
 
    class ParserHelper{
    private:
        std::vector<Lexeme> toks;
        uint idx;
    public:
        ParserHelper(const std::vector<Lexeme> &_toks)
        :toks(_toks) { idx = 0;}
        ~ParserHelper(){}



        inline void next() {
            if(idx + 1 < toks.size()) {
                ++idx;
            }
        }

        inline bool checkNH(Token_type tok, int i){
            return at_tt(i) == tok;
        }

        inline bool check(Token_type tok) {
            return peek_tt() == tok;
        }

        inline bool CheckAndConsume(Token_type tok) {
            if(peek_tt() == tok){
                next();
                return true;
            }
            return false;
        }

        inline bool checkh(Token_type tok) {
            return next_tt() == tok;
        }

        inline Lexeme &next_l() {
            return (idx+1 < toks.size())?toks[idx+1]:toks[idx];
        }

        inline Tok next_t() {
            return next_l().getTok();
        }

        inline Token_type next_tt() {
            return next_t().getTokType();
        }

        inline Lexeme &peek_l() {
            return toks[idx];
        }

        inline bool isBinaryOpr() {
            return toks[idx].getTok().IsBinaryOP();
        }

        inline bool isAssnCombinedOpr() {
            return toks[idx].getTok().IsAssnCombinedOP();
        }

        inline bool isUnaryOpr() {
            return toks[idx].getTok().IsUnaryOP();
        }
        inline bool isPreDefTy() {
            return toks[idx].getTok().IsPreDefType();
        }
        inline bool isLiteral() {
            return toks[idx].getTok().isLiteral();
        }

        inline Tok peek_t() {
            return peek_l().getTok();
        }

        inline Token_type peek_tt() {
            return peek_t().getTokType();
        }

        inline Lexeme &at(int i) {
            return idx+i < toks.size()?toks[idx+i]:toks[toks.size()-1];
        }

        inline Tok at_t(int i) {
            return at(i).getTok();
        }

        inline Token_type at_tt(int i) {
            return at_t(i).getTokType();
        }

        void dump(std::string msg);
        void dump2(std::string msg);

        int preced(Token_type op);
    };

    class Parser{
    private:
        Context &mgr;
        Module* modctx;
    public:
        // Parser(Module *_modctx)
        // :modctx(_modctx){}
        Parser(Context &_mgr, Module* _modctx)
        :mgr(_mgr), modctx(_modctx) {}
        
        ~Parser(){}

        bool parse(Ast *&tree);
    private:
        bool ParseBlock(ParserHelper &P, BlockStmt *&ResNode, bool IsTop = false);
        bool ParseSubBlock(ParserHelper &P, BlockStmt *&ResNode);
        bool ParseMethod(ParserHelper &P, Ast *&ResNode);
        bool ParseUseStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseWhileStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseReturnStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseType(ParserHelper &P, Ast *&ResNode);
        bool ParseArrayType(ParserHelper &P, Ast *&ResNode);
        bool ParseTypeStatm(ParserHelper &P, Ast *&ResNode);
        bool ParseCall(ParserHelper &P, Ast *&ResNode);
        bool ParseListExpr(ParserHelper &P, Ast *&ResNode);
        bool ParsePrefixExpr(ParserHelper &P, Ast *&ResNode);
        bool ParseExpr(ParserHelper &P, Ast *&ResNode);
        bool ParseExpr1(ParserHelper &P, Ast *&ResNode, int Precedance);
        bool ParseExpr2(ParserHelper &P, Ast *&ResNode);
        bool ParseExpr3(ParserHelper &P, Ast *&ResNode);

        bool ParseExtFnCall(ParserHelper &P, Ast *&ResNode);

        bool ParseBinaryExpr1(ParserHelper &P, Ast *&ResNode, int prev_prece);
        bool ParseBinaryExpr2(ParserHelper &P, Ast *&ResNode, int prev_prece);
        bool ParseBinaryExpr3(ParserHelper &P, Ast *&ResNode, int prev_prece);
        bool ParseBinaryExpr4(ParserHelper &P, Ast *&ResNode, int prev_prece);
        bool ParseBinaryExpr5(ParserHelper &P, Ast *&ResNode, int prev_prece);
        bool ParseBinaryExpr6(ParserHelper &P, Ast *&ResNode, int prev_prece);
        bool ParseBinaryExpr7(ParserHelper &P, Ast *&ResNode, int prev_prece);

        // bool ParseGenericParam(ParserHelper &P, GenericParam *&ResNode);

        bool ParseDelStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseNewStmt(ParserHelper &P, Ast *&ResNode);
    

        bool ParsePath(ParserHelper &P, Ast *&ResNode);
        bool ParseExpression(ParserHelper &P, Ast *&ResNode);
        bool ParseLiteral(ParserHelper &P, Ast *&ResNode);
        bool ParseParenExpr(ParserHelper &P, Ast *&ResNode);
        bool ParseIdentifier(ParserHelper &P, Ast *&ResNode);
        bool ParseDotArrowExpr(ParserHelper &P, Ast *&ResNode);
        bool ParseStructExpr(ParserHelper &P, Ast *&ResNode);
        bool ParseArrayIndexExpr(ParserHelper &P, Ast *&ResNode);
        bool ParseSpecificType(ParserHelper &P, Ast *&ResNode);
        bool ParseEnumStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseStructStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseFuncDef(ParserHelper &P, Ast *&ResNode);
        bool ParseIfStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseForStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseForInStmt(ParserHelper &P, Ast *&ResNode);
        bool ParseExtern(ParserHelper &P, Ast *&ResNode);
        bool ParseMod(ParserHelper &P, Ast *&ResNode);
        bool ParseVarStmt(ParserHelper &P, Ast *&ResNode);
    };

}
