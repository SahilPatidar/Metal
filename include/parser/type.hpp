#pragma once
#include<memory>
#include<map>
#include"../lex/lex.hpp"
// #include"../Driver.hpp"
// #include"lex/lex.hpp"

namespace ast{

class Context;
class StructStmt;

template<typename To, typename From> 
inline To *as(From *Var) {
    return static_cast<To *>(Var);
}

class Type{
public:
    enum TypeID {
        IntTy,
        FltTy,
        StrTy,
        BoolTy,
        PointerTy,
        StructTy,
        ArrayTy,
        ConstTy,
        FunctionTy,
        EnumTy,
        RefTy,
        VoidTy,
        ScopeTy,
        UTy
    };

#define IsTyX(Ty, ETy) \
    inline bool is##Ty() const noexcept { return KTy == ETy; }

IsTyX(IntTy, IntTy)
IsTyX(FltTy, FltTy)
IsTyX(BoolTy, BoolTy)
IsTyX(PointerTy, PointerTy)
IsTyX(StructTy, StructTy)
IsTyX(ArrayTy, ArrayTy)
IsTyX(EnumTy, EnumTy)
IsTyX(FunctionTy, FunctionTy)
IsTyX(RefTy, RefTy)
IsTyX(VoidTy, VoidTy)

 Type(TypeID ty)
 :KTy(ty) {
    uId = (uintptr_t)this;
 }
 
 virtual ~Type() = default;
 virtual bool UnaryOpMatch(Tok op) { return false; }
 virtual bool IsCloneOf(Type *To) { return false; }
 virtual bool IsCasteble(Type *To) = 0;
 inline uintptr_t getuId() const noexcept { return uId; }
 inline bool isSameId(uintptr_t _uId) const noexcept { return _uId == uId; }
 inline bool Is(TypeID ty) const noexcept { return ty == KTy; }
 inline TypeID type() const noexcept { return KTy; }
 virtual std::string toStr() noexcept = 0;

 protected:
    uintptr_t uId;
    TypeID KTy;
};



// class UnTy: public Type {
// private:
//     Type *Ty;
//     bool set{false};
// public:
//     UnTy(Type *_Ty)
//     :Type(UTy), Ty(_Ty) {}

//     void setType(Type *_Ty) {
//         if(!set) {
//             Ty = _Ty;
//             set = true;
//         }
//     }
//     inline Type *getTy() const noexcept { return Ty; }
//     bool UnaryOpMatch(Tok op);
//     bool IsCloneOf(Type *To);
//     bool IsCasteble(Type *To);
//     std::string toStr() noexcept;
// };

class IntType: public Type{
private:
    uint16_t bit;
    bool isSign;
public:
    IntType(uint16_t _bit, bool _isSign)
    :Type(TypeID::IntTy), bit(_bit), isSign(_isSign){}
    ~IntType(){}

    bool IsCasteble(Type *To);
    bool IsCloneOf(Type *To);
    bool isSignInt() const noexcept {return isSign;}
    int getbit() const noexcept {return bit;}    
    bool IsIntWidth(uint16_t _bit) const noexcept {return _bit == bit;}    
    bool UnaryOpMatch(Tok op);
    std::string toStr() noexcept;
    static IntType *Create(Context &mgr, uint16_t _bit, bool _isSign);
};



// class VariadicTy: public Type{
//     std::vector<Type*>args;
// public:
//     VariadicTy(std::vector<Type*>&_args)
//     : Type(TypeID::VariadicTy), args(_args) {}
//     ~VariadicTy(){}

//     bool IsCasteble(Type *To);
//     std::vector<Type*>getArgs() const { return args; }
//     bool IsCloneOf(Type *To);

//     bool UnaryOpMatch(Tok op);
//     static AnyType *Create(Context &mgr, std::vector<Type*>&args);
// };



class FloatType: public Type {
private:
    uint16_t bit;
public:
    FloatType(uint16_t _bit)
    :Type(TypeID::FltTy), bit(_bit) {}
    ~FloatType() {}

    bool IsCasteble(Type *To);
    bool IsCloneOf(Type *To);
    int getbit() const {return bit;}
    bool UnaryOpMatch(Tok op);
    std::string toStr() noexcept;

    static FloatType *Create(Context &mgr, uint16_t _bit);
};


class EnumType: public Type {
private:
    IntType *Ty;
public:
    EnumType(IntType *_ITy)
    :Type(TypeID::EnumTy), Ty(_ITy) {}
    ~EnumType() {}

    bool UnaryOpMatch(Tok op);
    bool IsCasteble(Type *To);
    bool IsCloneOf(Type *To);

    inline IntType *getIntTy() const noexcept {  return Ty; }
    std::string toStr() noexcept;
    static EnumType* Create(Context &mgr, IntType *_ITy);
};


class FunctionType: public Type {
private:
    std::vector<Type*>param;
    Type* retype;

public:
    FunctionType(const std::vector<Type*>&_param, Type* _ret)
    :Type(TypeID::FunctionTy), param(_param), retype(_ret) {}
    ~FunctionType() {}

