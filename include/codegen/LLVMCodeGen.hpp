#pragma once
#include<iostream>
#include<map>


#include<llvm/IR/DIBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include"../parser/Ast.hpp"
#include"../analyzer/Table.hpp"


namespace codegen {
using namespace llvm;

class IRCodegenException : public std::exception {
  std::string errorMessage;

 public:
  IRCodegenException(std::string msg)
      : errorMessage("IR Codegen Error: " + msg){};
  const char *what() const throw() { return errorMessage.c_str(); }
};

class IRCodegenVisitor {
private:
    LLVMContext &Context;
    llvm::Module &TheModule;
    IRBuilder<> &Builder;
    Table<Value *> ResMgr;
    std::map<std::string, Value *> NamedValues;
    std::map<std::string, llvm::Type *> NamedTypes;
    llvm::Type *CurTy;
    std::vector<BasicBlock *>LoopBagin;
    std::vector<BasicBlock *>LoopEnd;

    std::vector<BasicBlock *>FalseBB;
    std::vector<BasicBlock *>TrueBB;

    std::map<uint64_t, Type *>TypeMap;
    bool isConstF{false};
public:
    IRCodegenVisitor(LLVMContext &_Context, llvm::Module &_TheModule, IRBuilder<> &_Builder)
    :Context(_Context), TheModule(_TheModule), Builder(_Builder) {}
    ~IRCodegenVisitor(){}

    void insertTy(uint64_t ID, Type *Ty) { TypeMap.insert({ID, Ty}); }
    bool HasTy(uint64_t ID) { return TypeMap.find(ID) != TypeMap.end(); }
    Type *getTy(uint64_t ID) { return TypeMap.find(ID) != TypeMap.end()?TypeMap[ID]:nullptr; }

    inline void putTrueBB(BasicBlock *BB) { TrueBB.push_back(BB); }
    inline void dropTrueBB() { TrueBB.pop_back(); }

    inline void putFalseBB(BasicBlock *BB) { FalseBB.push_back(BB); }
    inline void dropFalseBB() { FalseBB.pop_back(); }

    void dumpir1(std::string str) {
    std::cout<<"step :: entering in "<<str<<std::endl;
    }
    void dumpir2(std::string str){
        std::cout<<"step :: returning in "<<str<<std::endl;
    }
    // Type *getStoredTy(uint64_t);
    inline Type *getStoredTy(uint64_t TID) {
        return TypeMap.find(TID) != TypeMap.end()?TypeMap[TID]: nullptr;
    }
    inline void addTy(uint64_t TID, Type *Ty) {
         TypeMap.insert({TID, Ty});
    }
    Value *codeGen(ast::Ast *tree);
    Value *getTypeSize(Type *Ty);
    Value *getTypeSizeInBit(Type *Ty);

    Constant *codeGenConst(ast::Ast *AstNode);

    PHINode *GenPHI(Value *Val, Type *Ty);


    Value *codeGenMemCpy(Type *Ty, Value *Ptr, Value *Val);
    Value *codeGenPrintf(ast::FieldExpr *ArgF);
    Value *codeGenScanf(ast::FieldExpr *ArgF);
    Value *codeGenFree(ast::FieldExpr *ArgF);
    Value *codeGenMalloc(ast::FieldExpr *ArgF);

    Value *codeGenImportValue(ast::UseStmt *Imported);
    Value *codeGenImportStmt(ast::Ast *Stmt);
    
    FunctionType *codegenFunctionType(ast::FunctionProto &FunctionProto);

    Value *codegenPhiAndCond(ast::Expression &Expr);
    Value *codegenPhiOrCond(ast::Expression &Expr);
    Value *codegenAndCond(ast::Expression &Expr);
    Value *codegenOrCond(ast::Expression &Expr);
    
    Value *codegenBinaryExpr(ast::Expression &Expr);
    Value *codegenStructExpr(ast::Expression &Expr, Value *Alloca = nullptr);
    Value *codegenArg(ast::Ast *Expr, Type *Ty);
    Value *codegenCallExpr(ast::Expression &Expr, Value *Alloca = nullptr);

