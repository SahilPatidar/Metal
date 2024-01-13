#include"../../include/analyzer/Sema.hpp"
#include"../../include/analyzer/Value.hpp"
#include"../../include/Error.hpp"
#include"../../include/Module.hpp"
// #include"analyzer/TypeChecker.hpp"

namespace ast {


bool TypeChecker::visit(Identifier *AstNode, Ast **Base) {
    dumpSema("Identifier");
    Ast *&Decl = AstNode->getDecl();
    if(!Decl) {
        err::err_out(AstNode, AstNode->toString(), " not a value");
        return false;
    }
    Type *&Ty = Decl->getTypeInfo();
    if(!Ty) {
        if(!visit(Decl, &Decl)){
            return false;
        }
    }

    if(!Ty){
        err::err_out(AstNode, "type is not available for name " ,  Decl->toString());
        return false;
    }

     
    Lexeme &IDN = AstNode->getLexeme();
    String N = IDN.getStr();
    if(Decl->Is(NodeEnum)) {
        IDN.setDataStr(static_cast<EnumExpr *>(Decl)->getName().getStr());
        /*
            let some_var any_enum_ty = some_value 
                |
                | converted to 
                |
            let some_var i32 = some_value 
        */
        if(AstNode->IsTy()) {
            *Base = PremitiveType::Create(mgr, AstNode->getStmtLoc(), Lexeme(AstNode->getStmtLoc(), "i32", I32));
            (*Base)->setType(Decl->getTypeInfo());
            return true;
        }
    }else if(Decl->Is(NodeStructStm)){
        IDN.setDataStr(static_cast<StructStmt *>(Decl)->getName().getStr());
    }else if(Decl->Is(NodeFNStm)){
        FunctionDef *FnDecl = static_cast<FunctionDef *>(Decl);
        IDN.setDataStr(FnDecl->getFnProto()->getFuncName().getStr());
    }else if(Decl->Is(NodeVarStm)){
        VarStmt *varDecl = static_cast<VarStmt *>(Decl);
        IDN.setDataStr(varDecl->getVar().getStr());
        if(isConst && !varDecl->IsConst()){
            err::err_out(AstNode, "element is not a compile-time constant");
            return false;
        }

        if(varDecl->IsConst()) {
            *Base = varDecl->getVal();
            (*Base)->setTydConst();
            return true;
        }else {
            if(varDecl->HasMut()) {
                AstNode->setMut();
            }


            AstNode->setValue(varDecl->getValueInfo());
        }
    }else if(Decl->Is(NodeFnProto)) {
    }else {
        err::err_out(AstNode->getStmtLoc(), "there is no `",  N ,  "` exist with any declareation");
        return false;
    }

    AstNode->setType(Decl->getTypeInfo());
    dumpSema2("Identifier");
    return true;
}

bool TypeChecker::CheckPathExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();
    String RhsN = Rhs->toString();

    if(!visit(Lhs, &Lhs)) {
        return false;
    }

    Type *LhsTy = Lhs->getTypeInfo();
    if(!LhsTy->isStructTy() && !LhsTy->isEnumTy()) {
        err::err_out(&Expr, "invalid expression expected struct or enum type found - " ,  LhsTy->toStr());
        return false;
    }

    if(LhsTy->isStructTy()) {
        StructType *StTy = static_cast<StructType *>(LhsTy);
        StructStmt *SS =  StTy->getStructStmt();      
        uint32_t Idx = StTy->getIdx(RhsN);
    
        Lexeme &Lxm = static_cast<Identifier *>(Rhs)->getLexeme();
        Lxm.setDataStr(mangle_name(Lxm.getStr(), SS->getName().getStr(), Rhs));
        FunctionProto *MtFn = MT.getImpl(Lxm.getStr());
        if(!MtFn) {
            err::err_out(&Expr, "there is no associative function in struct `",  RhsN , "` field");
            return false;
        }

        if(!MtFn->IsAssociateFunc()) {
            err::err_out(&Expr, "associative function can not be access using struct object");
            return false;
        }
        Rhs->setType(MtFn->getTypeInfo());
        Rhs->setDecl(MtFn);
        *Base = Rhs;
    }else if(LhsTy->isEnumTy()) {
        EnumType *EnumTy = static_cast<EnumType *>(LhsTy);
        String mangle_n = mangle_name(RhsN, Lhs->toString(), Rhs);
        if(!TagF.Has(mangle_n)) {
            err::err_out(&Expr, "there is no `" ,  RhsN ,  "` named in enum field");
            return false;
        }
        *Base = TagF.getTag(mangle_n);
        (*Base)->setType(EnumTy);
        (*Base)->setTydConst();
    }
    dumpSema2(__func__);
    return true;
}

bool TypeChecker::CheckIsExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);

    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();
    String RhsN = Rhs->toString();

    if(!visit(Lhs, &Lhs)){
        return false;
    }
    Type *LhsTy = Lhs->getTypeInfo();

    if(!visit(Rhs, &Rhs)){
        return false;
    }
    Type* RhsTy = Rhs->getTypeInfo();
    
    BoolLiteral *res = nullptr;

    if(LhsTy->IsCloneOf(RhsTy)){
        res = BoolLiteral::Create(mgr, Expr.getStmtLoc(), Lexeme(Expr.getStmtLoc(), "true", TRUE));
    }else{
        res = BoolLiteral::Create(mgr, Expr.getStmtLoc(), Lexeme(Expr.getStmtLoc(), "false", FALSE));
    }
    res->setType(IntType::Create(mgr,  1, false));
    *Base = res;
    return true;
}

