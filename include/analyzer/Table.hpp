#pragma once
#include"../Core.hpp"

template<typename T>
class StackV{
private:
    ast::Map<ast::String, T>info;
public:
    StackV() {}
    ~StackV() {}

    inline void add(ast::String &n, T Node) {
        info.insert({n, Node});
    }
    inline T getInfo(const ast::String &n)  { 
        return info.find(n) == info.end()? 0: info[n]; 
    }
    inline bool isempty() const { return info.empty(); }

    inline bool Has(const ast::String &n) {
        return info.find(n) != info.end();
    }

};


template<typename T>
class FStack{
private:
    ast::Vec<StackV<T>> stack;
public:
    FStack() {}
    ~FStack(){}


    // FunctionType *getFunc() const noexcept { return Func; }
    
    inline void add(ast::String &n, T Node) {
        stack.back().add(n,Node);
    }
    inline void pushStack()  { stack.emplace_back(); }
    inline void popStack()  { stack.pop_back(); }
    inline bool empty()  { return stack.empty(); }

    bool Has(const ast::String &n, bool Top) {
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
    // void setFn(FunctionType *Fn) noexcept { Func = Fn;}
    T getInfo(const ast::String &n, bool Top) {
        ssize_t i = stack.size()-1;
        while(i >= 0) {
            T V = stack[i].getInfo(n);
            if(Top || V){
                return V;
            }
            i--;
        }
        return nullptr;
    }
};


template<typename T>
class Table{
private:
    ast::Vec<FStack<T>>funcstack;
    StackV<T> globalDecl;
public:
    Table() {}
    ~Table() {}
    
    inline void Push_Stack() {
        if(!funcstack.empty())funcstack.back().pushStack();
    }
    
    inline void Pop_Stack() {
        if(!funcstack.empty())funcstack.back().popStack();
    }
    
    inline void Push_Func() {
        funcstack.emplace_back();
        funcstack.back().pushStack();
    }
    
    inline void Pop_Func()  {
        funcstack.pop_back();
    }
    inline bool HasFunc()  {
        return !funcstack.empty();
    }
    
    bool addInfo(ast::String n, T Node, bool global = false) {
        if(!global&&!funcstack.empty()) {
            funcstack.back().add(n,Node);
        }
            
        if(global){
            globalDecl.add(n, Node);
        }
        return true;
    }
    
    void updateGlobalInfo(ast::String n, T Node) {
        globalDecl.add(n, Node);
    }

    // inline FunctionType *getFuncBack() { return funcstack.back().getFunc(); }
    inline FStack<T> getFuncTop() { return HasFunc()?funcstack.back():NULL; }
    
    
    // Type* getGlobalFunc(ast::String &n);
    
    bool Has(const ast::String &n, bool Top = false) {
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

    T getInfo(const ast::String &n, bool Top = false) {
        if(!funcstack.empty()){
            T info = funcstack.back().getInfo(n, Top);
            if(info || Top){
                return info;
            }
        }
        return globalDecl.getInfo(n);
    }
};
