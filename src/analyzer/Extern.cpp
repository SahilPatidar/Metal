#include"../../include/analyzer/Sema.hpp"
#include"../../include/Error.hpp"
// #include"analyzer/TypeChecker.hpp"

namespace ast {

bool IsValidFmt(std::string &fmt, Type *Ty) {
    if(fmt == "%d") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }

        if(ITy->getbit() != 32) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hd") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(ITy->getbit() != 16) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hhd") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(ITy->getbit() != 8) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%lld") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(ITy->getbit() != 64) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%u") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(ITy->getbit() != 32) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hu") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(ITy->getbit() != 8) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hhu") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(ITy->getbit() != 16) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%llu") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(ITy->getbit() != 64) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%c") {
        if(!Ty->Is(Type::IntTy)) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);

        if(ITy->getbit() != 8) {
            return false;
        }
    }else if(fmt == "%s") {
        if(!Ty->Is(Type::PointerTy) && !Ty->Is(Type::ArrayTy)) {
            return false;
        }
        if(Ty->Is(Type::PointerTy)) {
            PointerType *PTy = static_cast<PointerType *>(Ty);
            if(!PTy->getTo()->Is(Type::IntTy)) {
                return false;
            }
            IntType *ITy = static_cast<IntType *>(PTy->getTo());
            if(ITy->getbit() != 8) {
                return false;
            }
        }else {
            ArrayType *ATy = static_cast<ArrayType *>(Ty);
            if(!ATy->getArrType()->Is(Type::IntTy)) {
                return false;
            }
            IntType *ITy = static_cast<IntType *>(ATy->getArrType());
            if(ITy->getbit() != 8) {
                return false;
            }
        }
    }else if(fmt == "%p") {
        if(!Ty->Is(Type::RefTy) &&  !Ty->Is(Type::PointerTy) && !Ty->Is(Type::ArrayTy)) {
            return false;
        }
    }else if(fmt == "%f") {
        if(!Ty->Is(Type::FltTy)) {
            return false;
        }
    }else {
        return false;
    }
    return true;
}

std::string getFmt(std::string &s, std::string &fmt, size_t &pos) {
    size_t length = s.size();
    pos++;
    while(pos < length && ((s[pos] >= '0' && s[pos] <= '9') || (s[pos] >= 'a' && s[pos] <= 'z') || (s[pos] >= 'A' && s[pos] <= 'Z'))) {
        fmt.push_back(s[pos]);
        pos++;
    }
    return fmt;
}


bool TypeChecker::CheckPrintExtCall(Expression &Expr) {
    Ast *&lhs = Expr.getLhs();
    Ast *&rhs = Expr.getRhs();
    std::string lhsN = lhs->toString();
    std::string rhsN = rhs->toString();

    std::vector<Ast *> &field = static_cast<FieldExpr*>(rhs)->getArgs();
    if(!field[0]->Is(NodeStrLit)) {
        err::err_out(field[0], "format argument must be a string literal");
        return false;
    }
    StringLiteral *Str = static_cast<StringLiteral *>(field[0]);
    if(Str->ischar()){
        err::err_out(field[0], "format argument must be a string literal");
        return false;
    }
    std::string fmt = "";
    std::string StrArg = Str->getLexeme().getStr();
    if(field.size() > 1){
        size_t argIdx = 1;
        for(size_t i = 0, siz = StrArg.size(); i < siz; i++) {
            if(StrArg[i] == '%') {
                if(argIdx == field.size()) {
                    err::err_out(field[argIdx], "too few args");
                    return false;
                }
                std::string fmt = "%";
                getFmt(StrArg, fmt, i);
                if(fmt.empty()) {
                    err::err_out(field[argIdx], "invalid formate string");
                    return false;
                }
                
                if(!IsValidFmt(fmt, field[argIdx]->getTypeInfo())) {
                    err::err_out(field[argIdx], "invalid formate string `"+fmt+"` for arg");
                    return false;
                }
                argIdx++;
            }
        }
        if(argIdx != field.size()) {
            err::err_out(field[argIdx], "too many args");
            return false;
        }
    }
    return true;
}

bool TypeChecker::CheckScanfExtCall(Expression &Expr) {
    Ast *&lhs = Expr.getLhs();
    Ast *&rhs = Expr.getRhs();
    std::string lhsN = lhs->toString();
    std::string rhsN = rhs->toString();

    std::vector<Ast *> &field = static_cast<FieldExpr*>(rhs)->getArgs();
    if(!field[0]->Is(NodeStrLit)) {
        err::err_out(field[0], "format argument must be a string literal");
        return false;
    }
    StringLiteral *Str = static_cast<StringLiteral *>(field[0]);
    if(Str->ischar()){
        err::err_out(field[0], "format argument must be a string literal");
        return false;
    }
    std::string fmt = "";
    std::string StrArg = Str->getLexeme().getStr();
    if(field.size() > 1){
        size_t argIdx = 1;
        for(size_t i = 0, siz = StrArg.size(); i < siz; i++) {
            if(StrArg[i] == '%') {
                if(argIdx == field.size()) {
                    err::err_out(field[argIdx], "too few args");
                    return false;
                }
                Type *ArgTy = field[argIdx]->getTypeInfo();
                if(!ArgTy->Is(Type::RefTy) && !ArgTy->Is(Type::PointerTy)) {
                    err::err_out(field[argIdx], "invalid arg for format string");
                    return false;
                }
                std::string fmt = "%";
                getFmt(StrArg, fmt, i);
                if(fmt.empty()) {
                    err::err_out(field[argIdx], "invalid formate string");
                    return false;
                }
                Type *Ty = nullptr;
                if(ArgTy->Is(Type::RefTy)){
                    Ty = static_cast<RefType *>(ArgTy)->getTo();
                }else if(ArgTy->Is(Type::PointerTy)) {
                    Ty = static_cast<PointerType *>(ArgTy)->getTo();
                }
                if(!IsValidFmt(fmt, Ty)) {
                    err::err_out(field[argIdx], "invalid formate string");
                    return false;
                }
                argIdx++;
            }
        }
        if(argIdx != field.size()) {
            err::err_out(field[argIdx], "too many args");
            return false;
        }
    }
    return true;
}





} 