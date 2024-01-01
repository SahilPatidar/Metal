#include <iostream>
#include <string>
#include <charconv>
#include "../../include/lex/lex.hpp"
#include"../../include/Module.hpp"
// #include "lex/lex.hpp"
#include "../../include/Error.hpp"

namespace lex
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

    #define CUR (src[i])
    #define NXT (i < str_len?src[i+1]:0)
    #define PRV (str_len > 0&&i > 0?src[i-1]:0)

    ast::StmtLoc *Lexer::getLoc(size_t line, size_t col) noexcept {
        return mgr.getLoc(mod, line, col);
    }

    bool Lexer::tokenizer(const std::string &src, std::vector<Lexeme> &toks, size_t begin, size_t end){
        size_t i = begin;
        bool comment_line = false;
        bool comment_block = false;
        size_t line = 1;
        size_t str_len = src.size();
        size_t start_pos = 0;
        size_t line_start = 0;
        while(i < end){
            start_pos = i;
            if(CUR=='\n'){
                ++line;
                line_start = i+1;
            }

            if(comment_line){
                if(CUR == '\n')comment_line=false;
                ++i;
                continue;
            }
            
            if(isspace(src[i])){
                i++;
                continue;
            }
            if(CUR == '*' && NXT == '/'){
                if(!comment_block){
                    err::err_out(getLoc(line, i - line_start), "wrong multicomment symbol '",CUR,
                    "' found");
                    return false;
                }

                comment_block = false;
                i+=2;
                continue;
            }
            if(CUR == '/' && NXT == '*'){
                comment_block = true;
                i+=2;
                continue;
            }
            if(comment_block){
                i++;
                continue;
            }

            if(CUR == '/'&& NXT == '/'){
                comment_line = true;
                i++;
                continue;
            }
            if((CUR == '.' && (isalpha(NXT) || NXT == '_') && !isalnum(PRV) &&
		    PRV != '_' && PRV != ')' && PRV != ']' && PRV != '\'' && PRV != '"') ||
		   isalpha(CUR) || CUR == '_') {

                std::string str = get_string(src, i);

                if(str == ""){
                    return false;
                }
                Token_type tok_name = get_keyword(str);
                toks.emplace_back(getLoc(line, i - line_start), str, tok_name);
                continue;
            }

            if(isdigit(src[i])){
                int base = 10;
                Token_type type = INT;
                std::string str;
                if(!get_num(src, line, i, base, str, type)){
                    err::err_out(getLoc(line, i - line_start), "unknown token '",str,
                    "' found");
                    return false;
                }
                if(str.empty()){
                    return false;
                }
                
                if(type == FLOAT){
                    // std::from_chars(str.c_str(), str.c_str() + str.size(), f);
                    double f = std::stold(str.c_str());
                    toks.emplace_back(getLoc(line, i - line_start), str,f,type);
                    continue;
                }
                int64_t intval;
                if(str.size() > 2 && base != 10) {
                    str = str.substr(base == 8 ? 1 : 2);
                }
                std::from_chars(str.c_str(), str.c_str() + str.size(), intval, base);
                toks.emplace_back(getLoc(line, i - line_start), str,intval,type);
                continue;

            }

            if(CUR == '\"'||CUR == '\'') {
                std::string str;
                char quote = '\"';
                if(!get_const_string(src, i, line, quote, str)){
                    err::err_out(getLoc(line, i - line_start), "unknown string '",str,
                    "' found");
                    return false;
                }

                if(quote=='\"')
                    toks.emplace_back(getLoc(line, i - line_start), str, STR);
                else{
                    toks.emplace_back(getLoc(line, i - line_start), str, (int64_t)str[0], CHAR);
                }
                continue;
            }
            Token_type type = INVALID;
            if(!get_operator(src, type, i)){
                err::err_out(getLoc(line, i - line_start), "unknown operator '",CUR,
                "' found");
                return false;
            }
            toks.emplace_back(getLoc(line, i - line_start), TokenMap[type], type);
        }
        toks.emplace_back(getLoc(line, i - line_start) , TokenMap[FEOF], FEOF);
        return true;
    }

    
    Token_type Lexer::get_keyword(std::string &src) {
        if(src == TokenMap[FOR])return FOR;
        if(src == TokenMap[WHILE])return WHILE;
        if(src == TokenMap[EXTERN])return EXTERN;
        if(src == TokenMap[IF])return IF;
        if(src == TokenMap[IS])return IS;
        if(src == TokenMap[AS])return AS;
        if(src == TokenMap[ELSE])return ELSE;
        if(src == TokenMap[FN])return FN;
        if(src == TokenMap[MUT])return MUT;
        if(src == TokenMap[SELF])return SELF;
        if(src == TokenMap[STRUCT])return STRUCT;
        if(src == TokenMap[METHOD])return METHOD;
        if(src == TokenMap[NIL])return NIL;
        if(src == TokenMap[CONTINUE])return CONTINUE;
        if(src == TokenMap[BREAK])return BREAK;
        if(src == TokenMap[TRUE])return TRUE;
        if(src == TokenMap[TYPE])return TYPE;
        if(src == TokenMap[RETURN])return RETURN;
        if(src == TokenMap[FALSE])return FALSE;
        if(src == TokenMap[CONST])return CONST;
        if(src == TokenMap[STATIC])return STATIC;
        if(src == TokenMap[LET])return LET;
        if(src == TokenMap[IN])return IN;
        if(src == TokenMap[ENUM])return ENUM;
        if(src == TokenMap[MOD])return MOD;
        if(src == TokenMap[USE])return USE;
        if(src == TokenMap[BOOL])return BOOL;
        if(src == TokenMap[I8])return I8;
        if(src == TokenMap[I16])return I16;
        if(src == TokenMap[I32])return I32;
        if(src == TokenMap[I64])return I64;
        if(src == TokenMap[I128])return I128;
        if(src == TokenMap[UI8])return UI8;
        if(src == TokenMap[UI16])return UI16;
        if(src == TokenMap[UI32])return UI32;
        if(src == TokenMap[UI64])return UI64;
        if(src == TokenMap[F32])return F32;
        if(src == TokenMap[F64])return F64;

        if(src == TokenMap[NEW])return NEW;
        if(src == TokenMap[DEL])return DEL;

        return IDEN;
    }

    std::string  Lexer::get_string(const std::string &src, size_t &i){
        size_t str_len = src.size();
        std::string str;
        while (i < str_len)
        {   
            if(!isalnum(src[i]) && CUR != '_'){
               break;
            }
            str.push_back(src[i]);
            ++i;
        }
        return str;
    }

    bool Lexer::get_const_string(const std::string &src, size_t &i, size_t &line, char &quote, std::string &str){
        quote = CUR;
        int start_pos = i;
        ++i;
        int str_len = src.size();
        int back_slash = 0;
        while(i < str_len){
            if(CUR == '\\') {
                ++back_slash;
                str.push_back(CUR);
                ++i;
                continue;
            }
            if(CUR == quote && back_slash%2 == 0)
                break;
            
            str.push_back(CUR);
             ++i;
            if(quote == '\''){
                if(CUR != quote){
                    err::err_out(getLoc(line, i - start_pos), "invalid string symbol '",CUR,
                    "' found");
                    return false;
                }
                break;
            }
            back_slash = 0;
        }
        // if(CUR != quote){
        //     i = start_pos;
        //     return false;
        // }
        ++i;
        remove_slashes(str);
        return true;
    };

    bool Lexer::get_num(const std::string &src, size_t line, size_t &i, size_t base, std::string &num, Token_type &type){
        int str_len = src.size();
        bool hex = false;
        int frist_digit = i;
        int dot_pos = -1;
        while(i < str_len){
            const char cur = CUR;
            const char nxt = NXT;
            if(i == frist_digit && cur == '0' && (nxt == 'x'||nxt == 'X')){
                hex = true;
                base = 16;
                num.push_back(cur);
                num.push_back(nxt);
                i+=2;
                continue;
            }
            switch(cur){
                case '0':
                {
                    break;
                }
                case 'A':
                case 'a':
                case 'B':
                case 'b':
                case 'C':
                case 'c':
                case 'D':
                case 'd':
                case 'E':
                case 'e':
                case 'F':
                case 'f':
                {
                    if(hex)break;
                    goto fail;
                }
                case '1':
                    break;
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                {
                    if(hex||base > 2)break;
                    goto fail;                 
                }
                case '7':
                case '8':
                case '9':
                {
                    if(hex||base >= 8)break;
                    goto fail;
                }
                case '.':
                {
                    if(base != 10 || hex){
                        err::err_out(getLoc(line, frist_digit - i), "invalid symbol '",CUR,
                        "' found");
                        return false;
                    } else if(dot_pos == -1) {
                        if(nxt >= '0' && nxt <='9'){
                          dot_pos = i;
                          type = FLOAT;
                        }else{
                            goto fail;
                        }
                    }else{
                        printf("encountered double dot in single number\n");
                        return false;
                    }
                    break;
                } 
                default:
                {
                    fail:
                        if(isalnum(cur)){
                            err::err_out(getLoc(line, frist_digit - i), "invalid string symbol '",CUR,
                            "' found");
                            return false;
                        }else{
                            return true;
                        }
                }
            }

            num.push_back(cur);
            ++i;
        }
        return true;
    }

    #define SET(type) \
      op_type = type; \
      break                                 

    bool Lexer::get_operator(const std::string &src, Token_type &op_type, size_t &i) {
        int str_len = src.size();
        int first_op = i;
        switch(CUR){
            case '+':
            {
                if(i < str_len - 1){
                    // if(NXT == '+'){
                    //     ++i;
                    //    SET(INC);
                    // }else 
                    if(NXT == '='){
                        ++i;
                        SET(ASN_PLUS);
                    }
                }
               SET(PLUS);
            }
            case '-':
             {
                if(i < str_len - 1){
                    // if(NXT == '-'){
                    //     ++i;
                    //    SET(DEC);
                    // }else 
                    if(NXT == '='){
                        ++i;
                       SET(ASN_MINUS);
                    }else if(NXT == '>'){
                        ++i;
                        SET(ARROW);
                    }
                }
                SET(MINUS);
            }
            case '%':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASN_MOD); 
                    }
                }
                SET(MODULO);
            }
            case '*':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASN_STAR);
                    }
                }
                SET(STAR);
            }
            case '=':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(EQL);
                    }
                }
                SET(ASN);
            }
            case '/':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASN_DIV);
                    }
                }
                SET(DIV);
            }
            case '&':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASN_AND);
                    }else if(NXT == '&'){
                        ++i;
                        SET(CND_AND);
                    }
                }
                SET(AND);
            }
            case '|':
             {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASN_OR);
                    }else if(NXT == '|'){
                        ++i;
                        SET(CND_OR);
                    }
                }
                SET(OR);
            }
            case '!':
             {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(NEQL);
                    }
                }
                SET(CND_NOT);
            }
            case '~':
            {
                SET(NOT);
            }
            case '<':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(LEQL);
                    }else if(NXT == '<'){
                        
                        if(i < str_len - 1){
                            ++i;
                            if(NXT == '='){
                                SET(ASN_LSHIFT);
                            }
                        }
                        SET(LSHIFT);
                    }
                }
                SET(LT);
            }
            case '>':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(GEQL);
                    }else if(NXT == '<'){
                        ++i;
                        if(i < str_len - 1){
                            if(NXT == '='){
                                SET(ASN_RSHIFT);
                            }
                        }
                        SET(RSHIFT);
                    }
                }
                SET(GT);
            }
            case '^':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASN_XOR);
                    }
                }
                SET(XOR);
            }
            case ':':
                if(i < str_len - 1){
                    if(NXT == ':'){
                        ++i;
                        SET(COLCOL);
                    }
                }
                SET(COL);
            case ',':
                SET(COMMA);
            case ';':
                SET(SCOL);
            case '\t':
                SET(TAB);
            case '\n':
                SET(NEWL);
            case ' ':
                SET(SPC);
            case '.':
            {
                if(i < str_len - 1){
                    if(NXT == '.'){
                        ++i;
                                SET(DOTDOT);

                    }
                }
                SET(DOT);
            }
            case '[':
                SET(LBRACK);
            case ']':
                SET(RBRACK);
            case '(':
                SET(LPAREN);
            case ')':
                SET(RPAREN);
            case '{':
                SET(LBRACE);
            case '}':
                SET(RBRACE);
            case '@':
                SET(AT);
            default:
            op_type = INVALID;
            return false;
        }
        ++i;
        return true;
    }

    bool Lexer::remove_slashes(std::string &s) {
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
