#include <iostream>
#include <string>
#include <charconv>
#include "../../include/lex/lex.hpp"
#include"../../include/Module.hpp"
// #include "lex/lex.hpp"
#include "../../include/Error.hpp"

namespace ast
{
    const char *TokenMap[_LAST] = {
        "self",
        "INT",
        "STR",
        "CHAR",
        "FLOAT",
        "IDEN",
        "null",

        "true",
        "false",
        "is",
        "mut",
        "while",
        "as",
        "in",
        "mod",
        "use",
        "type",
        "const",
        "static",
        "fn",
        "for",
        "let",
        "return",
        "continue",
        "break",
        "if",
        "else",
        "struct",
        "interface",
        "enum",
        "extern",
        "bool",
        "i8",
        "i16",
        "i32",
        "i64",
        "i128",
        "ui8",
        "ui16",
        "ui32",
        "ui64",
        "flt32", 
        "flt64",

        "=",
        "+",
        "-",
        "*",
        "/",
        "%",
        "+=",
        "*=",
        "-=",
        "/=",
        "%=",

        // "++",
        // "--",

        "&&",
        "||",

        "==",
        "!=",
        "<",
        ">",
        "<=",
        ">=",


        "&",
        "|",
        "^",
        "<<",
        ">>",

        "&=",
        "|=",
        "^=",
        "<<=",
        ">>=",

        "~",
        "!",

        "..",

        "->",
        ".",
        ";",
        ":",
        "::",
        ",",
        "SPC",
        "TAB",
        "NEWL",

        "(",
        ")",
        "{",
        "}",
        "[",
        "]",

        "@",

        "new",
        "del",

        "<FEOF>",
        "<INVALID>"
        };



    ast::StmtLoc *Lexer::getLoc(int Line, int Col) noexcept {
        return mgr.getLoc(mod, Line, Col);
    }


    bool Lexer::SkipWhiteSpace(const char *&CurBuff) {
        while (true)
        {
            char C = getAndAdvanceChar(CurBuff);
            while(isHorzizenalWhiteSpace(C)) {
                C = getAndAdvanceChar(CurBuff);
            }
            if(isVirticalWhiteSpace(C)) {
                StartLine = CurBuff;
                ++Line;
                continue;
            }
            break;    
        }
        /// decrementing pointer to terminator char
        --CurBuff;
        return true;
    }

    bool Lexer::SkipCommentLine(const char *&CurBuff) {
        while (true)
        {
            const char C = getAndAdvanceChar(CurBuff);
            if(C != 0) {
                if(C == '\n'){
                    StartLine = CurBuff;
                    Line++;
                    break;
                }
                continue;
            }
            break;
        }
        return true;

    }

    bool Lexer::SkipCommentBlock(const char *&CurBuff) {
        int CommentBlock = 1;
        const char *CommentBuf = CurBuff + 2;
        while (true)
        {
            const char C = getAndAdvanceChar(CommentBuf);
            if(C != 0){
                if(C == '\n') {
                    StartLine = CurBuff;
                    Line++;
                }
                
                const char NC = getAndAdvanceChar(CommentBuf);
                if(C == '/' && NC == '*') {
                    ++CommentBlock;
                }else if(C == '*' && NC == '/') {
                    --CommentBlock;
                }else {
                    --CommentBuf;
                }

                if(!CommentBlock) {
                    break;
                }
                continue;
            }
            break;    
        }
        /// decrementing CommentBuff to char '/'
        CurBuff = CommentBuf--;
        if(*CommentBuf != '/' || *(CommentBuf - 1) != '*') {
            err::err_out(getLoc(Line, CommentBuf - StartLine), "wrong multicomment symbol '",*CommentBuf,
                    "' found");
            return false;
        }
        return true;
    }

