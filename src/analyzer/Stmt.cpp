#include"../../include/analyzer/Sema.hpp"
#include"../../include/analyzer/Value.hpp"
#include"../../include/Error.hpp"
#include"../../include/Module.hpp"
// #include"analyzer/TypeChecker.hpp"

namespace ast {

bool TypeChecker::visit(BranchStmt *AstNode, Ast** SrcPtr) {
    dumpSema("Branch");
    if(!BranchAllow) {
        err::err_out(
		AstNode, AstNode->getLexeme().getStr() , "used in only loop stmt");
        return false;
    }
    dumpSema2("Branch");
    return true;
}


bool TypeChecker::visit(NewStmt *AstNode, Ast** SrcPtr) {
    dumpSema("NewStmt");
    Ast *&Size = AstNode->getSize();
    Ast *&StmtTy = AstNode->getTy();
    if(!visit(StmtTy, &StmtTy)) {
        return false;
    }
    Type *Ty = StmtTy->getTypeInfo();
    if(!Ty){
        err::err_out(StmtTy, "failed to determined type of - ",StmtTy->toString());
        return false;
    }

    if(!visit(Size, &Size)) {
        return false;
    }

    Type *STy = Size->getTypeInfo();
    if(!STy){
        err::err_out(StmtTy, "failed to determined type of - ",StmtTy->toString());
        return false;
    }
    if(!STy->isIntTy() || (!Size->IsConst() && static_cast<IntType *>(STy)->isSignInt())){
        err::err_out(StmtTy, "size must be unsigned integer");
        return false;
    }
    if(Ty->isPointerTy()) {
        AstNode->setType(Ty);
    }else
        AstNode->setType(PointerType::Create(mgr, true, Ty));
    dumpSema2("NewStmt");
    return true;
}

bool TypeChecker::visit(DelStmt *AstNode, Ast** SrcPtr) {
    dumpSema("DelStmt");
    Ast *&VPtr = AstNode->getPtr();

    if(!visit(VPtr, &VPtr)) {
        return false;
    }

    if(!VPtr->getDecl()->Is(NodeVarStm)) {
        err::err_out(VPtr, VPtr->toString() , " must be valid pointer");
        return false;
    }

    Type *VPtrTy = VPtr->getTypeInfo();
    if(!VPtrTy) {
        err::err_out(VPtr, "failed to determined type of - ", VPtr->toString());
        return false;
    }

    if(!VPtrTy->isPointerTy()) {
        err::err_out(VPtr, VPtr->toString() , " must be pointer type");
        return false;
    }
    AstNode->setType(VoidType::Create(mgr));
    dumpSema2("DelStmt");
    return true;
}

static bool CheckStructRescursion(uintptr_t Id, StructType *STy) {
    for(auto &Ty: STy->getTypeList()) {
        if(Id == Ty->getuId()) {
            return false;
        }
        if(Ty->isStructTy() && !CheckStructRescursion(Id, static_cast<StructType *>(Ty))) {
            return false;
        }
    }
    return true;
}

bool TypeChecker::visit(StructStmt *AstNode, Ast **SrcPtr) {
    dumpSema("StructStmt");
    Lexeme &IdenL = AstNode->getName();
    std::string STN = IdenL.getStr();
    std::string MangleN = mangle_name(STN, AstNode->getStmtLoc()->getMod()->getModId(), AstNode);
    IdenL.setDataStr(MangleN);

    StructType* s = StructType::Create(mgr, {});
    s->setStructStmt(AstNode);
    AstNode->setType(s);
    Vec<VarStmt *>&vars = AstNode->getfield();
    for(size_t i = 0, siz = vars.size(); i < siz; i++) {
        std::string EleName = vars[i]->getVar().getStr();
        if(s->contains(EleName)){
            err::err_out(vars[i], "redefination of field name ", EleName);
            return false;
        }
        Ast *&VarTy = vars[i]->getType();
        if(!visit(VarTy, &VarTy)){
            return false;
        }
        Type *Ty = VarTy->getTypeInfo();
        s->InsertField(EleName, VarTy->getTypeInfo());
    }

    if(!CheckStructRescursion(s->getuId(), s)) {
        err::err_out(AstNode, "recursive type `", STN , "` has infinite size");
        return false;
    }

    if(AstNode->getImpl()&& !visit(AstNode->getImpl(), nullptr)) {
        return false;
    }
    dumpSema2("StructStmt");
    return true;
}


bool TypeChecker::visit(EnumExpr *AstNode, Ast **SrcPtr) {
    dumpSema("EnumExpr");
    Lexeme &IdenN = AstNode->getName();
    std::string MangleN = mangle_name(IdenN.getStr(), AstNode->getStmtLoc()->getMod()->getModId(), AstNode);
    IdenN.setDataStr(MangleN);

    int64_t Eval = 0;   
    Ast *&Ty = AstNode->getEVals()[0]->getType();
    
    if(!visit(Ty, &Ty)) {
        return false;
    }

    if(!Ty->getTypeInfo()->isIntTy()) {
        err::err_out(AstNode, "type must be int with enum");
        return false;
    }

    IntType* ETy = static_cast<IntType *>(Ty->getTypeInfo());

    Vec<VarStmt *>&Vals = AstNode->getEVals();

    for(auto &V :Vals) {
        std::string EName = V->getVar().getStr();
        V->getVar().setDataStr(mangle_name(EName, MangleN, V));
        Ast *&TagVal = V->getVal();
        if(TagVal) {
            isConst = true;
            if(!visit(TagVal, &TagVal, ETy)) {
                return false;
            }
            isConst = false;

            if(!TagVal->IsConst()) {
                err::err_out(TagVal, "enum value must be const integer or integer literal or const expression");
                return false;
            }

            Type *VTy = TagVal->getTypeInfo();
            if(!VTy|| (VTy && !VTy->isIntTy())) {
                err::err_out(TagVal, "type must integer type\n\t\t"
                                    "expression is not an integer constant expression");
                return false;
            }

            if(as<IntType>(VTy)->IsIntWidth(1)) {
                err::err_out(TagVal, "expression is not an integer constant expression");
                return false;
            }

            if(TagVal->getStmtTy() != NodeCategory::NodeNumLit) {
                TagVal = getConstVal(TagVal, &TagVal);
                if(!TagVal) {
                    err::err_out(TagVal, "invalid const value, can't find or calculate at compile time");
                    return false;
                }
                TagVal->setType(VTy);
            }

            if(TagVal->getStmtTy() != NodeCategory::NodeNumLit) {
                err::err_out(TagVal, "expression is not an integer constant expression");
                return false;
            }

            Eval = static_cast<NumericLiteral *>(TagVal)->getLexeme().getDataInt();
        }else {
            TagVal = NumericLiteral::Create(mgr, AstNode->getStmtLoc(),  Lexeme(AstNode->getStmtLoc(), (int64_t)Eval, Token_type::INT));
            Eval++;
        }

        TagVal->setType(ETy);
        TagF.insert(V->getVar().getStr(), TagVal);
    }

    AstNode->setType(EnumType::Create(mgr, ETy));

    dumpSema2("EnumExpr");
    return true;
}


bool TypeChecker::visit(ReturnStmt *AstNode, Ast **SrcPtr) {
    dumpSema("ReturnStmt");
    Type *RetType = AstNode->getFnBlk()->getTypeInfo();
    Ast *&RetVal = AstNode->getRetValue();

    if(!RetType->isVoidTy() && !RetVal) {
        err::err_out(AstNode, "only non-void function can return");
        return false;
    }

    if(!RetVal) {
        return true;
    }

    if(!visit(RetVal, &RetVal, RetType)){
        err::err_out(AstNode, "falied to determined return type");
        return false;
    }

    Type *&Ty = RetVal->getTypeInfo();

    if(!TypeCorel(Ty, RetType, RetVal, RetVal->IsConst())) {
        err::err_out(RetVal, "mismatch type\n\t" 
                            "expected type ", RetType->toStr() , " found ", Ty->toStr());
        return false;
    }

    if(RetVal->IsConst()) {
        AstNode->setConst();
    }
    AstNode->setType(RetType);
    dumpSema2("ReturnStmt");
    return true;
}


bool TypeChecker::visit(FunctionDef *FnStmt, Ast **SrcPtr) {
    dumpSema("FunctionDef");
    FunctionProto *FnProto = FnStmt->getFnProto();
    Lexeme &FuncN = FnProto->getFuncName();
    std::string name = FuncN.getStr();
    Type *&Ty = FnProto->getTypeInfo();
    if(!Ty)
        if(!visit(FnProto, asAst(&FnProto))) {
            return false;
        }
    FunctionType *FnTy = as<FunctionType>(Ty);

    BlockStmt *Blk = FnStmt->getFuncBlock();
    Type *RetTy = FnTy->getRetType();
    Blk->setType(RetTy);

    if(!FnProto->IsMemberFunc() && !FnProto->IsAssociateFunc() && !(FnProto->getStmtLoc()->getMod() == RootMod && name == "main")) {
        std::string MangleN = mangle_name(name, 
                            FnStmt->getStmtLoc()->getMod()->getModId(), 
                            FnStmt);
        FuncN.setDataStr(MangleN);
    }

    FnStmt->setType(FnTy);
    FnProto->setType(FnTy);
    if(Blk->empty() && !RetTy->isVoidTy()) {
        err::err_out(Blk, "expected return type `", RetTy->toStr() , "` found ()" );
        return false;
    }
    if(!visit(Blk, asAst(&Blk))){
        err::err_out(Blk, "failed due to previous error");
        return false;
    }

    dumpSema2("FunctionDef");
    return true;
}


Ast *TypeChecker::getConstVal(Ast *Val, Ast **SrcPtr) {
    if(!valpass.visit(Val, SrcPtr)) {
        err::err_out(Val, "failed to determined value at compile time");
        return nullptr;
    }
    VALUE *VVal = Val->getValueInfo();
    switch (VVal->getValTy())
    {
    case VALUE::VBool:
    {
        IntVal *IVal = static_cast<IntVal *>(VVal); 
        Val = BoolLiteral::Create(mgr, Val->getStmtLoc(), Lexeme(Val->getStmtLoc(), IVal->getVal(), IVal->getVal()?TRUE:FALSE));
    }
    break;
    case VALUE::VInt:
    {
        IntVal *IVal = static_cast<IntVal *>(VVal); 
        Val = NumericLiteral::Create(mgr, Val->getStmtLoc(), Lexeme(Val->getStmtLoc(), IVal->getVal(), INT));
    }
    break;
    case VALUE::VFlt:
    {
        FltVal *FVal = static_cast<FltVal *>(VVal); 
        Val = FloatLiteral::Create(mgr, Val->getStmtLoc(), Lexeme(Val->getStmtLoc(), FVal->getVal(), FLOAT));
    }
    break;
    default:
        break;
    }
    Val->setValue(VVal);
    return Val;
}

bool TypeChecker::visit(VarStmt *AstNode, Ast **SrcPtr) {
    dumpSema("VarStmt");
    Ast *&varTy = AstNode->getType();
    Ast *&varVal = AstNode->getVal();
    Lexeme &VarN = AstNode->getVar();
    std::string MID = AstNode->getStmtLoc()->getMod()->getModId();
    std::string MangleN = mangle_name(VarN.getStr(), MID, AstNode);
    VarN.setDataStr(MangleN);

    if(varTy && !visit(varTy, &varTy))
        return false;

    bool IsGlobVar = false;
    if(AstNode->IsConst() || AstNode->IsGlobVar()) {
        IsGlobVar = true;
        isConst = true;
    }

    if(isConst && !IsGlobVar && !varTy->Is(NodePreDefTy)) {
        err::err_out(AstNode, "invalid constant type\n expected preemetive type with const found ", varTy->toString());
        return false;
    }

    Type* type = varTy?varTy->getTypeInfo():nullptr;

    if(varVal&&!visit(varVal, &varVal, type)){
        return false;
    }

    Type *valType = varVal?varVal->getTypeInfo():nullptr;
    if(!varTy) {
        if(varVal->Is(NodeNullLit)) {
            err::err_out(varVal, "type is must be declare to assign null");
            return false;
        }

        if(valType->isVoidTy()) {
            err::err_out(varVal, "void can not be used for initalization");
            return false;
        }
    }

    if(isConst){
        if(varTy && !IsGlobVar && type->isPointerTy()) {
            err::err_out(AstNode, "invalid constant type ", varTy->toString());
            return false;
        }

        if(varVal && !IsGlobVar && varVal->Is(NodeNullLit)) {
            err::err_out(AstNode, "const can not be assign with null");
            return false;
        }

        if((!varVal->IsConst() && !varVal->IsTydConst()) && (IsGlobVar&&!isConstF)) {
            err::err_out(AstNode, "initializer element is not a compile-time constant");
            return false;
        }   
    }

    if(!varTy && varVal) {
        if(valType->isRefTy()) {
            type = static_cast<RefType *>(valType)->getPtr(mgr);
        }else
            type = valType; 
    }
    

    if(varTy&&varVal){
        std::cout<<type->type()<<" "<<std::endl;
        if(!TypeCorel(varVal->getTypeInfo(), type, varVal, varVal->IsConst())) {
            err::err_out(AstNode, "mismatch type \n\t\t"
                                "expected type is ", type->toStr() , " found ", valType->toStr());
            return false;
        }
    }

    if(varVal) {
        AstNode->setInitialized();
    }

    if(AstNode->HasMut()) {
        AstNode->setMut();
    }

    if(isConst&&!IsGlobVar) {
        varVal = getConstVal(varVal, &varVal);
        varVal->setTydConst();
        varVal->setType(type);
    }
    isConst = false;
    isConstF = false;
    AstNode->setType(type);
    dumpSema2("VarStmt");
    return true;
}

bool TypeChecker::visit(FunctionProto *FnProto, Ast **SrcPtr) {
    dumpSema("FunctionProto");
    Lexeme &FuncN = FnProto->getFuncName();
    std::string MID = FnProto->getStmtLoc()->getMod()->getModId();
    std::string name = FuncN.getStr();
    
    Ast *&Ret = FnProto->getResultType();
    Type *RetTy = nullptr;
    if(Ret) {
        if(!visit(Ret, &Ret)) {
            return false;
        }
        
        RetTy = Ret->getTypeInfo();
    }else
        RetTy = VoidType::Create(mgr);

    if(name == "main") {
        if(!RetTy->isIntTy()) {
            err::err_out(FnProto, "'main' must return 'int'" );
            return false;
        }
    }

    Vec<Type*>ElementType;
    if(!FnProto->getParameter().empty()){
        Vec<VarStmt*>&Param = FnProto->getParameter();
        for(size_t i = 0, size = Param.size(); i < size; i++) {
            Ast *&Ty = Param[i]->getType();
            if(!visit(Ty, &Ty)){
                return false;
            }
            
            Param[i]->setInitialized();
            Type *&pty = Ty->getTypeInfo();
            Param[i]->setType(pty);
            Lexeme &ParamVar = Param[i]->getVar();
            ParamVar.setDataStr(mangle_name(ParamVar.getStr(), MID, Param[i]));
            ElementType.push_back(Ty->getTypeInfo());
        }
    }
    FnProto->setType(FunctionType::Create(mgr, ElementType, RetTy));

    if(!FnProto->IsMemberFunc() && !FnProto->IsAssociateFunc() && !(FnProto->getStmtLoc()->getMod() == RootMod && name == "main")) {
        std::string MangleN = mangle_name(name, 
                                            MID, 
                                        FnProto);
        FuncN.setDataStr(MangleN);
    }
    dumpSema2("FunctionProto");
    return true;
}

bool TypeChecker::visit(Method *AstNode, Ast **SrcPtr) {
    dumpSema("Method");
    Ast *&MTy = AstNode->getName();
    if(!visit(MTy, &MTy)){
        err::err_out(MTy, "unable to resolve interface type", MTy->toString());
        return false;
    }
    Lexeme &SName = static_cast<StructStmt *>(MTy->getDecl())->getName();

    Type *AssociateTy = MTy->getTypeInfo();
    if(!AssociateTy) {
        err::err_out(MTy, MTy->toString() , "type is not in this scope");
        return false;
    }
    if(!AssociateTy->isStructTy()) {
        err::err_out(MTy, "type should be struct found - ", MTy->toString());
        return false;
    }
    std::map<std::string, Type*>impl;
    auto st = static_cast<StructType*>(AssociateTy);
    Vec<Ast*> &impls = AstNode->getImpl();

    // first apply name mangling to all method function because
    // it might be possible that if any method function can call any other method function 
    // that is not mangled and inserted in MethodHandler so, it would give error
    for(size_t i = 0, siz = impls.size(); i < siz; i++) {
        Type *fnty = nullptr;
        FunctionDef *Fn = static_cast<FunctionDef *>(impls[i]);
        FunctionProto *FnProto = Fn->getFnProto();
        Lexeme &FnLxm = FnProto->getFuncName();
        std::string FName = FnLxm.getStr();
        FnProto->getFuncName().setDataStr(mangle_name(FName, SName.getStr(), FnProto));
        if(MT.Has(FName)) {
            err::err_out(FnProto, "redefination of function with name ", FName);
            return false;
        }
        if(!visit(FnProto, asAst(&FnProto))){
            return false;
        }
        MT.insert(FnLxm.getStr(), FnProto);
    }

    for(size_t i = 0, siz = impls.size(); i < siz; i++) {
        if(!visit(impls[i], &impls[i])){
            return false;
        }
    }
    dumpSema2("Method");
    return true;
}


bool TypeChecker::visit(BlockStmt *AstNode, Ast **SrcPtr) {
    dumpSema("BlockStmt");
    Vec<Ast*> &Stmts = AstNode->getStmts();

    for(auto &S :Stmts) {
        if(S->getTypeInfo() || S->Is(NodeImpl)){
            continue;
        }
        if(!visit(S, &S)){
            return false;
        }

    }
    dumpSema2("BlockStmt");
    return true;
}



bool TypeChecker::visit(ForLoop  *AstNode, Ast **SrcPtr) {
    dumpSema("ForLoop");
    Ast *&Var = AstNode->getVar();
    Ast *&Cond = AstNode->getCond();
    Ast *&Incr = AstNode->getIncr();
    BlockStmt *&Blk = AstNode->getBlock();
    if(Var&&!visit(Var, &Var)){
        return false;
    }
    Type *init = Var?Var->getTypeInfo():nullptr;
    if(Cond){
        if(!visit(Cond, &Cond)) {
            return false;
        }
        Type *condTy = Cond->getTypeInfo();
        if(!condTy || !condTy->isIntTy()) {
            err::err_out(AstNode, "condidtion expression should be boolean");
            return false;
        }
        if(!as<IntType>(condTy)->IsIntWidth(1)) {
            err::err_out(AstNode, "condidtion expression should be boolean");
            return false;
        }
    }
    if(Incr&&!visit(Incr, &Incr)){
        return false;
    }

    Type *incr = Incr?Incr->getTypeInfo():nullptr;

    bool isAlready = BranchAllow?true:false;
    BranchAllow = true;
    
    if(!visit(Blk, asAst(&Blk))){
        return false;
    }
    if(!isAlready)
        BranchAllow = false;
    dumpSema2("ForLoop");
    return true;
}


bool TypeChecker::visit(WhileLoop  *AstNode, Ast **SrcPtr) {
    dumpSema("WhileLoop");
    Ast *&Cond = AstNode->getCond();
    BlockStmt *&Blk = AstNode->getBlock();
    if(Cond){
        if(!visit(Cond, &Cond)){
            return false;
        }
        Type *condTy = AstNode->getCond()->getTypeInfo();
        if(!condTy || !condTy->isIntTy()) {
            err::err_out(AstNode, "condidtion expression should be boolean");
            return false;
        }
        if(!as<IntType>(condTy)->IsIntWidth(1)) {
            err::err_out(AstNode, "condidtion expression should be boolean");
            return false;
        }
    }
    bool isAlready = BranchAllow?true:false;
    BranchAllow = true;
    if(!visit(Blk, asAst(&Blk))) {
        return false;
    }
    if(!isAlready)
        BranchAllow = false;
    dumpSema2("WhileLoop");
    return true;
}

bool TypeChecker::visit(IfStmt  *AstNode, Ast **SrcPtr) {
    dumpSema("IfStmt");
    Ast *&Cond = AstNode->getCondV();
    BlockStmt *&IfBlk = AstNode->getIfBlock();
    Ast *&ElBlk = AstNode->getElBlock();
    if(!visit(Cond, &Cond)){
        return false;
    }

    Type *condTy = Cond->getTypeInfo();
    if(!condTy || !condTy->isIntTy()){
        err::err_out(AstNode, "condidtion expression must be boolean");
        return false;
    }
    if(!as<IntType>(condTy)->IsIntWidth(1)) {
        err::err_out(AstNode, "condidtion expression must be boolean");
        return false;
    }

    if(IfBlk&&!visit(IfBlk, asAst(&IfBlk))){
        return false;
    }
    
    if(ElBlk&&!visit(ElBlk, &ElBlk)){
        return false;
    }
    dumpSema2("IfStmt");
    return true;
}


bool TypeChecker::visit(UseStmt *AstNode, Ast **SrcPtr) {    
    dumpSema("UseStmt");
    dumpSema2("UseStmt");
    return true;
}

} 