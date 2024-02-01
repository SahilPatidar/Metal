#pragma once
#include"Context.hpp"


#include"Module.hpp"
#include"lex/lex.hpp"
#include"analyzer/Resolve.hpp"
#include"analyzer/Sema.hpp"
#include"parser/Parser.hpp"
#include"utils/File.hpp"
namespace ast{
    /// @brief working on Builder class to create Ast Node
    // class Builder{
    //     using StmtType = PremitiveType;
    //     StmtType *getInt8Ty();
    //     StmtType *getInt16Ty();
    //     StmtType *getInt32Ty();
    //     StmtType *getInt64Ty();
    //     StmtType *getFloatTy();
    //     StmtType *getDoubleTy();
    //     StmtType *getInt1Ty();
    //     StmtType *getVoidTy();

    //     StmtType *getInt8PtrTy();
    //     StmtType *getInt16PtrTy();
    //     StmtType *getInt32PtrTy();
    //     StmtType *getInt64PtrTy();
    //     StmtType *getFloatPtrTy();
    //     StmtType *getDoublePtrTy();
    //     StmtType *getInt1PtrTy();
    //     StmtType *getVoidPtrTy();

    //     StmtType *getVoidTy();
    //     StmtType *getVoidTy();

    //     FunctionDef *CreateFunctionDef();
    //     FunctionProto *CreateFunctionProto();
    //     StructStmt *CreateStructStmt();
    //     Expression *CreateCallExpr();
    //     private:
    //         Module *Mod;
    // };
}