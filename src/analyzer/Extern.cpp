#include"../../include/analyzer/Sema.hpp"
#include"../../include/Error.hpp"
// #include"analyzer/TypeChecker.hpp"

namespace ast {

bool isValidFmt(String &fmt) {
    if(fmt == "%d" || fmt == "%hd" || fmt == "%hhd" || 
        fmt == "%lld" || fmt == "%u" || fmt == "%hu" || 
        fmt == "%hhu" || fmt == "%llu" || fmt == "%c" || 
        fmt == "%s" || fmt == "%p" || fmt == "%f") {
        return true;
    }
    return false;
}

bool IsValidArgForFmt(String &fmt, Type *Ty, bool isConst) {
    if(fmt == "%d") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 32) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hd") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 16) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hhd") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 8) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%lld") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 64) {
            return false;
        }
        if(!ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%u") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 32) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hu") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 8) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%hhu") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 16) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%llu") {
        if(!Ty->isIntTy()) {
            return false;
        }

        IntType *ITy = static_cast<IntType *>(Ty);
        if(ITy->getbit() == 1){
            return true;
        }
        if(isConst) {
            return true;
        }
        if(ITy->getbit() != 64) {
            return false;
        }
        if(ITy->isSignInt()) {
            return false;
        }
    }else if(fmt == "%c") {
        if(!Ty->isIntTy()) {
            return false;
        }
        IntType *ITy = static_cast<IntType *>(Ty);

        if(ITy->getbit() != 8) {
            return false;
        }
    }else if(fmt == "%s") {
        if(!Ty->isPointerTy() && !Ty->isArrayTy()) {
            return false;
        }
        if(Ty->isPointerTy()) {
            PointerType *PTy = static_cast<PointerType *>(Ty);
            if(!PTy->getTo()->isIntTy()) {
                return false;
            }
            IntType *ITy = static_cast<IntType *>(PTy->getTo());
            if(ITy->getbit() != 8) {
                return false;
            }
        }else {
            ArrayType *ATy = static_cast<ArrayType *>(Ty);
            if(!ATy->getArrType()->isIntTy()) {
                return false;
            }
            IntType *ITy = static_cast<IntType *>(ATy->getArrType());
            if(ITy->getbit() != 8) {
                return false;
            }
        }
    }else if(fmt == "%p") {
        if(!Ty->isRefTy() &&  !Ty->isPointerTy() && !Ty->isArrayTy()) {
            return false;
        }
    }else if(fmt == "%f") {
        if(!Ty->isFltTy()) {
            return false;
        }
    }else {
        return false;
    }
    return true;
}

String getFmt(String &s, String &fmt, size_t &pos) {
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
    String lhsN = lhs->toString();
    String rhsN = rhs->toString();

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
    String fmt = "";
    String StrArg = Str->getLexeme().getStr();
    if(field.size() > 1){
        size_t argIdx = 1;
        for(size_t i = 0, siz = StrArg.size(); i < siz; i++) {
            if(StrArg[i] == '%') {
                if(argIdx == field.size()) {
                    err::err_out(field[argIdx], "too few args");
                    return false;
                }
                String fmt = "%";
                getFmt(StrArg, fmt, i);
                if(fmt.empty()) {
                    err::err_out(field[argIdx], "invalid formate string");
                    return false;
                }

                if(!isValidFmt(fmt)) {
                    err::err_out(field[argIdx], "invalid formate string `", fmt,"`");
                    return false;
                }
                if(!IsValidArgForFmt(fmt, field[argIdx]->getTypeInfo(), field[argIdx]->IsConst())) {
                    err::err_out(field[argIdx], "invalid formate string `", fmt,"` for arg type `", field[argIdx]->getTypeInfo()->toStr(),"`");
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
    String lhsN = lhs->toString();
    String rhsN = rhs->toString();

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
    String fmt = "";
    String StrArg = Str->getLexeme().getStr();
    if(field.size() > 1){
        size_t argIdx = 1;
        for(size_t i = 0, siz = StrArg.size(); i < siz; i++) {
            if(StrArg[i] == '%') {
                if(argIdx == field.size()) {
                    err::err_out(field[argIdx], "too few args");
                    return false;
                }
                Type *ArgTy = field[argIdx]->getTypeInfo();
                if(!ArgTy->isRefTy() && !ArgTy->isPointerTy()) {
                    err::err_out(field[argIdx], "invalid arg for format string");
                    return false;
                }
                String fmt = "%";
                getFmt(StrArg, fmt, i);
                if(fmt.empty()) {
                    err::err_out(field[argIdx], "invalid formate string");
                    return false;
                }
                Type *Ty = nullptr;
                if(ArgTy->isRefTy()){
                    Ty = static_cast<RefType *>(ArgTy)->getTo();
                }else if(ArgTy->isPointerTy()) {
                    Ty = static_cast<PointerType *>(ArgTy)->getTo();
                }
                if(!isValidFmt(fmt)) {
                    err::err_out(field[argIdx], "invalid formate string `", fmt,"`");
                    return false;
                }
                if(!IsValidArgForFmt(fmt, Ty, field[argIdx]->IsConst())) {
                    err::err_out(field[argIdx], "invalid formate string `", fmt,"` for arg type `", Ty->toStr(),"`");
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