#pragma once
//#include <cstdio>
#include <iostream>
#include <vector>
#include"../ResMgr.hpp"

namespace lex
{
    enum Token_type
    {
        SELF,
        INT,
        STR,
        CHAR,
        FLOAT,
        IDEN,
        NIL,

        TRUE,
        FALSE,
        IS,
        MUT,
        WHILE,
        AS,
        IN,
        MOD,
        USE,
        TYPE,
        CONST,
        STATIC,
        FN,
        FOR,
        LET,
        RETURN,
        CONTINUE,
        BREAK,
        IF,
        ELSE,
        STRUCT,
        METHOD,
        ENUM,
        EXTERN,
        BOOL,
        I8,
        I16,
        I32,
        I64,
        I128,
        UI8,
        UI16,
        UI32,
        UI64,
        F32,
        F64,

        ASN,
        PLUS,
        MINUS,
        STAR,
        DIV,
        MODULO,

        ASN_PLUS,
        ASN_STAR,
        ASN_MINUS,
        ASN_DIV,
        ASN_MOD,


        
        CND_AND,
        CND_OR,

        EQL,
        NEQL,
        LT,
        GT,
        LEQL,
        GEQL,


        AND,
        OR,
        XOR,
        LSHIFT,
        RSHIFT,

        ASN_AND,
        ASN_OR,
        ASN_XOR,
        ASN_LSHIFT,
        ASN_RSHIFT,

        NOT,
        CND_NOT,

        DOTDOT,

        ARROW,
        DOT,
        SCOL,
        COL,
        COLCOL,
        COMMA,
        SPC,
        TAB,
        NEWL,

        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        LBRACK,
        RBRACK,

        AT,

        NEW,
        DEL,

        FEOF,
        INVALID,
        _LAST
    };
    extern const char *TokenMap[_LAST];

    struct TokData
    {
        std::string s;
        int64_t i;
        double f;
    };

    class Tok{
    private:
        Token_type tok;
    public: 
        Tok(const Token_type &_tok)
        :tok(_tok) {}

        Token_type getTokType() const { return tok; }
        
        // inline const char* toStr() { return tok?TokenMap[tok]:"";}
        inline std::string toStr() { 
            if(tok) {
                std::string str = TokenMap[tok];
                return str;
            }
            return "";
        }
        inline bool isLiteral() const noexcept {
            return tok >= INT && tok <= FALSE;
        }
        
        inline bool ArithmeticOP() const noexcept {
            return  tok >= PLUS && tok <= MODULO;

            // return tok == STAR || tok == DIV || tok == MODULO ||
            //                         tok == MINUS || tok == PLUS;

        } 

        inline bool IsConditionalOP() const noexcept {
            return tok >= CND_AND &&  tok <= GEQL;
            // return tok == LT || tok == LEQL || tok == GT || 
            //         tok == GEQL || tok == EQL || tok == NEQL ||
            //                             tok == CND_AND ||  tok == CND_OR;
        }  

        inline bool LogicalOP() const noexcept{
            return tok >= AND && tok <= RSHIFT;
        }  

        inline bool IsBinaryOP() const noexcept {
            return ArithmeticOP()||IsConditionalOP()||LogicalOP();
        } 

        inline bool IsUnaryOP() const noexcept {
            return tok == MINUS||
            tok == STAR|| tok == AND || tok == NOT || tok == CND_NOT;
        }

        inline bool IsAsnArithmeticOP() const noexcept {
            return tok >= ASN_PLUS && tok <= ASN_MOD;
        }
        inline bool IsAsnLogicalOP() const noexcept {
            return  tok >= ASN_AND && tok <= ASN_RSHIFT;
        }
        inline bool IsAssnCombinedOP() const noexcept {
            return IsAsnArithmeticOP() || IsAsnLogicalOP();
        }

        inline bool IsAssignOP() const noexcept {
            return tok == ASN;
        }
        
