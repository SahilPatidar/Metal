#pragma once
//#include <cstdio>
#include<iostream>
#include<map>
#include<vector>

namespace lex
{
    enum Token_type
    {
        INT,
        STR,
        CHAR,
        FLOAT,
        IDEN,
        NIL,

        IS,
        MUT,
        EXTERN,
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
        TRUE,
        FALSE,
        SELF,
        IF,
        ELSE,
        STRUCT,
        METHOD,
        ENUM,
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
        UI128,
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
        CND_NOT,

        EQL,
        NEQL,
        LT,
        GT,
        LEQL,
        GEQL,

        AND,
        OR,
        XOR,
        NOT,
        ASN_AND,
        ASN_OR,
        ASN_XOR,

        LSHIFT,
        RSHIFT,
        ASN_LSHIFT,
        ASN_RSHIFT,

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

        FEOF,
        INVALID,
        _LAST
    };
    extern const char *TokenMap[_LAST];

    struct TokData
    {
        int line;
        int pos;
        std::string s;
        int64_t i;
        double f;
        TokData(const int &_line, const int &_pos, const std::string &_data, int64_t _i, long double _f)
		:line(_line), pos(_pos),  s(_data), i(_i), f(_f)
	    {}
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
            return tok == INT||tok == STR||tok == CHAR|| tok == FLOAT||tok == TRUE||tok == FALSE||tok == NIL;
        }
        
        inline bool ArithmeticOP() const noexcept {
            return tok == STAR || tok == DIV || tok == MODULO ||
                                    tok == MINUS || tok == PLUS;
        } 

        inline bool ConditionalOP() const noexcept {
            return tok == LT || tok == LEQL || tok == GT || 
                    tok == GEQL || tok == EQL || tok == NEQL ||
                                        tok == CND_AND ||  tok == CND_OR;
        }  

        inline bool LogicalOP() const noexcept{
            return tok == LSHIFT || tok == RSHIFT || tok == XOR || 
                    tok == AND || tok == OR;
        }  

        inline bool IsBinaryOP() const noexcept {
            return ArithmeticOP()||ConditionalOP()||LogicalOP();
        } 

        inline bool IsUnaryOP() const noexcept {
            return tok == PLUS|| tok == MINUS||
            tok == STAR|| tok == AND || tok == NOT || tok == CND_NOT;
        }

        inline bool IsAssnCombinedOP() const noexcept {
            return tok == ASN_DIV||
            tok == ASN_MINUS|| tok == ASN_MOD||tok == ASN_PLUS|| tok == ASN_STAR|| 
            tok == ASN_AND|| tok == ASN_XOR||tok == ASN_OR || tok == ASN_LSHIFT ||
            tok == ASN_RSHIFT;
        }
        inline bool IsAssignOP() const noexcept {
            return tok == ASN;
        }
        
        inline bool IsPreDefType() const noexcept {
            return tok == I8 || tok == I16 ||
            tok == I32 || tok == I64 || tok == UI8 || tok == UI16 ||
            tok == UI32 || tok == UI64 || tok == F32 || tok == F64 ||
            tok == BOOL;
        }

        inline bool IsKeyword() const noexcept {
            return tok == FN || tok == RETURN || tok == EXTERN || tok == MUT || 
            tok == WHILE ||tok == AS ||tok == IN ||tok == MOD ||tok == TYPE || 
            tok == CONST ||tok == STATIC ||tok == FN ||tok == FOR || tok == LET ||
            tok == RETURN ||tok == CONTINUE ||tok == BREAK || tok == TRUE || 
            tok == FALSE ||tok == IF ||tok == ELSE ||tok == STRUCT ||tok == METHOD || tok == ENUM || 
            tok == BOOL ||tok == I8 ||tok == I16 ||tok == I32 ||tok == I64 ||tok == I128 || 
            tok == UI8 ||tok == UI16 ||tok == UI32 ||tok == UI64 ||tok == UI128 ||tok == F32 || tok == F64;
        }