    Value *codeGenExtCall(ast::Expression &Expr);

    Value *codegenIntCast(Value *Val, Type *DestTy);
    Value *codegenFPCast(Value *Val, Type *DestTy);
    Value *codegenFPExtCast(Value *Val, Type *DestTy);
    Value *codegenPtrCast(Value *Val, Type *DestTy);

    Value *codegenCastExpr(ast::Expression &Expr);
    Value *codegenIndexExpr(ast::Expression &Expr);
    Value *codegenMemExpr(ast::Expression &Expr);
    Value *codegenFieldExpr(ast::FieldExpr *AstNode, Value *Alloca = nullptr);
    void IntrinsicFnCodegen();
    Type *getTypeUsingStmtTypeInfo(ast::Type *Ty);
    AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
                                          Argument &Arg);
    AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
                                        Type *Ty);

    Value *LoadValue(ast::Ast *Expr, Value *Val, Type *Ty);

    Value *StoreValue(Value *Val, Value *Ptr, Type *Ty, Type *ValTy);

    Type *getType(Value *Val, ast::Ast *Expr);

    llvm::Type *codeGenTy(ast::Ast *AstNode);
    Value *codeGenStmt(ast::Ast *AstNode, Value *Alloca = nullptr);
    Value *codeGenBlockStmt(ast::BlockStmt *AstNode, BasicBlock *BB = nullptr);
    Value *codeGenFunctionDef(ast::FunctionDef *AstNode);
    Value *codeGenWhileLoop(ast::WhileLoop *AstNode);
    Value *codeGenForLoop(ast::ForLoop *AstNode);
    Value *codeGenStructStmt(ast::StructStmt *AstNode);
    Value *codeGenBranchStmt(ast::BranchStmt *AstNode);
    Value *codeGenVarStmt(ast::VarStmt *AstNode);
    Value *codeGenIfStmt(ast::IfStmt *AstNode);
    Value *codeGenMethod(ast::Method *AstNode);
    Value *codeGenReturnStmt(ast::ReturnStmt *AstNode);
    Value *codeGenEnumExpr(ast::EnumExpr *AstNode);
    Value *codeGenFnProto(ast::FunctionProto *AstNode);

    Value *codeGenNewStmt(ast::NewStmt *AstNode);
    Value *codeGenDelStmt(ast::DelStmt *AstNode);
    

    Value *codegenCondExpr(ast::Ast *Expr, BasicBlock *BB1, BasicBlock *BB2);
    Value *codeGenExpression(ast::Expression *AstNode, Value *Alloca = nullptr);
    Value *codeGenGroupedExpr(ast::GroupedExpr *AstNode);
    Value *codeGenPrefixExpr(ast::PrefixExpr *AstNode);
    
    llvm::Type *codeGenArray(ast::Array *AstNode) ;
    llvm::Type *codeGenPremitiveType(ast::PremitiveType *AstNode);
    Value *codeGenIdentifier(ast::Identifier *AstNode );
    llvm::Type *codeGenFnType(ast::FnType *AstNode);
    Type *codeGenVoidTy(ast::Void *AstNode );

    // Value *codeGenFloatLiteral(ast::FloatLiteral *AstNode);
    // Value *codeGenBoolLiteral(ast::BoolLiteral *AstNode);
    // Value *codeGenStringLiteral(ast::StringLiteral *AstNode);
    // Value *codeGenNullLiteral(ast::NullLiteral *AstNode);
    // Value *codeGenNumericLiteral(ast::NumericLiteral *AstNode);
    Constant *codeGenFloatLiteral(ast::FloatLiteral *AstNode);
    Constant *codeGenBoolLiteral(ast::BoolLiteral *AstNode);
    Constant *codeGenNumericLiteral(ast::NumericLiteral *AstNode);
    Constant *codeGenNullLiteral(ast::NullLiteral *AstNode);
    Constant *codeGenStringLiteral(ast::StringLiteral *AstNode);
};

bool InitCodegen(ast::Module *M);
}