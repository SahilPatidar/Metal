#include"../../include/codegen/LLVMCodeGen.hpp"
#include<llvm/IR/DerivedTypes.h>
#include<llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include"../../include/Error.hpp"
#include"../../include/parser/type.hpp"
#include<iostream>
#include<stdlib.h>

namespace codegen{


Type *IRCodegenVisitor::codeGenTy(ast::Ast *AstNode) {
    dumpir1(__func__);
    switch (AstNode->getStmtTy())
    {
    case ast::NodePreDefTy:
        return codeGenPremitiveType(static_cast<ast::PremitiveType *>(AstNode));
        break;
    case ast::NodePrefix:
    {
        ast::PrefixExpr *PtrTy = static_cast<ast::PrefixExpr *>(AstNode);
        Type *Ty = codeGenTy(PtrTy->getBase());
        Ty = PointerType::get(Ty, 0);
        if(!Ty) {
            err::err_out(PtrTy, "Failed to generate IR");
            return nullptr;
        }
        return Ty;
    }
        break;
    case ast::NodeIdent:
    {
        ast::Identifier *Ident = static_cast<ast::Identifier *>(AstNode);
        std::cout<<Ident->getIdent()<<std::endl;
        if(NamedTypes.find(Ident->getIdent()) != NamedTypes.end()){
            return NamedTypes[Ident->getIdent()];
        }
        if(!codeGenStmt(Ident->getDecl())){
            return nullptr;
        }
        Type *Ty = NamedTypes[Ident->getIdent()];
        if(!Ty){
            err::err_out(AstNode, "Failed to generate IR");
            return nullptr;
        }
        return Ty;
    }
        break;
    case ast::NodeFnTy:
        return codeGenFnType(static_cast<ast::FnType *>(AstNode));
        break;
    case ast::NodeArray:
        return codeGenArray(static_cast<ast::Array *>(AstNode));
        break;
    case ast::NodeVoid:
        return codeGenVoidTy(static_cast<ast::Void *>(AstNode));
        break;
    default:
        break;
    }
        dumpir2(__func__);
    return nullptr;
}


Type *IRCodegenVisitor::codeGenFnType(ast::FnType *AstNode) {
    dumpir1("FnType");
    ast::FnType *Fn = static_cast<ast::FnType *>(AstNode);
    std::vector<ast::Ast *>&PTy = Fn->getParamType();
    Type *RetTy = nullptr;
    if(Fn->getRetType()){
        RetTy = codeGenTy(Fn->getRetType());
    }else{
        RetTy = Builder.getVoidTy();
    }
    if(!RetTy) {
        err::err_out(Fn, "Failed to generate IR");
        return nullptr;
    }

    std::vector<Type *>Tys;
    for(auto &P :PTy) {
        Tys.push_back(codeGenTy(P));
        if(!Tys.back()){
            err::err_out(Fn, "Failed to generate IR");
            return nullptr;
        }
    }
    dumpir2("FnType");
    return PointerType::get(FunctionType::get(RetTy, Tys, false), 0);
}


Type *IRCodegenVisitor::codeGenPremitiveType(ast::PremitiveType *AstNode) {
    dumpir1("PremitiveType");
    switch (AstNode->getType().getTokType())
    {
    case ast::I8:
    case ast::UI8:
        return Type::getInt8Ty(Context);
    case ast::I16:
    case ast::UI16:
        return Type::getInt16Ty(Context);
    case ast::I32:
    case ast::UI32:
        return Type::getInt32Ty(Context);
    case ast::I64:
    case ast::UI64:
        return Type::getInt64Ty(Context);
    case ast::I128:
        return Type::getInt128Ty(Context);
    case ast::F32:
        return Type::getFloatTy(Context);
    case ast::F64:
        return Type::getDoubleTy(Context);
    case ast::BOOL:
        return Type::getInt1Ty(Context);
    default:
        break;
    }
    return nullptr;
}


Type *IRCodegenVisitor::codeGenVoidTy(ast::Void *AstNode ) {
    return Builder.getInt8Ty();
}
Type *IRCodegenVisitor::codeGenArray(ast::Array *AstNode ) {
    dumpir1("Array");
    ast::Ast *size = AstNode->getArraySize();
    Type* Ty = codeGenTy(AstNode->getArrayTy());
    if(!Ty) {
        return nullptr;
    }

    ArrayType *ArrTy = ArrayType::get(Ty, static_cast<ast::NumericLiteral*>(size)->getLexeme().getDataInt());
    if(!ArrTy) {
        return nullptr;
    }
    addTy(AstNode->getTypeInfo()->getuId(), ArrTy);
    dumpir2("Array");
    return ArrTy;
}


Type *IRCodegenVisitor::getTypeUsingStmtTypeInfo(ast::Type *Ty) {
    dumpir1(__func__);
    Type *IRTy = getStoredTy(Ty->getuId());
    if(IRTy) {
        return IRTy;
    }

    switch (Ty->type())
    {
    case ast::Type::ArrayTy:
    {
        ast::ArrayType *StmtArrTy = static_cast<ast::ArrayType *>(Ty);
        size_t size = StmtArrTy->getSize();
        Type *IRArrTy = getTypeUsingStmtTypeInfo(StmtArrTy->getArrType());

        IRArrTy = ArrayType::get(IRArrTy, size);
        if(!IRArrTy){
            std::cout<<"array type to ir type failed"<<std::endl;
            return nullptr;
        }

        IRTy = IRArrTy;
    }
    break;
    case ast::Type::StructTy:
    {
        StructType *IRSTy = StructType::get(Context);
        ast::StructType *STy = static_cast<ast::StructType *>(Ty);
        TypeMap.insert({Ty->getuId(), IRSTy});
        const std::vector<ast::Type *>&FTys = STy->getTypeList();
        std::vector<Type *> SFTy;
        for(int i = 0; i < FTys.size(); i++) {
            Type *Ty = getTypeUsingStmtTypeInfo(FTys[i]);
            if(!Ty) {
                std::cout<<FTys[i]->toStr()<<" struct type to ir type failed"<<std::endl;
                return nullptr;
            }
            SFTy.push_back(Ty);
        }
        std::cout<<"return - StructTy"<<std::endl;
        IRSTy->setBody(SFTy);
        std::cout<<"return - StructTy"<<std::endl;
        IRTy = IRSTy;
    }
    break;
    case ast::Type::IntTy:
    {
        int8_t Bit = static_cast<ast::IntType *>(Ty)->getbit();
        if(Bit == 64)
            IRTy = Type::getInt64Ty(Context);
        if(Bit == 32)
            IRTy = Type::getInt32Ty(Context);
        if(Bit == 16)
            IRTy = Type::getInt16Ty(Context);
        if(Bit == 8)
            IRTy = Type::getInt8Ty(Context);
        if(Bit == 1)
            IRTy = Type::getInt1Ty(Context);
        TypeMap.insert({Ty->getuId(), IRTy});
    }
    break;
    case ast::Type::EnumTy:
    {
        ast::IntType *ITy = ast::as<ast::EnumType>(Ty)->getIntTy();
        IRTy = getTypeUsingStmtTypeInfo(ITy);
    }
    break;
    case ast::Type::FltTy:
    {
        int8_t Bit = static_cast<ast::FloatType *>(Ty)->getbit();
        if(Bit == 64)
            IRTy = Type::getDoubleTy(Context);
        if(Bit == 32)
            IRTy = Type::getFloatTy(Context);
        TypeMap.insert({Ty->getuId(), IRTy});
    }
    break;
    case ast::Type::PointerTy:
    {
        ast::PointerType *PtrTy = static_cast<ast::PointerType *>(Ty);
        Type *PTy = getTypeUsingStmtTypeInfo(PtrTy->getTo());
        PTy = PointerType::get(PTy, 0);
        if(!PTy) {
            std::cout<<"ptr type to ir type failed"<<std::endl;
            return nullptr;
        }
        IRTy = PTy;
        TypeMap.insert({Ty->getuId(), IRTy});
    }
    break;
    case ast::Type::RefTy:
    {
        ast::RefType *RTy = static_cast<ast::RefType *>(Ty);
        Type *LRTy = getTypeUsingStmtTypeInfo(RTy->getTo());
        if(!LRTy) {
            std::cout<<"ref type to ir type failed"<<std::endl;
            return nullptr;
        }
        IRTy = LRTy->getPointerTo();
        TypeMap.insert({Ty->getuId(), IRTy});
    }
    break;
    case ast::Type::FunctionTy:
    {
        ast::FunctionType *FnTy = static_cast<ast::FunctionType *>(Ty);
        std::vector<Type *>PTys;
        for(auto &P: FnTy->getParamTypes()) {
            Type *Ty = getTypeUsingStmtTypeInfo(P);
            if(!Ty){
                std::cout<<"parameter type to ir type failed"<<std::endl;
                return nullptr;
            }
            PTys.push_back(Ty);
        }
        Type *ResTy = Type::getVoidTy(Context);
        if(FnTy->getRetType()) 
            ResTy = getTypeUsingStmtTypeInfo(FnTy->getRetType());
        IRTy = FunctionType::get(ResTy, PTys, false);
    }
    break;
    case ast::Type::VoidTy:
    {
        IRTy = Type::getInt8Ty(Context);
    }
    break;
    default:
        break;
    }
    
    dumpir2(__func__);
    return IRTy;
}

}