        inline bool IsTerminal() const noexcept {
            return tok == RPAREN || tok == COMMA ||
            tok == RBRACE || tok == RBRACK || tok == COL || tok == SCOL;
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

        inline bool operator==(Token_type _Tok) {
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
        TokData data;
        Tok tok;
    public:
        explicit Lexeme(int line, int pos, std::string _str, long double f, const Token_type &_t)
        :data({line, pos, _str, 0ul, f}),tok(_t){}
        explicit Lexeme(int line, int pos, std::string _str, int64_t i,  const Token_type &_t)
        :data({line, pos, _str, i, 0.0}),tok(_t){}
        explicit Lexeme(int line, int pos, std::string _str, const Token_type &_t)
        :data({line, pos, _str, 0ul, 0.0}),tok(_t){}
        explicit Lexeme(int line, int pos, long double f, const Token_type &_t)
        :data({line, pos, "", 0ul, f}),tok(_t){}
        explicit Lexeme(int line, int pos, int64_t i,  const Token_type &_t)
        :data({line, pos, "", i, 0.0}),tok(_t){}
        explicit Lexeme(int64_t i,  const Token_type &_t)
        :data({0, 0, "", i, 0.0}),tok(_t){}
        explicit Lexeme(std::string s, const Token_type &_t)
        :data({-1,-1,s, 0ul, 0.0}),tok(_t){}

        Tok getTok() const noexcept { return tok; }
        Token_type getTokTy() const noexcept { return tok.getTokType(); }
        int getPos() const noexcept { return data.pos; }
        int getLine() const noexcept { return data.line; }
        std::string getStr() const noexcept { return data.s; }
        inline void setDataStr(const std::string &str) { data.s = str; }
        inline void setDataInt(int64_t i)  { data.i = i; }
        inline void setDataFlt(const long double &f) { data.f = f; }
        inline int64_t getDataInt() const noexcept { return data.i; }
        inline double getDataFlt() const noexcept { return data.f; }
        
    };

    class Lexer {
    private:
        std::map<const char *, Token_type>TokenMap;
        Token_type get_keyword(std::string &src);
        std::string  get_string(const std::string &src, int &i);
        bool get_const_string(const std::string &src, int &i, char &quote, std::string &str);
        bool get_num(const std::string &src, int &i, int base, std::string &num, Token_type &type);
        bool get_operator(const std::string &src, Token_type &op_type, int &i);
    public:
        Lexer(){
        TokenMap.insert({"INT",INT});
        TokenMap.insert({"STR",STR});
        TokenMap.insert({"CHAR",CHAR});
        TokenMap.insert({"FLOAT",FLOAT});
        TokenMap.insert({"null",NIL});
        TokenMap.insert({"IDEN",IDEN});

        TokenMap.insert({"is",IS});
        TokenMap.insert({"mut",MUT});
        TokenMap.insert({"extern",EXTERN});
        TokenMap.insert({"while",WHILE});
        TokenMap.insert({"as",AS});
        TokenMap.insert({"in",IN});
        TokenMap.insert({"mod",MOD});
        TokenMap.insert({"use",USE});
        TokenMap.insert({"type",TYPE});
        TokenMap.insert({"const",CONST});
        TokenMap.insert({"static",STATIC});
        TokenMap.insert({"fn",FN});
        TokenMap.insert({"for",FOR});
        TokenMap.insert({"let",LET});
        TokenMap.insert({"return",RETURN});
        TokenMap.insert({"continue",CONTINUE});
        TokenMap.insert({"break",BREAK});
        TokenMap.insert({"true",TRUE});
        TokenMap.insert({"false",FALSE});
        TokenMap.insert({"self",SELF});
        TokenMap.insert({"if",IF});
        TokenMap.insert({"else",ELSE});
        TokenMap.insert({"struct",STRUCT});
        TokenMap.insert({"interface",METHOD});
        TokenMap.insert({"enum",ENUM});
        TokenMap.insert({"bool",BOOL});
        TokenMap.insert({"i8",I8});
        TokenMap.insert({"i16",I16});
        TokenMap.insert({"i32",I32});
        TokenMap.insert({"i64",I64});
        TokenMap.insert({"i128",I128});
        TokenMap.insert({"ui8",UI8});
        TokenMap.insert({"ui16",UI16});
        TokenMap.insert({"ui32",UI32});
        TokenMap.insert({"ui64",UI64});
        TokenMap.insert({"ui128",UI128});
        TokenMap.insert({"flt32",F32}); 
        TokenMap.insert({"flt64",F64});

        TokenMap.insert({"=",ASN});
        TokenMap.insert({"+",PLUS});
        TokenMap.insert({"-",MINUS});
        TokenMap.insert({"*",STAR});
        TokenMap.insert({"/",DIV});
        TokenMap.insert({"%",MODULO});
        TokenMap.insert({"+=",ASN_PLUS});
        TokenMap.insert({"*=",ASN_STAR});
        TokenMap.insert({"-=",ASN_MINUS});
        TokenMap.insert({"/=",ASN_DIV});
        TokenMap.insert({"%=",ASN_MOD});

        // TokenMap.insert({// "++",});
        // TokenMap.insert({// "--",});

        TokenMap.insert({"&&",CND_AND});
        TokenMap.insert({"||",CND_OR});
        TokenMap.insert({"!",CND_NOT});

        TokenMap.insert({"==",EQL});
        TokenMap.insert({"!=",NEQL});
        TokenMap.insert({"<",LT});
        TokenMap.insert({">",GT});
        TokenMap.insert({"<=",LEQL});
        TokenMap.insert({">=",GEQL});

        TokenMap.insert({"&",AND});
        TokenMap.insert({"|",OR});
        TokenMap.insert({"^",XOR});
        TokenMap.insert({"~",NOT});
        TokenMap.insert({"&=",ASN_AND});
        TokenMap.insert({"|=",ASN_OR});
        TokenMap.insert({"^=",ASN_XOR});

        TokenMap.insert({"<<",LSHIFT});
        TokenMap.insert({">>",RSHIFT});
        TokenMap.insert({"<<=",ASN_LSHIFT});
        TokenMap.insert({">>=",ASN_RSHIFT});

        TokenMap.insert({"..",DOTDOT});

        TokenMap.insert({"->",ARROW});
        TokenMap.insert({".",DOT});
        TokenMap.insert({";",SCOL});
        TokenMap.insert({":",COL});
        TokenMap.insert({"::",COLCOL});
        TokenMap.insert({",",COMMA});
        TokenMap.insert({"SPC",SPC});
        TokenMap.insert({"TAB",TAB});
        TokenMap.insert({"NEWL",NEWL});

        TokenMap.insert({"(",LPAREN});
        TokenMap.insert({")",RPAREN});
        TokenMap.insert({"{",LBRACE});
        TokenMap.insert({"}",RBRACE});
        TokenMap.insert({"[",LBRACK});
        TokenMap.insert({"]",RBRACK});

        TokenMap.insert({"<FEOF>",FEOF});
        TokenMap.insert({"<INVALID>",INVALID});
        }
        bool tokenizer(const std::string &src, std::vector<Lexeme> &toks, int begin, int end);
    };
}