        inline bool IsPreDefType() const noexcept {
            return tok >= BOOL && tok <= F64;
        }

        inline std::string toStr() const noexcept { return TokenMap[tok]; }

        inline bool IsKeyword() const noexcept {
            return tok >= TRUE && tok <= F64;
        }

        inline bool IsTerminal() const noexcept {
            return tok == RPAREN || tok == COMMA ||
            tok == RBRACE || tok == RBRACK || tok == COL || tok == SCOL;
        }

        inline bool operator==(const Tok &_Tok) {
            if(tok == _Tok.getTokType()){
                return true;
            }
            return false;
        }

        inline bool operator==(Tok _Tok) {
            if(tok == _Tok.getTokType()){
                return true;
            }
            return false;
        }

        inline bool operator!=(Tok _Tok) {
            if(tok != _Tok.getTokType()){
                return true;
            }
            return false;
        }

        inline bool operator==(const enum Token_type _Tok) {
            if(tok == _Tok){
                return true;
            }
            return false;
        }
        inline bool operator!=(Token_type _Tok) {
            if(tok != _Tok){
                return true;
            }
            return false;
        }
    };
    
    class Lexeme {
    private:
        const ast::StmtLoc *Loc;
        TokData data;
        Tok tok;
    public:
        explicit Lexeme(const ast::StmtLoc *_Loc, std::string _s,  double f, const Token_type &_t)
        :Loc(_Loc), data({.s = _s, .i = 0lu, .f = f}),tok(_t){}
        explicit Lexeme(const ast::StmtLoc *_Loc, std::string _s, int64_t i,  const Token_type &_t)
        :Loc(_Loc), data({.s = _s, .i = i, .f = 0.0}),tok(_t){}
        explicit Lexeme(const ast::StmtLoc *_Loc, std::string _s, const Token_type &_t)
        :Loc(_Loc), data({.s = _s, .i = 0, .f = 0.0}),tok(_t){}
        explicit Lexeme(const ast::StmtLoc *_Loc, double f, const Token_type &_t)
        :Loc(_Loc), data({.s = "", .i = 0, .f = f}),tok(_t){}
        explicit Lexeme(const ast::StmtLoc *_Loc, int64_t i,  const Token_type &_t)
        :Loc(_Loc), data({.s = "", .i = i, .f = 0.0}),tok(_t){}
        ~Lexeme(){}

        const ast::StmtLoc *getLoc() noexcept { return Loc; }
        inline Tok getTok() const noexcept { return tok; }
        inline Token_type getTokTy() const noexcept { return tok.getTokType(); }
        int getPos() const noexcept { return Loc->getCol(); }
        int getLine() const noexcept { return Loc->getLine(); }
        std::string getStr() const noexcept { return data.s; }
        inline void setDataStr(const std::string &str) { data.s = str; }
        inline void setDataInt(int64_t i)  { data.i = i; }
        inline void setDataFlt(const long double &f) { data.f = f; }
        inline int64_t getDataInt() const noexcept { return data.i; }
        inline double getDataFlt() const noexcept { return data.f; }
        
    };

    class Lexer {
        ast::ResourceMgr &mgr;
        ast::Module *mod;
    private:
        ast::StmtLoc *getLoc(size_t line, size_t col) noexcept;
        Token_type get_keyword(std::string &src);
        std::string  get_string(const std::string &src, size_t &i);
        bool get_const_string(const std::string &src, size_t &i, size_t &line, char &quote, std::string &str);
        bool get_num(const std::string &src, size_t line, size_t &i, size_t base, std::string &num, Token_type &type);
        bool get_operator(const std::string &src, Token_type &op_type, size_t &i);
        bool remove_slashes(std::string &src);
    public:
        Lexer(ast::ResourceMgr &_mgr, ast::Module *_mod) 
        :mgr(_mgr), mod(_mod) {}
        ~Lexer() {}
        bool tokenizer(const std::string &src, std::vector<Lexeme> &toks, size_t begin, size_t end);
    };
}

