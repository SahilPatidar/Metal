#pragma once
//#include <cstdio>
#include <iostream>
#include"../Context.hpp"

namespace ast
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
        String s;
        int64_t i;
        long double f;
    };

    class Tok{
    private:
        Token_type tok;
    public: 
        Tok(const Token_type &_tok)
        :tok(_tok) {}

        Token_type getTokType() const { return tok; }
        
        // inline const char* toStr() { return tok?TokenMap[tok]:"";}
        inline String toStr() { 
            if(tok) {
                String str = TokenMap[tok];
                return str;
            }
            return "";
        }
        inline bool isLiteral() const noexcept {
            return tok >= INT && tok <= FALSE;
        }
        
        inline bool ArithmeticOP() const noexcept {
            return  tok >= PLUS && tok <= MODULO;
        } 

        inline bool IsConditionalOP() const noexcept {
            return tok >= CND_AND &&  tok <= GEQL;
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

        inline String toStr() const noexcept { return TokenMap[tok]; }

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
        const StmtLoc *Loc;
        TokData data;
        Tok tok;
    public:
        explicit Lexeme(const StmtLoc *_Loc, String _s,  long double f, const Token_type &_t)
        :Loc(_Loc), data({.s = _s, .i = 0lu, .f = f}),tok(_t){}
        explicit Lexeme(const StmtLoc *_Loc, String _s, int64_t i,  const Token_type &_t)
        :Loc(_Loc), data({.s = _s, .i = i, .f = 0.0}),tok(_t){}
        explicit Lexeme(const StmtLoc *_Loc, String _s, const Token_type &_t)
        :Loc(_Loc), data({.s = _s, .i = 0, .f = 0.0}),tok(_t){}
        explicit Lexeme(const StmtLoc *_Loc, const Token_type &_t)
        :Loc(_Loc), data({.s = "", .i = 0, .f = 0.0}),tok(_t){}
        explicit Lexeme(const StmtLoc *_Loc, long double f, const Token_type &_t)
        :Loc(_Loc), data({.s = "", .i = 0, .f = f}),tok(_t){}
        explicit Lexeme(const StmtLoc *_Loc, int64_t i,  const Token_type &_t)
        :Loc(_Loc), data({.s = "", .i = i, .f = 0.0}),tok(_t){}
        ~Lexeme(){}

        const StmtLoc *getLoc() noexcept { return Loc; }
        inline Tok getTok() const noexcept { return tok; }
        inline Token_type getTokTy() const noexcept { return tok.getTokType(); }
        int getPos() const noexcept { return Loc->getCol(); }
        int getLine() const noexcept { return Loc->getLine(); }
        String getStr() const noexcept { return data.s.empty()?TokenMap[tok.getTokType()]:data.s; }
        inline void setDataStr(const String &str) { data.s = str; }
        inline void setDataInt(int64_t i)  { data.i = i; }
        inline void setDataFlt(const long double &f) { data.f = f; }
        inline int64_t getDataInt() const noexcept { return data.i; }
        inline double getDataFlt() const noexcept { return data.f; }
    };


    class Lexer {
    private:
        
        Context &mgr;
        
        Module *mod;
        
        const String &Src;
        const char *MainBuf;
        const char *StartLine;
        const char *EndBuf;
        size_t Line{0};
        // size_t CurBufIdx{0};
        // size_t StartIdx{0};
        Vec<Lexeme> &LxmS;

        inline bool isWhiteSpace(const char C) {
            return C == ' ' || C == '\t' || C == '\f' || 
                C == '\v' || C == '\n'  || C == '\r';
        }
        inline bool isHorzizenalWhiteSpace(const char C) {
            return C == ' ' || C == '\t' || C == '\f' || C == '\r' ;
        }
        inline bool isVirticalWhiteSpace(const char C) {
            return C == '\v' || C == '\n';
        }
        inline char getAndAdvanceChar(const char *&Ptr) {
            char C = *Ptr;
            ++Ptr;
            return C;
        }

        inline char getChar(const char *Ptr, int Size) {
            return *(Ptr + Size);
        }

        inline char getChar(const char *Ptr) {
            return *Ptr;
        }

        inline void AdvanceChar(const char *&Ptr) {
            const char *tmpPtr = Ptr;
            if(HasChar(++tmpPtr)) {
                ++Ptr;
            }
        }
        inline void AdvanceChar(const char *&Ptr, int Size) {
            const char *tmpPtr = Ptr + Size;
            if(HasChar(++tmpPtr)) {
                Ptr += Size;
            }
        }

        inline char HasChar(const char *Ptr) {
            return *Ptr != 0;
        }

        StmtLoc *getLoc(int Line, int Col) noexcept;
       
        Token_type getKeyWord(const String &Src);
        bool LexConstString(const char *&CurBuff);
        bool LexConstChar(const char *&CurBuff);
        bool LexIdentifier(const char *&CurBuff);
        bool SkipWhiteSpace(const char *&CurBuff);
        bool SkipCommentLine(const char *&CurBuff);
        bool SkipCommentBlock(const char *&CurBuff);
        
        bool LexConstNumerical(const char *&CurBuff, int &Base, Token_type &type);
        
        bool RemoveSlashes(String &s);
    public:
        Lexer(Context &_mgr, Module *_mod, String &_Src, Vec<Lexeme> &_LxmS) 
        :mgr(_mgr), mod(_mod), Src(_Src), LxmS(_LxmS) {
            MainBuf = _Src.c_str();
        }
        
        ~Lexer() {}
        
        bool Tokenize();
    };
}