    std::vector<Type*> &getParamTypes() { return param; }
    Type *getPTy(int i) { return (i < param.size())?param[i]:0; }
    inline void updateRetTy(Type *ty) noexcept { retype = ty; }
    inline void updateParam(int id, Type *ty) noexcept {
        param[id] = ty;
    }
    inline Type* getRetType() const noexcept{ return retype; }
    bool IsCasteble(Type *To);
    bool UnaryOpMatch(Tok op);
    bool IsCloneOf(Type *To);
    std::string toStr() noexcept;
    static FunctionType *Create(Context &mgr, const std::vector<Type*>&_param, Type* _ret);

};


class  StructType: public Type{
private:
    std::map<std::string, uint32_t>EleNameTypeList;
    std::vector<Type*>TypeList;
    StructStmt *Struct;
    // std::vector<TypeTy*>Temp;
public:                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    StructType(std::map<std::string, uint32_t>&_EleNameTypeList) 
    :Type(TypeID::StructTy),  EleNameTypeList(_EleNameTypeList) {}
    ~StructType() {}
    inline const std::map<std::string, uint32_t> &getNameTypeList() const noexcept {return EleNameTypeList;}
    // inline const std::vector<std::string> &getNameList() const noexcept { return NameList; }
    inline const std::vector<Type*>& getTypeList() const noexcept { return TypeList; }
    inline bool contains(const std::string &n) const noexcept {
        return EleNameTypeList.find(n) == EleNameTypeList.end()?false:true;
    }
    Type *getType(const std::string &n) const;
    inline uint32_t getIdx(const std::string &n) const {
        return EleNameTypeList.find(n) == EleNameTypeList.end()?10000:EleNameTypeList.at(n);
    }
    inline StructStmt *getStructStmt() const noexcept { return Struct; }
    inline void setStructStmt(StructStmt *_Struct) noexcept { Struct = _Struct; }
    bool UnaryOpMatch(Tok op);
    bool IsCloneOf(Type *To);
    bool IsCasteble(Type *To);
    void InsertField(const std::string &n, Type *ty) {
        EleNameTypeList.insert({n, TypeList.size()});
        TypeList.push_back(ty);
    }
    
    inline void updateField(const std::string &s, Type* ty) {
        if(EleNameTypeList.find(s) != EleNameTypeList.end())
            TypeList[EleNameTypeList[s]] = ty;
    }
    std::string toStr() noexcept;
    // inline std::vector<TypeTy*> &getTemp() {return Temp;}
    // inline bool HasTemp() const {return !Temp.empty();}
    static StructType *Create(Context &mgr, const std::map<std::string, uint32_t>&_EleNameTypeList);
};


class ArrayType: public Type{
private:
    Type* Ty;
    size_t Size;
public:
    ArrayType(Type* _Ty, size_t _Size)
    :Type(TypeID::ArrayTy), Ty(_Ty), Size(_Size) {}
    ~ArrayType() {}

    inline Type *&getArrType() { return Ty; }
    inline size_t getSize() noexcept { return Size; }
    bool UnaryOpMatch(Tok op);
    bool IsCloneOf(Type *To);
    bool IsCasteble(Type *To);
    std::string toStr() noexcept;
    static ArrayType *Create(Context &mgr, Type *_Ty, size_t _Size);
};


// class TypeTy: public Type{
// private:
//     uint32_t TyId;
// public:
//     TypeTy(uint32_t _TyId)
//     :Type(TypeID::ContainedTyTy), TyId(_TyId){}
//     ~TypeTy(){}

//     inline uint32_t getContainedId() const { return TyId; }
//     bool IsCloneOf(Type *To);
//     bool UnaryOpMatch(Tok op);
//     static TypeTy *Create(Context &mgr, uint32_t _TyId);
// };


class ScopeTy: public Type{
private:
    Module *mod;
public:
    ScopeTy(Module *_mod)
    :Type(TypeID::ScopeTy), mod(_mod){}
    ~ScopeTy(){}

    inline Module *getMod() const noexcept { return mod; }
    // inline std::string getScope() const noexcept { return str; }
    // inline bool IsEnum() const { return mask&1; }
    bool IsCloneOf(Type *To); 
    bool UnaryOpMatch(Tok op);
    bool IsCasteble(Type *To);
    // inline bool IsRMod() const noexcept { return mask&1; }
    // inline bool IsMod() const noexcept { return mask&2; }
    std::string toStr() noexcept;
    static ScopeTy *Create(Context &mgr, Module *_mod);
};


class PointerType: public Type{
private:
    bool mut;
    Type* To;
public:
    PointerType(bool _mut, Type* _To)
    :Type(TypeID::PointerTy), mut(_mut), To(_To) {}
    ~PointerType() {}

    inline Type *&getTo() { return To; }
    inline bool HasMut() const noexcept { return mut; }
    inline void setMut() noexcept{
        mut = true;
    }
    size_t getCount() const noexcept;
    PointerType *getPtrOf(Context &mgr, int DefCount);
    void clone(Context &mgr) const noexcept;
    bool UnaryOpMatch(Tok op);
    bool IsCasteble(Type *To);
    bool IsCloneOf(Type *To);
    std::string toStr() noexcept;
    static PointerType *Create(Context &mgr, bool _mut, Type* _To);
};


class RefType: public Type{
private:
    Type* To;
    bool mut;
public:
    RefType(Type *_To, bool _mut)
    :Type(TypeID::RefTy), To(_To), mut(_mut) {}
    ~RefType() {}

    inline Type *getTo() const noexcept {return To;}
    PointerType *getPtr(Context &mgr) noexcept;
    static RefType *Create(Context &mgr, Type *_To, bool _mut);
    bool UnaryOpMatch(Tok op);
    inline bool IsMutRef() const noexcept { return mut; }
    bool IsCloneOf(Type *To);
    std::string toStr() noexcept;
    bool IsCasteble(Type *To);
};

class VoidType: public Type{
public:
    VoidType()
    :Type(TypeID::VoidTy) {}
    ~VoidType() {}

    static VoidType *Create(Context &mgr);
    bool UnaryOpMatch(Tok op);
    bool IsCloneOf(Type *To);
    std::string toStr() noexcept;
    bool IsCasteble(Type *To);
};


}