static bool CheckCMPOperation(Ast *Lhs, Ast *Rhs, Type *LhsTy, Type *RhsTy, const Tok &Op) {
    if(Op.getTokType() == EQL || Op.getTokType() == NEQL){
        if(LhsTy->isPointerTy()) {
            if(!RhsTy->isPointerTy() && (RhsTy->isIntTy() && !Rhs->Is(NodeNullLit))){
                err::err_out(Lhs,"comparison between pointer and integer");
                return false;
            }
            return true;
        }
        if(RhsTy->isPointerTy()) {
            if(!LhsTy->isPointerTy() && (LhsTy->isIntTy() && !Lhs->Is(NodeNullLit))){
                err::err_out(Lhs,"comparison between pointer and integer");
                return false;
            }
            return true;
        }
    }
    
    if(LhsTy->isEnumTy() && RhsTy->isEnumTy()){
        return true;
    }

    if((!LhsTy->isIntTy() || !RhsTy->isIntTy()) && (!LhsTy->isFltTy() || !RhsTy->isFltTy())){
        err::err_out(Lhs,"comparison between invalid operand");
        err::err_out(Lhs,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
        return false;
    }
    return true;
}


static bool BinaryOperandTypeChecking(Ast *Lhs, const Tok &Op,  Ast *Rhs) {
    Type *&LhsTy = Lhs->getTypeInfo();
    Type *&RhsTy = Rhs->getTypeInfo();

    if(Lhs->IsConst() || Rhs->IsConst()) {
        if((LhsTy->isIntTy() && !as<IntType>(LhsTy)->IsIntWidth(1)) || 
            (RhsTy->isIntTy() && !as<IntType>(RhsTy)->IsIntWidth(1))) {
            goto const_;
        }

        if(LhsTy->isFltTy() && RhsTy->isFltTy()) {
            goto const_;
        }

        if((LhsTy->isPointerTy() && Rhs->Is(NodeNullLit)) || 
            (Lhs->Is(NodeNullLit) && RhsTy->isPointerTy())){
            goto const_;
        }
        goto final;
const_:
        if(Lhs->IsConst()) {
            LhsTy = RhsTy;
        }else if(Rhs->IsConst()){
            RhsTy = LhsTy;
        }
        return true;
    }
final:
    if(!RhsTy->IsCloneOf(LhsTy)) {
        return false;
    }

    return true;
}

bool TypeChecker::CheckBinaryExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();
    String RhsN = Rhs->toString();
    const Tok &Op = Expr.getOp();
    Type *ResTy = nullptr;
    if(!visit(Lhs, &Lhs)){
        return false;
    }

    Type *&LhsTy = Lhs->getTypeInfo();
    
    if(!visit(Rhs, &Rhs, (Op.IsAssignOP() || Op.IsAssnCombinedOP())?LhsTy:nullptr)){
        return false;
    }

    Type *&RhsTy = Rhs->getTypeInfo();
    Ast *&LhsDecl = Lhs->getDecl();
    Ast *&RhsDecl = Rhs->getDecl();


    // VarStmt* varDecl = static_cast<VarStmt*>(Lhs->getDecl());
    if(Op.IsAssignOP() || Op.IsAssnCombinedOP()) {
        // ResTy = LhsTy;

        if(!LhsDecl || (LhsDecl&&!LhsDecl->Is(NodeVarStm))){
            err::err_out(Lhs,"expression is not assignable");
            return false;
        }
        
        if(Lhs->IsConst() || Lhs->IsTydConst()){
            err::err_out(Lhs,"cannot assign to this expression");
            return false;
        }
        
        if(!Lhs->IsMut() && CheckIsInitialized(Lhs)){
            err::err_out(Lhs,"expression is not assignable due to mutability\n\t" 
                        "consider change to `mut`");
            return false;
        }  

        if(!TypeCorel(Rhs->getTypeInfo(), Lhs->getTypeInfo(), Rhs, Rhs->IsConst())) {
            err::err_out(Lhs,"mismatch type, expected type is - ", LhsTy->toStr() ,  " found " ,  RhsTy->toStr());
            return false;
        }

        if(Op.IsAssignOP()){
            setInitialized(Lhs);
        }
        ResTy = VoidType::Create(mgr);
    }else if(Op.IsBinaryOP()) {
        if(!BinaryOperandTypeChecking(Lhs, Op, Rhs)) {
            err::err_out(Lhs, "mismatch type\n\t"
                    "invalid operand to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
            return false;
        }
        if(Lhs->IsConst() && Rhs->IsConst()) 
            Expr.setConst();
        if(Lhs->IsTydConst() && Rhs->IsTydConst())
            Expr.setTydConst();
        if((Lhs->IsTydConst() && Rhs->IsConst()) || (Lhs->IsConst() && Rhs->IsTydConst())) 
            Expr.setTydConst();
    }


    if(Op.IsConditionalOP()) {
        if(Op.getTokType() == CND_AND || Op.getTokType() ==  CND_OR) {
            if(as<IntType>(LhsTy)->getbit() != 1) {
                err::err_out(&Expr,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
                err::err_out(Lhs,"expected type is boolean found - ",  LhsTy->toStr());
                return false;
            }
            if(as<IntType>(RhsTy)->getbit() != 1) {
                err::err_out(&Expr,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
                err::err_out(Lhs,"expected type is boolean found - ",  RhsTy->toStr());
                return false;
            }
        }

        if(!CheckCMPOperation(Lhs, Rhs, LhsTy, RhsTy, Op)) {
            return false;
        }
        ResTy = IntType::Create(mgr, 1, false);
    }else if(Op.LogicalOP() || Op.IsAsnLogicalOP()) {
        if((!LhsTy->isIntTy() && !RhsTy->isIntTy())){
            err::err_out(&Expr,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
            return false;
        }
        if(Op.getTokType() == ASN_LSHIFT || Op.getTokType() == ASN_RSHIFT || 
                        Op.getTokType() == LSHIFT || Op.getTokType() == RSHIFT ) {
            if(as<IntType>(LhsTy)->IsIntWidth(1) || as<IntType>(RhsTy)->IsIntWidth(1)){
                err::err_out(&Expr,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
                return false;
            }
        }

        ResTy = LhsTy;
    }else if(Op.ArithmeticOP() || Op.IsAsnArithmeticOP()) {
        if((Op.getTokType() == MODULO || Op.getTokType() == ASN_MOD) && 
                    (!LhsTy->isIntTy() || !RhsTy->isIntTy())) {
            err::err_out(&Expr,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
            return false;
        }
        if(LhsTy->isIntTy() && RhsTy->isIntTy()){
            if(as<IntType>(LhsTy)->getbit() < 8 || as<IntType>(RhsTy)->getbit() < 8 ) {
                err::err_out(&Expr,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
                return false;
            }
        }
        if((!LhsTy->isIntTy() || !RhsTy->isIntTy()) && (!LhsTy->isFltTy() || !RhsTy->isFltTy())){
            err::err_out(&Expr,"invalid operands to binary expression (`" ,  LhsTy->toStr() ,  "` and `" ,  RhsTy->toStr() ,  "`)");
            return false;
        }
        ResTy = LhsTy;
    }

    Expr.setType(ResTy);
    dumpSema2(__func__);
    return true;
}


bool TypeChecker::CheckStructExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();
    String RhsN = Rhs->toString();
    if(!visit(Lhs, &Lhs)){
        err::err_out(&Expr, "failed to determined type of struct expression");
        return false;
    }

    Type* ty = Lhs->getTypeInfo();
    if(!Lhs->getDecl() || !Lhs->getDecl()->Is(NodeStructStm)){
        err::err_out(&Expr, LhsN ,  "is not struct Declaration");
        return false;
    }

    if(!ty->isStructTy()){
        err::err_out(&Expr, LhsN ,  "expression shoule be struct type");
        return false;
    }

    StructType *StructTy = static_cast<StructType*>(ty);
    Vec<Ast*>&field = static_cast<FieldExpr*>(Rhs)->getArgs();
    bool isConstV = true;
    for(auto &V: field){
        Ast *&Val = static_cast<VarStmt*>(V)->getVal();
        Lexeme &Varn = static_cast<VarStmt*>(V)->getVar();
        Type* Sty = StructTy->getType(Varn.getStr());
        if(!Sty) {
            err::err_out(V, "no type field in struct" ,  LhsN ,  " for " ,  Varn.getStr());
            return false;
        }
        if(!visit(Val, &Val, Sty)){
            return false;
        }
        if(!Val->IsConst() && !Val->IsTydConst() && !isConstF) {
            isConstV = false;
        }
        
        Type *&ValTy = Val->getTypeInfo();
        if(!TypeCorel(ValTy, Sty, Val, Val->IsConst())) {
            err::err_out(Val, "type mismatch\n\t" 
                            "expected argument type is " ,  Sty->toStr() ,  " found - " ,  ValTy->toStr());
            return false;
        }
        V->setType(Val->getTypeInfo());
    }
    if(isConst)
        isConstF = isConstV;
    as<FieldExpr>(Rhs)->setC(isConstV);
    Expr.setType(ty);
    dumpSema2(__func__);
    return true;
}

bool TypeChecker::CheckCallerArg(Ast *Arg, Type *ParamTy) {
    dumpSema(__func__);
    Type *&ArgTy = Arg->getTypeInfo();

    if(!TypeCorel(ArgTy, ParamTy, Arg, Arg->IsConst())) {
        err::err_out(Arg, "type mismatch\n" 
                            "expected argument type is " ,  ParamTy->toStr() ,  " found - " ,  ArgTy->toStr());
        return false;
    }

    dumpSema2(__func__);
    return true;
}


bool TypeChecker::CheckMethodCallExpr(Expression &Expr, Ast **Base) {
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    Ast *&caller = static_cast<Expression *>(Lhs)->getRhs();
    String LhsN = Lhs->toString();
    
    Ast *&self =  static_cast<Expression *>(Lhs)->getLhs();
    Token_type Op =  static_cast<Expression *>(Lhs)->getOp().getTokType();
    if(!visit(self, &self)) {
        return false;
    }
    
    Type *selfTy = self->getTypeInfo();

    if(!selfTy || (!selfTy->isStructTy() && !selfTy->isPointerTy())) {
        err::err_out(Lhs, "(.,->) can be used only with struct type");
        return false;
    }
    Type *StTy = nullptr;
    if(selfTy->isPointerTy()) {
        PointerType *PtrTy = static_cast<PointerType*>(selfTy);
        if(!PtrTy->getTo()->isStructTy()) {
            err::err_out(Lhs, "expected type struct found ", PtrTy->getTo()->toStr());
            return false;
        }

        if(Op != ARROW) {
            err::err_out(Lhs, " `->` should be with type ",  LhsN , 
                        "\n consider `.` to `->`");
            return false;
        }

        StTy = PtrTy->getTo();
    }else if(selfTy->isStructTy()) {
        if(Op != DOT) {
            err::err_out(Lhs, " `.` should be use with this expression ",  LhsN , 
                        "\n consider `.`");
            return false;
        }
        StTy = selfTy;
    }

    // StructType *STy = static_cast<StructType *>(selfTy);
    StructType *STy = as<StructType>(StTy);
    
    Lexeme &Lxm = static_cast<Identifier *>(caller)->getLexeme();
    String FnN = Lxm.getStr();
    Lxm.setDataStr(mangle_name(FnN, STy->getStructStmt()->getName().getStr(), caller));

    FunctionProto *MtFn = MT.getImpl(Lxm.getStr());

    if(!MtFn) {
        err::err_out(&Expr, "there is no `",  FnN , "` associative function in struct field");
        return false;
    }

    FunctionType *FuncType = static_cast<FunctionType *>(MtFn->getTypeInfo()); 
    
    if(MtFn->IsAssociateFunc()) {
        err::err_out(&Expr, "associative function can not be access using struct object");
        return false;
    }

    Vec<Ast *> &field = static_cast<FieldExpr*>(Rhs)->getArgs();
    Vec<Type *> &paramty = FuncType->getParamTypes();

    if(selfTy->isPointerTy())
        field.insert(field.begin(),self);
    else {
        bool mut = static_cast<PointerType *>(paramty[0])->HasMut();
        Ast *Addr = PrefixExpr::Create(mgr, self->getStmtLoc(), AND, self, mut, false);
        if(!visit(Addr, &Addr)) {
            return false;
        }
        field.insert(field.begin(), Addr);
    }

    if(!TypeCorel(field[0]->getTypeInfo(), paramty[0], self)) {
        err::err_out(&Expr, "member function can not be called with this object due to mutability\n\t" 
                            "here's Declare - \n\t" ,  
                            self->getDecl()->toString());
        return false;
    }

    Lhs = static_cast<Expression *>(Lhs)->getRhs();
    Lhs->setDecl(MtFn);
    Lhs->setType(FuncType);

    return true;
}

bool TypeChecker::CheckExternFnCall(Expression &Expr) {
    String CalleName = as<FunctionProto>(Expr.getLhs())->getFuncName().getStr();
    if(CalleName == "printf") {
        if(!CheckPrintExtCall(Expr)) {
            return false;
        }
    }else if(CalleName == "scanf") {
        if(!CheckScanfExtCall(Expr)) {
            return false;
        }
    }
    return true;
}

bool TypeChecker::CheckCallExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();

    if(Lhs->Is(NodeExpr) && as<Expression>(Lhs)->isMemAccessExpr()) {
        if(!CheckMethodCallExpr(Expr, Base)){
            return false;
        }
    }else if(!visit(Lhs, &Lhs)) {
        err::err_out(&Expr, "there's no function declare for " ,  LhsN);
        return false;
    }
    Ast *CallerDecl = Lhs->getDecl();
    bool isExtern = false;
    bool isVariadic = false;
    FunctionProto *FNProto = nullptr;
    if(CallerDecl && CallerDecl->Is(NodeFnProto)) {
        FNProto = static_cast<FunctionProto *>(CallerDecl);
        if(FNProto->isVariadic()){
            isVariadic = true;
        }
        if(FNProto->isExtern()){
            isExtern = true;
        }
    }

    Type *calleTy = Lhs->getTypeInfo();
    if(!calleTy || (calleTy&&!calleTy->isFunctionTy())) {
        err::err_out(&Expr, "expected function found - " ,  calleTy->toStr());
        return false;
    }
    FunctionType *FuncType = static_cast<FunctionType *>(calleTy);

    Vec<Type *> &paramty = FuncType->getParamTypes();
    Vec<Ast *> &field = static_cast<FieldExpr*>(Rhs)->getArgs();


    if(field.size() < paramty.size()) {
        err::err_out(&Expr, "too few argument");
        return false;
    }

    if(!isVariadic && field.size() != paramty.size()) {
            err::err_out(&Expr, "mismatch function arguments");
        return false;
    }

    if(!field.empty()){
        size_t i = 0;
        for(size_t siz = paramty.size(); i < siz; i++) {
            if(!visit(field[i], &field[i], paramty[i])){
                return false;
            }
            Type *&exprTy = field[i]->getTypeInfo();
            if(!CheckCallerArg(field[i], paramty[i])) {
                return false;
            }
        }
        for(size_t siz = field.size(); i < siz; i++) {
            if(!visit(field[i], &field[i])){
                return false;
            }
        }
    }

    if(isExtern) {
        if(!CheckExternFnCall(Expr)) {
            return false;
        }
    }

    Expr.setDecl(Lhs->getDecl());
    Expr.setType(FuncType->getRetType());
    dumpSema2(__func__);
    return true;
}


bool IsValidCastingOprand(Ast *Opr) {
    if(Opr->Is(NodeField) || (Opr->Is(NodeExpr) && as<Expression>(Opr)->isStructExpr())
                        || (Opr->Is(NodeIdent) && !Opr->getDecl()->Is(NodeVarStm))) {
        err::err_out(Opr, "invalid operand to cast");
        return false;
    }
    if((Opr->Is(NodeIdent) && (Opr->getDecl() && !Opr->getDecl()->Is(NodeVarStm)) ) ) {
        err::err_out(Opr, "invalid operand to cast");
        return false;
    }
    if(Opr->Is(NodeBoolLit)) {
        err::err_out(Opr, "invalid operand to cast");
        return false;
    }
    return true;
}

bool TypeChecker::CheckCastExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();
    String RhsN = Rhs->toString();

    if(!IsValidCastingOprand(Lhs)) {
        return false;
    }

    if(!visit(Lhs, &Lhs)){
        return false;
    }

    Type* LhsTy = Lhs->getTypeInfo();

    if(!visit(Rhs, &Rhs)){
        err::err_out(&Expr, "invalid type to cast");
        return false;
    }
    Type *RhsTy = Rhs->getTypeInfo();


    if(isConst && (!RhsTy->isIntTy() && !RhsTy->isFltTy())) {
        err::err_out(&Expr, LhsTy->toStr() ,  " cannot be cast to " ,  RhsTy->toStr() ,  " during const eval");
        return false;
    }

    if(RhsTy->isIntTy() && as<IntType>(RhsTy)->IsIntWidth(1)) {
        err::err_out(&Expr, "cannot cast as `bool`\n\t"
                            "compare with zero instead: `some_expression != 0`");
        return false;
    }

    if(!LhsTy->IsCasteble(RhsTy)) {
        err::err_out(&Expr, "can not be cast " ,  LhsTy->toStr() ,  " to " ,  RhsTy->toStr());
        return false;
    }

    Expr.setDecl(Lhs->getDecl());
    if(Lhs->IsMut())
        Expr.setMut();
    if(Lhs->IsConst() || Lhs->IsTydConst())
        Expr.setTydConst();
    Expr.setType(RhsTy);
    dumpSema2(__func__);
    return true;
}

bool TypeChecker::CheckIndexOutOfBound(Ast *IdxVal, size_t DimSize) {
    if(!valpass.visit(IdxVal, nullptr)){
        return false;
    }
    VALUE* valTy = IdxVal->getValueInfo();
    if(valTy->getValTy() != VALUE::VInt){
        err::err_out(IdxVal, "index value should be usigned integer");
        return false;
    }

    int idxval = static_cast<IntVal *>(valTy)->getVal();        
    if(idxval < 0 || idxval >= DimSize){
        err::err_out(IdxVal, "index out of bounds: the length is " ,  std::to_string(DimSize) ,  " but the index is " ,  std::to_string(idxval));
        return false;
    }
    return true;
}


bool TypeChecker::CheckPointerIndex(Expression &Expr) {
    dumpSema(__func__);
    Ast *Opr = Expr.getLhs();


    Ast *IdxExpr = Expr.getRhs();
    PointerType *PtrTy = static_cast<PointerType *>(Opr->getTypeInfo());

    if(!visit(IdxExpr, &IdxExpr)){
        return false;
    }
    Type *expTy = IdxExpr->getTypeInfo();
    if(!expTy->isIntTy() ){
        err::err_out(IdxExpr, "[] array can only be indexed by `integer`");
        return false;
    }

    if(as<IntType>(expTy)->IsIntWidth(1)) { 
        err::err_out(IdxExpr, "[] array can only be indexed by `integer`");
        return false;
    }

    Expr.setType(PtrTy->getTo());

    Expr.setDecl(Opr->getDecl());

    if(PtrTy->HasMut())
        Expr.setMut();
    dumpSema2(__func__);
    return true;
}

bool TypeChecker::CheckIndexExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();
    String RhsN = Rhs->toString();
    Ast *IdxExpr = Expr.getRhs();
    if(!visit(Lhs, &Lhs)){ 
        err::err_out(&Expr, "failed to determined type of index expression");
        return false;
    }
    Type *Ty = Lhs->getTypeInfo();
    if(Ty->isPointerTy()) {
        if(!CheckPointerIndex(Expr)) {
            return false;
        }

        return true;
    }
    if(!Ty->isArrayTy()) {
        err::err_out(&Expr, "expected type is []_ found" ,  Ty->toStr());
        return false;
    }
    
    ArrayType *ArrTy = static_cast<ArrayType*>(Ty);

    size_t arrSize = ArrTy->getSize();

    if(!visit(IdxExpr, &IdxExpr)){
        err::err_out(IdxExpr, "failed to determined type for array index");
        return false;
    }
    
    Type *expTy = IdxExpr->getTypeInfo();
    if(!expTy->isIntTy()) { 
        err::err_out(IdxExpr, "[] array can only be indexed by `integer`");
        return false;
    }
    if(as<IntType>(expTy)->IsIntWidth(1)) { 
        err::err_out(IdxExpr, "[] array can only be indexed by `integer`");
        return false;
    }

    if(IdxExpr->IsConst() || IdxExpr->IsTydConst() ) {
        if(!CheckIndexOutOfBound(IdxExpr, arrSize)) {
            return false;
        }
        if(static_cast<IntType *>(expTy)->isSignInt()) {
            IdxExpr->setType(IntType::Create(mgr, 64, false));
        }
    }

    Expr.setType(ArrTy->getArrType());
    Expr.setDecl(Lhs->getDecl());
    if(Lhs->IsMut())
        Expr.setMut();
    dumpSema2(__func__);
    return true;
}


bool TypeChecker::CheckMemExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String LhsN = Lhs->toString();
    String RhsN = Rhs->toString();
    Type *LhsTy = nullptr;
    Type *RhsTy = nullptr;
    StructType *stTy = nullptr;
    bool Mut = false;
    if(!visit(Lhs, &Lhs)){
        return false;
    }

    Ast *&Decl = Lhs->getDecl();
    if(!Decl || (Decl && Decl->Is(NodeStructStm))) {
        err::err_out(Lhs, "expected struct value, found struct");
        return false;
    }
    if(!Decl->Is(NodeVarStm) && !Decl->Is(NodeFNStm) && !Decl->Is(NodeFnProto)){
        err::err_out(Lhs, "expected struct value, found struct");
        return false;
    }
    
    LhsTy = Lhs->getTypeInfo();
    if(!LhsTy || (!LhsTy->isStructTy() && !LhsTy->isPointerTy())) {
        err::err_out(Lhs, "(.,->) can be used with struct");
        return false;
    }


    if(LhsTy->isPointerTy()) {
        PointerType *PtrTy = static_cast<PointerType*>(LhsTy);
        if(!PtrTy->getTo()->isStructTy()) {
            err::err_out(Lhs, "expected type struct found ", PtrTy->getTo()->toStr());
            return false;
        }

        if(Expr.getOp().getTokType() != ARROW) {
            err::err_out(Lhs, " `->` should be with type ",  LhsN , 
                        "\n consider `.` to `->`");
            return false;
        }

        LhsTy = PtrTy->getTo();
        if(PtrTy->HasMut())
            Mut = true;
    }else if(LhsTy->isStructTy()) {
        if(Expr.getOp().getTokType() != DOT) {
            err::err_out(Lhs, " `.` should be with type ",  LhsN , 
                        "\n consider `.`");
            return false;
        }
        if(Lhs->IsMut())
            Mut = true;
    }

    stTy = static_cast<StructType*>(LhsTy);
    RhsTy = stTy->getType(RhsN);
    if(RhsTy == nullptr) {
        err::err_out(Rhs, "no field `" ,  RhsN ,  "` on type " ,  LhsN);
        return false;
    }

    StructStmt *SS =  stTy->getStructStmt();     
    uint32_t Idx = stTy->getIdx(RhsN);
    if(Idx < SS->getfield().size()) {
        Expr.setDecl(SS->getfield()[Idx]);
    }


    if(Mut)
        Expr.setMut();
    Rhs->setType(RhsTy);
    Expr.setType(RhsTy);
    dumpSema2(__func__);
    return true;
}


bool TypeChecker::visit(FloatLiteral  *AstNode, Ast **Base) {
    dumpSema("FloatLiteral");
    Type *ty = nullptr;
    if(AstNode->getLexeme().getDataInt() > __FLT_MAX__ || AstNode->getLexeme().getDataInt() < __FLT_MIN__){
        ty = FloatType::Create(mgr, 64);
    }else {
        ty = FloatType::Create(mgr, 32);
    }

    AstNode->setType(ty);

    if(isConst && !valpass.visit(AstNode, Base)){
        return false;
    }
    AstNode->setConst();
    dumpSema2("FloatLiteral");
    return true;
}

bool TypeChecker::visit(BoolLiteral  *AstNode, Ast **Base) {
    dumpSema("BoolLiteral");
    AstNode->setType(IntType::Create(mgr, 1, false));

    if(isConst && !valpass.visit(AstNode, Base)) {
        err::err_out(AstNode, "failed to determined value at compile time");
        return false;
    }
    AstNode->setConst();
    dumpSema2("BoolLiteral");
    return true;
}

bool TypeChecker::visit(NumericLiteral  *AstNode, Ast **Base) {
    dumpSema("NumericLiteral");
    if(AstNode->getLexeme().getDataInt() > INT32_MAX || AstNode->getLexeme().getDataInt() < INT32_MIN){
        AstNode->setType(IntType::Create(mgr, 64, true));
    }else {
        AstNode->setType(IntType::Create(mgr, 32, true));
    }

    if(isConst && !valpass.visit(AstNode, Base)) {
        err::err_out(AstNode, "failed to determined value at compile time");
        return false;
    }
    AstNode->setConst();
    dumpSema2("NumericLiteral");
    return true;
}

bool TypeChecker::visit(NullLiteral  *AstNode, Ast **Base) {
    dumpSema("NullLiteral");

    AstNode->setType(PointerType::Create(mgr, true, VoidType::Create(mgr)));
    if(isConst && !valpass.visit(AstNode, Base)) {
        err::err_out(AstNode, "failed to determined value at compile time");
        return false;
    }

    AstNode->setConst();
    dumpSema2("NullLiteral");
    return true;
}


bool TypeChecker::visit(StringLiteral  *AstNode, Ast **Base) {
    dumpSema("StringLiteral");
    Type *lity = nullptr;
    if(AstNode->ischar()){
        lity = IntType::Create(mgr, 8, false);
        AstNode->setConst();
    }else{
        lity = ArrayType::Create(mgr, IntType::Create(mgr, 8,false), AstNode->getLexeme().getStr().size() + 1);
        if(isConst)
            isConstF = true;
    }
    AstNode->setType(lity);

    if(isConst && !valpass.visit(AstNode, Base)) {
        err::err_out(AstNode, "failed to determined value at compile time");
        return false;
    }
    dumpSema2("StringLiteral");
    return true;
}


bool TypeChecker::visit(FieldExpr *AstNode, Ast **Base) {
    dumpSema("FieldExpr");
    Vec<Ast *> &field = AstNode->getArgs();
    if(field.empty()){
        err::err_out(AstNode, "empty array field");
        return false;
    }
    if(!visit(field[0], &field[0])){
        return false;
    }

    Type *PrevType = field[0]->getTypeInfo();

    bool isConstV = true; 
    size_t size = field.size();
    for(auto &Val: field){
        if(!visit(Val, &Val)){
            return false;
        }

        if(!Val->IsConst() && !Val->IsTydConst() && !isConstF) {
            isConstV = false;
        }
        
        if(!TypeCorel(Val->getTypeInfo(), PrevType, Val, Val->IsConst())) {
            err::err_out(Val, "mismatch type\n\t"
                            "expected `" ,  PrevType->toStr() ,  "`, found `" ,  Val->getTypeInfo()->toStr());
            return false;
        }
    }
    if(isConst) {
        isConstF = isConstV;
    }
    AstNode->setC(isConstV);
    AstNode->setType(ArrayType::Create(mgr, PrevType, size));
    
    dumpSema2("FieldExpr");
    return true;
}


bool TypeChecker::visit(PrefixExpr *AstNode, Ast **Base) {
    dumpSema("PrefixExpr");
    Ast *&BaseVar = AstNode->getBase();
    if(!visit(BaseVar, &BaseVar)){
        err::err_out(BaseVar, "invalid expression");
        return false;
    }
    const Tok &Op = AstNode->getOp();
    switch (Op.getTokType())
    {
    case STAR:
    {
        if(AstNode->IsType()) {
            Type *baseTy = BaseVar->getTypeInfo();
            
            if(!baseTy->UnaryOpMatch(AstNode->getOp())) {
                err::err_out(BaseVar, "mismatch operator\n\t"
                            " *() can not be used with type - " ,  baseTy->toStr());
                return false;
            }
            AstNode->setType(PointerType::Create(mgr, AstNode->HasMut(), baseTy));
        }else {
            
            Type *Ty = BaseVar->getTypeInfo();
            Ast *Decl = BaseVar->getDecl();

            /// it can be function call or variable
            if(!Decl || (!Decl->Is(NodeVarStm) && !Decl->Is(NodeFNStm) && !Decl->Is(NodeFnProto))) {
                err::err_out(BaseVar, "exprssion can not be dereferenced");
                return false;
            }
            if(!isValue(BaseVar, false)) {
                err::err_out(BaseVar, "exprssion can not be dereferenced");
                return false;
            }

            if(!Ty->isPointerTy() && !Ty->isRefTy()){
                err::err_out(BaseVar, "mismatch operator\n\t",
                          Ty->toStr(), " type can not be dereferenced");
                return false;
            }

            PointerType* PtrTy = nullptr;
            if(Ty->isRefTy()) {
                RefType *RefTy = static_cast<RefType*>(Ty);
                AstNode->setType(RefTy->getTo());
                if(RefTy->IsMutRef())
                    AstNode->setMut();
                break;
            }else
                PtrTy = static_cast<PointerType*>(Ty);


            if(!PtrTy){
                err::err_out(BaseVar, "unable to dereference type " ,  PtrTy->toStr());
                return false;
            }

            if(isConst) {
                err::err_out(BaseVar, "initializer element is not a compile-time constant");
                return false;
            }

            if(PtrTy->HasMut())
                AstNode->setMut();
            AstNode->setType(PtrTy->getTo());
        }
    }
        break;
    case AND: 
    case MINUS: 
    case CND_NOT: 
    case NOT:
    {
        Type *baseTy = BaseVar->getTypeInfo();

        if(!baseTy->UnaryOpMatch(AstNode->getOp())){
            err::err_out(BaseVar, "mismatch unary operator\n\t\t" 
                                "can not apply `" ,  Op.toStr() ,  "` with type - " ,  baseTy->toStr());
            return false;
        }

        if(Op.getTokType() == AND) {
            if(!isAddressableValue(BaseVar)) {
                err::err_out(BaseVar, "exprssion is not addressable, &() can not be used with " ,  BaseVar->toString());
                return false;
            }
            if(BaseVar->IsConst() || BaseVar->IsTydConst()) {
                err::err_out(BaseVar, "cannot take address of const");
                return false;
            }
            bool mut = false;
            if(AstNode->HasMut()) {
                 if(!BaseVar->IsMut()) {
                    err::err_out(BaseVar, "defer in mutability\n");
                    return false;
                 }
                 mut = true;
            }

            AstNode->setType(RefType::Create(mgr, baseTy, mut));
            break;
        }else if(Op.getTokType() == CND_NOT) {
            AstNode->setType(IntType::Create(mgr, 1, false));
        }else
            AstNode->setType(baseTy);

        if(BaseVar->IsConst())
            AstNode->setConst();
        if(BaseVar->IsMut())
            AstNode->setMut();
    }
    
    default:
        break;
    }
    AstNode->setDecl(BaseVar->getDecl());
    dumpSema2("PrefixExpr");
    return true;
}

bool TypeChecker::visit(GroupedExpr  *AstNode, Ast **Base) {
    dumpSema("GroupedExpr");
    Ast *&Expr = AstNode->getExpression();
    if(!visit(Expr, &Expr)){
        err::err_out(AstNode, "failed to determined type of expression");
        return false;
    }
    AstNode->setType(Expr->getTypeInfo());
    AstNode->setDecl(Expr->getDecl());

    if(Expr->IsMut())
        AstNode->setMut();
    if(Expr->IsConst())
        AstNode->setConst();
    if(Expr->IsTydConst())
        AstNode->setTydConst();
    dumpSema2("GroupedExpr");
    return true;
}


size_t SizeOf(Type *Ty) {
	static constexpr size_t szvoidp = sizeof(void *);

	if(Ty->isPointerTy()) {
		return sizeof(void *);
	}
	if(Ty->isArrayTy()) {
        size_t sz= as<ArrayType>(Ty)->getSize();
		return SizeOf(as<ArrayType>(Ty)->getArrType())*sz;
	}
	if(Ty->isEnumTy()) {
		return SizeOf(as<EnumType>(Ty)->getIntTy());
	}
	if(Ty->isIntTy()) {
		if(as<IntType>(Ty)->getbit() < 8) return 1;
		return as<IntType>(Ty)->getbit() / 8;
	}
	if(Ty->isFltTy()) {
		return as<FloatType>(Ty)->getbit() / 8;
	}
	if(Ty->isStructTy()) {
		StructType *st   = as<StructType>(Ty);
		size_t sz      = 0;
		size_t biggest = 0;
		for(auto &t : st->getTypeList()) {

			size_t newsz = SizeOf(t);
			// biggest cannot be greater than sizeof(void *)
			if(newsz > biggest && biggest < szvoidp) {
				biggest = newsz > szvoidp ? szvoidp : newsz;
			}
			sz += newsz;
		}
		while(sz % biggest != 0) {
			++sz;
		}
        
		return sz;
	}
	return 0;
}

bool TypeChecker::CheckExtCallExpr(Expression &Expr, Ast **Base) {
    dumpSema(__func__);
    Ast *&Lhs = Expr.getLhs();
    Ast *&Rhs = Expr.getRhs();
    String call = Lhs->toString();
    String RhsN = Rhs->toString();

    Vec<Ast *> &field = static_cast<FieldExpr*>(Rhs)->getArgs();

    if(!field.empty()){
        // const siz i32 = @szof(i32); i32 is not const in case;
        bool HadConst = isConst;
        isConst = false;
        for(size_t i = 0, siz = field.size(); i < siz; i++ ) {
            if(!visit(field[i], &field[i])){
                err::err_out(field[i], "failed to determine type of argument");
                return false;
            }
        }
        isConst = HadConst;
    }
    if(call == "print") {
        if(!CheckPrintExtCall(Expr)) {
            return false;
        }
    }else if(call == "szof") {
        if(field.size() != 1) {
            err::err_out(Lhs, "args mismatch");
            return false;
        }

        size_t sz = SizeOf(field[0]->getTypeInfo());
        *Base = NumericLiteral::Create(mgr, Expr.getStmtLoc(), Lexeme(Expr.getStmtLoc(), (int64_t)sz, INT));
        (*Base)->setType(IntType::Create(mgr, 64, false));
        (*Base)->setConst();
    }else if(call == "asVoidPtr") {
        if(field.size() != 1) {
            err::err_out(Lhs, "too many args");
            return false;
        }
        Type *Ty = field[0]->getTypeInfo();
        if(!Ty->isPointerTy() && !Ty->isRefTy() && !Ty->isArrayTy()) {
            err::err_out(Lhs, "arg should pointer type");
            return false;
        }
        *Base = field[0];
        (*Base)->setType(PointerType::Create(mgr, true, VoidType::Create(mgr)));
    }else if(call == "scan") {
        if(!CheckScanfExtCall(Expr)) {
            return false;
        }
    }else{
        err::err_out(Lhs, "there no `" ,  call ,  "` extern function call");
        return false;
    }
    dumpSema2(__func__);
    return true;
}

bool TypeChecker::visit(Expression *AstNode, Ast **Base) {
    dumpSema("Expression");
    switch (AstNode->getExprID())
    {
    case Expression::KMemExpr:
        return CheckMemExpr(*AstNode, Base);
        break;
    case Expression::KBinaryExpr:
        return CheckBinaryExpr(*AstNode, Base);
        break;
    case Expression::KAsExpr:
        return CheckCastExpr(*AstNode, Base);
    break;
    case Expression::KIsExpr:
        return CheckIsExpr(*AstNode, Base);
    break;
    case Expression::KPathExpr:
        return CheckPathExpr(*AstNode, Base);
    break;
    case Expression::KIndexExpr:
        return CheckIndexExpr(*AstNode, Base);
    break;
    case Expression::KStructExpr:
        return CheckStructExpr(*AstNode, Base);
    break;
    case Expression::KCallExpr:
        return CheckCallExpr(*AstNode, Base);
    break;
    case Expression::KExtCallExpr:
        return CheckExtCallExpr(*AstNode, Base);
    break;
    default:
        break;
    }
    dumpSema2("Expression");
    return false;
}



} 