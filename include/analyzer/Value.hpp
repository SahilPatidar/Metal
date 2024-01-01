#pragma once
#include<map>
#include"../ResMgr.hpp"
// #include"../parser/type.hpp"
// #include"../lex/lex.hpp"

namespace ast{




class VALUE {
public:

    enum ValID{
        VInt,
        VFlt,
        VArray,
        VStruct,
        VEnum,
        VCharArr,
        VBool,
        VPtr,
        VFUN
    };


    VALUE(ValID _vty)
    :vty(_vty) {}
    virtual ~VALUE() = default;

    inline bool Is(const ValID val) const noexcept { return val == vty; }
    inline ValID getValTy() const noexcept { return vty; }
    virtual VALUE* clone(ResourceMgr &mgr) noexcept = 0;
    virtual bool updateValue(VALUE *val) = 0;

protected:
    ValID vty;
};

class IntVal: public VALUE {
private:
    int64_t val;
public:
    IntVal(int64_t &_val, ValID vty)
    :VALUE(vty), val(_val) {}
    ~IntVal() {}

    static IntVal *Create(ResourceMgr &mgr, int64_t _val, ValID vty = VInt);
    VALUE* clone(ResourceMgr &mgr) noexcept;
    bool updateValue(VALUE *_val);
    void updateValue(int64_t _val) noexcept { val = _val; }
    inline int64_t getVal() noexcept { return val; }
};

class FltVal: public VALUE {
    double val;
    public:
    FltVal(double &_val)
    :VALUE(ValID::VFlt), val(_val) {}
    ~FltVal(){}

    static FltVal *Create(ResourceMgr &mgr, double _val);
    VALUE* clone(ResourceMgr &mgr) noexcept;
    bool updateValue(VALUE *_val);
    void updateValue(double _val) noexcept { val = _val; }
    inline double getVal() noexcept { return val; }
};

// class TyVal: public VALUE {
// private:
//     Type* ty;
// public:
//     TyVal(Type *_ty)
//     :VALUE(ValID::VInt), ty(_ty) {}
//     ~TyVal();

//     bool updateValue(VALUE *val);
//     bool IsStruct() const { return ty->type() == TypeStruct; }
//     bool IsFunc() const { return ty->type() == TypeFunction; }
// };

// class PtrVal: public VALUE {
//     VALUE *val;
//     public:
//     PtrVal(VALUE *_val)
//     :VALUE(ValID::VPtr), val(_val) {}
//     ~PtrVal();

//     bool updateValue(VALUE *val);
//     inline VALUE *&getVal() { return val; }
// };

class ArrayVal: public VALUE {
private:
    std::vector<VALUE*>vals;
public:
    ArrayVal(std::vector<VALUE*>&_vals)
    :VALUE(ValID::VArray), vals(_vals) {}
    ~ArrayVal(){}
    static ArrayVal *Create(ResourceMgr &mgr, const std::vector<VALUE*>&_vals); 
    VALUE* clone(ResourceMgr &mgr) noexcept;
    inline std::vector<VALUE*> &getVals() { return vals; }
    bool updateValue(VALUE *val);
};


class StructVal: public VALUE {
    std::map<std::string, VALUE*>vals;
    public:
    StructVal(std::map<std::string, VALUE*> &_vals)
    :VALUE(ValID::VStruct), vals(_vals) {}
    ~StructVal(){}

    static StructVal *Create(ResourceMgr &mgr, const std::map<std::string, VALUE*> &_vals);
    VALUE* clone(ResourceMgr &mgr) noexcept;
    inline void insert(std::string &id, VALUE* val) { vals.insert({id, val}); }
    inline std::map<std::string, VALUE*> &getVals() noexcept { return vals; }
    inline VALUE* getVal(const std::string &s)  noexcept {
        return vals.find(s) == vals.end()?0:vals[s];
    }
    bool updateValue(VALUE *val);
};

// class FuncVal: public VALUE {
//     FunctionType *funcval;
//     public:
//     FuncVal(FunctionType *_funcval)
//     :VALUE(ValID::VFUN), funcval(_funcval) {}
//     ~FuncVal();

//     inline FunctionType *&getVals() { return funcval; }
//     bool updateValue(VALUE *val);
// };

}