#include"../../include/analyzer/Sema.hpp"
#include"../../include/analyzer/Value.hpp"
#include"../../include/Error.hpp"
#include"../../include/Module.hpp"
// #include"analyzer/TypeChecker.hpp"

namespace ast {


bool TypeChecker::visit(UserDefinedTy *AstNode, Ast **Base){
    dumpSema("UserDefinedTy");
    AstNode->setConst();
    dumpSema2("UserDefinedTy");
    return true;
}



bool TypeChecker::visit(PremitiveType  *AstNode, Ast **Base) {
    dumpSema("PremitiveType");
    Type *ty = nullptr;
    switch (AstNode->getType().getTokType())
    {
    case I8:
        ty = IntType::Create(mgr, 8, true);
        break;
    case I16:
        ty = IntType::Create(mgr, 16, true);
        break;
    case I32:
        ty = IntType::Create(mgr, 32, true);
        break;
    case I64:
        ty = IntType::Create(mgr, 64, true);
        break;
    case I128:
        ty = IntType::Create(mgr, 128, true);
        break;
    case F32:
        ty = FloatType::Create(mgr, 32);
        break;
    case F64:
        ty = FloatType::Create(mgr, 64);
        break;
    case UI8:
        ty = IntType::Create(mgr, 8,false);
        break;
    case UI16:
        ty = IntType::Create(mgr, 16,false);
        break;
    case UI32:
        ty = IntType::Create(mgr, 32,false);
        break;
    case UI64:
        ty = IntType::Create(mgr, 64, false);
        break;
    case BOOL:
        ty = IntType::Create(mgr, 1,false);
        break;
    default:
        err::err_out(AstNode, "unable to resolve");
        return false;
    }
    AstNode->setType(ty);
    dumpSema2("PremitiveType");
    return true;
}

bool TypeChecker::visit(Void *AstNode, Ast **Base) {
    dumpSema("void");
    AstNode->setType(VoidType::Create(mgr));

    dumpSema2("void");
    return true;
}

bool TypeChecker::visit(FnType  *AstNode, Ast **Base) {
    dumpSema("FnType");
    std::vector<Type*>pTy;
    Ast *Ret = AstNode->getRetType();
    if(!AstNode->getParamType().empty()) {
        std::vector<Ast*>&pTys = AstNode->getParamType();
        for(int i = 0, size = pTys.size(); i < size; i++) {
            if(!visit(pTys[i], &pTys[i])){
                err::err_out(AstNode, "falied to determined parameter type for fn type");
                return false;
            }
            pTy.push_back(pTys[i]->getTypeInfo());
        }
    }
    Type* ret = nullptr;
    if(Ret){
        if(!visit(Ret, &AstNode->getRetType())){
            err::err_out(AstNode, "falied to determined return type for fn type");
            return false;
        }
        ret = Ret->getTypeInfo();
    }
    AstNode->setType(FunctionType::Create(mgr, pTy, ret));
    dumpSema2("FnType");
    return true;
}


bool TypeChecker::visit(Array *AstNode, Ast **Base) {
    dumpSema("Array");
    Ast *&ArrTy = AstNode->getArrayTy();
    if(!visit(ArrTy, &ArrTy)){
        err::err_out(AstNode, "failed to determined array type");
        return false;
    }

    Type *Ty = ArrTy->getTypeInfo();

    size_t Dim = 0;
    Ast *&arrDim = AstNode->getArraySize();
    if(!visit(arrDim, &arrDim)){
        err::err_out(arrDim, "failed to determined array size type");
        return false;
    }
    
    Type *ty = arrDim->getTypeInfo();

    if(!arrDim->IsConst() && !arrDim->IsTydConst()){
        err::err_out(arrDim, "array size should be const\n");
        return false;
    }
    if(!valpass.visit(arrDim, &arrDim)) {
        err::err_out(arrDim, "failed to determined size of array type");
        return false;
    }
    VALUE* val = arrDim->getValueInfo();
    if((ty->type() != Type::IntTy) || (val->getValTy() != VALUE::VInt)){
        err::err_out(arrDim, ty->toStr() +" can not be used to defined array size, type should be integer");
        return false;
    }
    if(as<IntType>(ty)->IsIntWidth(1)){
        err::err_out(arrDim, ty->toStr() +" can not be used to defined array size, type should be integer");
        return false;
    }
    int64_t ival = static_cast<IntVal *>(val)->getVal();
    if(ival <= 0){
        err::err_out(arrDim, "array size can not be less than or equal to 0");
        return false;
    }
    if(!arrDim->Is(NodeNumLit)) {
        const StmtLoc *loc = arrDim->getStmtLoc();
        NumericLiteral *NumData = NumericLiteral::Create(mgr, loc, Lexeme(loc, ival, INT));
        NumData->setType(ty);
        NumData->setConst();
        NumData->setValue(val);
        arrDim = NumData;
    }

    Dim = ival;
    
    AstNode->setType(ArrayType::Create(mgr,  ArrTy->getTypeInfo(), Dim));
    dumpSema2("Array");
    return true;
}


} 