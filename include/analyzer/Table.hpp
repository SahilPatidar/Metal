#pragma once
#include<map>

template<typename T>
class StackV{
private:
    std::map<std::string, T>info;
public:
    StackV() {}
    ~StackV() {}

    inline void add(std::string &n, T Node) {
        info.insert({n, Node});
    }
    inline T getInfo(const std::string &n)  { 
        return info.find(n) == info.end()? 0: info[n]; 
    }
    inline bool isempty() const { return info.empty(); }

    inline bool Has(const std::string &n) {
        return info.find(n) != info.end();
    }

};


template<typename T>
class FStack{
private:
    std::vector<StackV<T>> stack;
public:
    FStack() {}
    ~FStack(){}


    // FunctionType *getFunc() const noexcept { return Func; }
    
    inline void add(std::string &n, T Node) {
        stack.back().add(n,Node);
    }
    inline void pushStack()  { stack.emplace_back(); }
    inline void popStack()  { stack.pop_back(); }
    inline bool empty()  { return stack.empty(); }

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
    // void setFn(FunctionType *Fn) noexcept { Func = Fn;}
    T getInfo(const std::string &n, bool Top) {
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
    std::vector<FStack<T>>funcstack;
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
    
    bool addInfo(std::string n, T Node, bool global = false) {
        if(!global&&!funcstack.empty()) {
            funcstack.back().add(n,Node);
        }
            
        if(global){
            globalDecl.add(n, Node);
        }
        return true;
    }
    
    void updateGlobalInfo(std::string n, T Node) {
        globalDecl.add(n, Node);
    }

    // inline FunctionType *getFuncBack() { return funcstack.back().getFunc(); }
    inline FStack<T> getFuncTop() { return HasFunc()?funcstack.back():NULL; }
    
    
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

    T getInfo(const std::string &n, bool Top = false) {
        if(!funcstack.empty()){
            T info = funcstack.back().getInfo(n, Top);
            if(info || Top){
                return info;
            }
        }
        return globalDecl.getInfo(n);
    }
};
