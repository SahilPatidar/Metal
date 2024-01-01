#pragma once
#include<map>
#include<optional>
#include"../parser/type.hpp"
#include"Value.hpp"

// #include"parser/type.hpp"

using namespace ast;


struct AstNodeInfo {
    Type* type;
    ast::VALUE* val;
    Ast* Node;
};

class StackVal{
private:
    std::map<std::string, AstNodeInfo>info;
public:
    StackVal() {}
    ~StackVal() {}

    inline void add(std::string &n, Type *Ty, ast::VALUE *Val, Ast *Node) {
        info.insert({n, (AstNodeInfo){Ty, Val, Node}});
    }
    inline AstNodeInfo* getAllInfo(const std::string &n)  { 
        return info.find(n) == info.end()? 0: &info[n]; 
    }
    inline bool isempty() { return info.empty(); }

    inline bool Has(const std::string &n) {
        return info.find(n) != info.end();
    }

    inline Type* getTypeInfo(const std::string &n)  { 
        return info.find(n) == info.end()? 0: info[n].type; 
    }
    inline ast::VALUE* getValInfo(const std::string &n)  { 
        return info.find(n) == info.end()? 0: info[n].val; 
    }
};



class FuncStack{
private:
    FunctionType *Func;
    std::vector<StackVal> stack;
public:
    FuncStack(FunctionType *_func)
    : Func(_func) {}
    ~FuncStack(){}


    FunctionType *getFunc() const noexcept { return Func; }
    
    inline void add(std::string &n, Type *Ty, VALUE *Val, Ast *Node) {
        stack.back().add(n, Ty, Val, Node);
    }
    inline void pushStack() { stack.emplace_back(); }
    inline void popStack() { stack.pop_back(); }
    inline bool empty() { return stack.empty(); }

    bool Has(const std::string &n, bool Top) {
        ssize_t i = stack.size()-1;
        while(i >= 0) {
            if(stack[i].Has(n)){
                return true;
            }
            if(Top){
                break;
            }
            i--;
        }
        return false;
    }
    void setFn(FunctionType *Fn) noexcept { Func = Fn;}
    AstNodeInfo* getAll(const std::string &n, bool Top) {
        ssize_t i = stack.size()-1;
        while(i >= 0) {
            AstNodeInfo *V = stack[i].getAllInfo(n);
            if(Top || V){
                return V;
            }
            i--;
        }
        return nullptr;
    }

};

class Registry{
private:
    std::vector<FuncStack>funcstack;
    StackVal globalDecl;
public:
    Registry() {}
    ~Registry() {}
    
    inline void Push_Stack() {
        if(!funcstack.empty())funcstack.back().pushStack();
    }
    
    inline void Pop_Stack() {
        if(!funcstack.empty())funcstack.back().popStack();
    }
    
    inline void Push_Func(FunctionType *_func) {
        funcstack.emplace_back(_func);
        funcstack.back().pushStack();
    }
    
    inline void Pop_Func() {
        funcstack.pop_back();
    }
    inline bool HasFunc() {
       return !funcstack.empty();
    }
    
    bool addInfo(std::string n, Type *type, ast::VALUE *val, Ast *Node, bool global = false) {
        if(!global&&!funcstack.empty()) {
            funcstack.back().add(n, type, val, Node);
        }
            
        if(global){
            globalDecl.add(n, type, val, Node);
        }
        return true;
    }
    
    void updateGlobalInfo(std::string n, Type *type, ast::VALUE *val, Ast* Node) {
        globalDecl.add(n, type, val, Node);
    }

    inline FunctionType *getFuncBack() { return funcstack.back().getFunc(); }
    inline FuncStack getFuncTop() { return funcstack.back(); }
    
    Type* getType(const std::string &n, bool Top = false) {
        if(!funcstack.empty()){
            Type *Ty = funcstack.back().getAll(n, Top)->type;
            if(Ty || Top){
                return Ty;
            }
        }
        return globalDecl.getAllInfo(n)->type;
    }
    
    // Type* getGlobalFunc(std::string &n);
    
    bool Has(const std::string &n, bool Top = false) {
        if(!funcstack.empty()){
            if(funcstack.back().Has(n, Top)) {
                return true;
            }
            if(Top){
                return false;
            }
        }
        return globalDecl.Has(n);
    }

    ast::VALUE* getVal(std::string n, bool Top = false) {
        if(!funcstack.empty()){
            VALUE *val = funcstack.back().getAll(n, Top)->val;
            if(val || Top){
                return val;
            }
        }
        return globalDecl.getAllInfo(n)->val;
    }
    AstNodeInfo* getAllInfo(const std::string &n, bool Top = false) {
        if(!funcstack.empty()){
            AstNodeInfo *info = funcstack.back().getAll(n, Top);
            if(info || Top){
                return info;
            }
        }
        return globalDecl.getAllInfo(n);
    }
};