    bool Lexer::Tokenize() {
        const char *CurBuff = MainBuf;
        Line  = 1;
        Token_type ResultTok;
        const char *StartAnnot = CurBuff;
        while (true)
        {
        ResultTok = INVALID;
        StartAnnot = CurBuff;
        const char C = getAndAdvanceChar(CurBuff);
        std::cout<<C<<std::endl;
        switch (C)
        {
        case 0:
            goto LexDone;
        case '\n':   
        {
            Line++;
            StartLine = CurBuff;
            continue;
        }
        case ' ': 
        case '\t':  
        case '\f':  
        case '\v': 
        case '\r':
        {
            if(!SkipWhiteSpace(CurBuff)) {
                return false;
            }
            continue;
        }
        case '/':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_DIV;
                AdvanceChar(CurBuff);
            }
            else if (Char == '/') {
                if(!SkipCommentLine(CurBuff)) {
                    return false;
                }
                continue;
            }
            else if (Char == '*') {
                if(!SkipCommentBlock(CurBuff)) {    
                    return false;
                }
                continue;
            }else{
                ResultTok = Token_type::DIV;
            }
        }
        break;
        case '+':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_PLUS;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::PLUS;
            }
        }
        break;
        case '-':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_MINUS;
                AdvanceChar(CurBuff);
            }
            else if(Char == '>') {
                ResultTok = Token_type::ARROW;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::MINUS;
            }
        }
        break;
        case '=':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::EQL;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::ASN;
            }
        }
        break;
        case '*':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_STAR;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::STAR;
            }
        }
        break;
        case '&':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_AND;
                AdvanceChar(CurBuff);
            }
            else if(Char == '&') {
                AdvanceChar(CurBuff);
                ResultTok = Token_type::CND_AND;
            }
            else{
                ResultTok = Token_type::AND;
            }
        }
        break;
        case '|':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_OR;
                AdvanceChar(CurBuff);
            }
            else if(Char == '|') {
                ResultTok = Token_type::CND_OR;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::OR;
            }
        }
        break;
        case '^':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_XOR;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::XOR;
            }
        }
        break;
        case '>':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::GEQL;
                AdvanceChar(CurBuff);
            }else if(Char == '>') {
                char Char = getAndAdvanceChar(CurBuff);
                if(Char == '=') {
                    ResultTok = Token_type::ASN_RSHIFT;
                    AdvanceChar(CurBuff);
                }else
                    ResultTok = Token_type::RSHIFT;
            }else{
                ResultTok = Token_type::GT;
            }
        }
        break;
        case '<':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::LEQL;
                AdvanceChar(CurBuff);
            }
            else if(Char == '<') {
                char Char = getAndAdvanceChar(CurBuff);
                if(Char == '=') {
                    ResultTok = Token_type::ASN_LSHIFT;
                    AdvanceChar(CurBuff);
                }else
                    ResultTok = Token_type::LSHIFT;
            }
            else{
                ResultTok = Token_type::LT;
            }
        }
        break;
        case '%':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::ASN_MOD;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::MODULO;
            }
        }
        break;
        case '!':
        {
            char Char = getChar(CurBuff);
            if(Char == '=') {
                ResultTok = Token_type::NEQL;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::CND_NOT;
            }
        }
        break;
        case '~':
        {
            ResultTok = Token_type::NOT;
        }
        break;
        case '\'':
        {
            char Char = getAndAdvanceChar(CurBuff);
            LxmS.emplace_back(getLoc(Line, StartAnnot - StartLine), (int64_t)Char, CHAR);
            continue;
        }
        case '\"':
        {
                    std::cout<<*CurBuff<<std::endl;

            const char *StartAnnot = CurBuff;
            if(!LexConstString(CurBuff)){
                err::err_out(getLoc(Line, StartAnnot - StartLine), "invalid string found");
                return false;
            }
            // decrementing pointer to point to before \" char 
            const char *EndAnnot = CurBuff - 1;

            String CStr(StartAnnot, EndAnnot - StartAnnot);
            RemoveSlashes(CStr);
            LxmS.emplace_back(getLoc(Line, StartAnnot - StartLine), CStr, STR);
            continue;
        }
        case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8': case '9':
        {
            // decrementing pointer to point to first digit char 
            const char *StartAnnot = --CurBuff;
            int Base = 10;
            ResultTok = INT;
            if(!LexConstNumerical(CurBuff, Base, ResultTok)) {
                err::err_out(getLoc(Line, StartAnnot - StartLine), "unknown token found");
                    return false;
            }

            const char *EndAnnot = CurBuff;

            String Num(StartAnnot, EndAnnot - StartAnnot);
            if(ResultTok == FLOAT){
                long double f = std::stold(Num.c_str());
                LxmS.emplace_back(getLoc(Line, StartAnnot - StartLine), Num, f, ResultTok);
                continue;
            }
            int64_t intval;
            if(Num.size() > 2 && Base != 10) {
                Num = Num.substr(Base == 8 ? 1 : 2);
            }

            std::from_chars(Num.c_str(), Num.c_str() + Num.size(), intval, Base);
            LxmS.emplace_back(getLoc(Line, StartAnnot - StartLine), Num, intval, ResultTok);
            continue;
        }
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
        case 'H': case 'I': case 'J': case 'K': case 'L' : case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':    /*'U'*/
        case 'V': case 'W': case 'X': case 'Y': case 'Z':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': 
        case 'v': case 'w': case 'x': case 'y': case 'z':
        case '_':
        {
            // decrementing pointer to point to first char 
            const char *StartAnnot = --CurBuff;
            if(!LexIdentifier(CurBuff)) {
                return false;
            }

            const char *EndAnnot = CurBuff;
            String Ident(StartAnnot, EndAnnot - StartAnnot);
            Token_type ResTok = getKeyWord(Ident);
            LxmS.emplace_back(getLoc(Line, StartAnnot - StartLine), Ident, ResTok);
            continue; 
        }
        case '(':
        {
            ResultTok = Token_type::LPAREN;
        }
        break;
        case ')':
        {
            ResultTok = Token_type::RPAREN;
        }
        break;
        case '[':
        {
            ResultTok = Token_type::LBRACK;
        }
        break;
        case ']':
        {
            ResultTok = Token_type::RBRACK;
        }
        break;
        case '{':
        {
            ResultTok = Token_type::LBRACE;
        }
        break;
        case '}':
        {
            ResultTok = Token_type::RBRACE;
        }
        break;
        case '.':
        {
            char Char = getChar(CurBuff);
            if(Char == '.') {
                ResultTok = Token_type::DOTDOT;
                AdvanceChar(CurBuff);
            }
            else{
                ResultTok = Token_type::DOT;
            }
        }
        break;
        case '@':
        {
            ResultTok = Token_type::AT;
        }
        break;
        case ',':
        {
            ResultTok = Token_type::COMMA;
        }
        break;
        case ';':
        {
            ResultTok = Token_type::SCOL;
        }
        break;
        case ':':
        {
            const char Char = getChar(CurBuff); 
            if(Char == ':') {
                ResultTok = Token_type::COLCOL;
                AdvanceChar(CurBuff);
            }else
                ResultTok = Token_type::COL;
        }
        break;
        default:
        {
            err::err_out(getLoc(Line, StartAnnot - StartLine), "unknown token '",C,
                "' found");
                return false;
        }
        }
        if(ResultTok == INVALID) {
            err::err_out(getLoc(Line, StartAnnot - StartLine), "unknown token '",C,
                "' found");
                return false;
        }
        LxmS.emplace_back(getLoc(Line, StartAnnot - StartLine), ResultTok);
        }
LexDone:
        LxmS.emplace_back(getLoc(Line, StartAnnot - StartLine), FEOF);
        return true;
    }

    
    Token_type Lexer::getKeyWord(const String &Str) {
        if(Str == TokenMap[FOR])return FOR;
        if(Str == TokenMap[WHILE])return WHILE;
        if(Str == TokenMap[EXTERN])return EXTERN;
        if(Str == TokenMap[IF])return IF;
        if(Str == TokenMap[IS])return IS;
        if(Str == TokenMap[AS])return AS;
        if(Str == TokenMap[ELSE])return ELSE;
        if(Str == TokenMap[FN])return FN;
        if(Str == TokenMap[MUT])return MUT;
        if(Str == TokenMap[SELF])return SELF;
        if(Str == TokenMap[STRUCT])return STRUCT;
        if(Str == TokenMap[METHOD])return METHOD;
        if(Str == TokenMap[NIL])return NIL;
        if(Str == TokenMap[CONTINUE])return CONTINUE;
        if(Str == TokenMap[BREAK])return BREAK;
        if(Str == TokenMap[TRUE])return TRUE;
        if(Str == TokenMap[TYPE])return TYPE;
        if(Str == TokenMap[RETURN])return RETURN;
        if(Str == TokenMap[FALSE])return FALSE;
        if(Str == TokenMap[CONST])return CONST;
        if(Str == TokenMap[STATIC])return STATIC;
        if(Str == TokenMap[LET])return LET;
        if(Str == TokenMap[IN])return IN;
        if(Str == TokenMap[ENUM])return ENUM;
        if(Str == TokenMap[MOD])return MOD;
        if(Str == TokenMap[USE])return USE;
        if(Str == TokenMap[BOOL])return BOOL;
        if(Str == TokenMap[I8])return I8;
        if(Str == TokenMap[I16])return I16;
        if(Str == TokenMap[I32])return I32;
        if(Str == TokenMap[I64])return I64;
        if(Str == TokenMap[I128])return I128;
        if(Str == TokenMap[UI8])return UI8;
        if(Str == TokenMap[UI16])return UI16;
        if(Str == TokenMap[UI32])return UI32;
        if(Str == TokenMap[UI64])return UI64;
        if(Str == TokenMap[F32])return F32;
        if(Str == TokenMap[F64])return F64;

        if(Str == TokenMap[NEW])return NEW;
        if(Str == TokenMap[DEL])return DEL;

        return IDEN;
    }

    bool Lexer::LexIdentifier(const char *&CurBuff){
        while (true)
        {   
            char C = getAndAdvanceChar(CurBuff);
            if(C == 0) {
                break;
            }
            if((C >= 'A' && C <= 'Z') || (C >= 'a' && C <= 'z') || (C >= '0' && C <= '9') || C == '_' || C == '$'){
                continue;
            }
            break;
        }
        /// decrementing pointer to terminator char 
        --CurBuff;
        return true;
    }

    bool Lexer::LexConstString(const char *&CurBuff){
        const char *StringStart = CurBuff;
        const char *StringBuff = CurBuff;
        int BaseSlash = 0;
        while(true){
            char C = getAndAdvanceChar(StringBuff);
            if(C == 0 )
                break;

            if(C == '\\') {
                ++BaseSlash;
                continue;
            }
            if(C == '\"' && BaseSlash%2 == 0)
                break;
            
            BaseSlash = 0;
        }
        // save pointer to CurBuff which is pointing to string terminator char '\"' if any
        CurBuff = StringBuff;

        // decrement pointer to last char '\"'
        char C = getChar(--StringBuff);
        if(C != '\"'){
            err::err_out(getLoc(Line, StringBuff - StringStart), "invalid string symbol '",C,
                    "' found");
            return false;
        }
        return true;
    };

    bool Lexer::LexConstNumerical(const char *&CurBuff, int &Base, Token_type &ResultTok){
        const char *DigitStartPoint = CurBuff;
        const char *DigitSequance = CurBuff;
        bool HasDot = false;
        bool FoundBase = false;
        Base = 10;

        while(true){
            const char DigitChar = getAndAdvanceChar(DigitSequance);
            switch(DigitChar){
                case 0:
                    break;
                case '0':
                {
                    if(DigitSequance == DigitStartPoint + 1){
                        char Char = getChar(DigitSequance);
                        if(Char == 'x' || Char == 'X') {
                            Base = 16; 
                            FoundBase = true;
                            break;
                        }
                        Base = 8;
                    }
                    break;
                }
                case 'A': case 'a': case 'B': case 'b':
                case 'C': case 'c': case 'D': case 'd':
                case 'E': case 'e': case 'F': case 'f':
                {
                    if(Base == 16)break;
                    goto fail;
                }
                case '1':
                    break;
                case '2':
                case '3': case '4':
                case '5': case '6':
                {
                    if(Base > 2)break;
                    goto fail;                 
                }
                case '7':
                case '8':
                case '9':
                {
                    if(Base >= 8)break;
                    goto fail;
                }
                case '.':
                {
                    if((Base != 10 && FoundBase)){
                        err::err_out(getLoc(Line, DigitSequance - DigitStartPoint), 
                            "encountered dot (.) character when Base is not 10 (",
                                Base, ") ");
                        return false;
                    } else if(!HasDot) {
                        char NextDigit = getChar(DigitSequance);
                        if(NextDigit >= '0' && NextDigit <= '9'){
                          HasDot = true;
                          ResultTok = FLOAT;
                        }else{
                            goto fail;
                        }
                    }else{
                        err::err_out(getLoc(Line, DigitSequance - DigitStartPoint),
                        "encountered dot (.) character when the number being "
                        "retrieved (from column ",
                        (int)(DigitSequance - DigitStartPoint) + 1, ") already had one");
                        return false;
                    }
                    FoundBase = true;
                    break;
                } 
                default:
                {
                    fail:
                        if(isalnum(DigitChar)){
                            err::err_out(getLoc(Line, DigitSequance - DigitStartPoint), "invalid symbol '", DigitChar,
                            "' found");
                            return false;
                        }
                        goto Done;
                }
            }

            // if it's first digit and not 0
            if((DigitSequance - DigitStartPoint == 1) && DigitChar != '0') {
                FoundBase = true;
            }
        }
    Done:
        // decrementing pointer to last terminator char
        CurBuff = --DigitSequance;
        return true;
    }


    bool Lexer::RemoveSlashes(String &s) {
        for(auto it = s.begin(); it != s.end(); ++it) {
		if(*it == '\\') {
			if(it + 1 >= s.end()) continue;
			it = s.erase(it);
			if(*it == '0') *it = '\0';
			else if(*it == 'a') *it = '\a';
			else if(*it == 'b') *it = '\b';
#if !defined(OS_WINDOWS)
			else if(*it == 'e') *it = '\e';
#endif
			else if(*it == 'f') *it = '\f';
			else if(*it == 'n') *it = '\n';
			else if(*it == 'r') *it = '\r';
			else if(*it == 't') *it = '\t';
			else if(*it == 'v') *it = '\v';
		}
	}
        return true;
    }
}
