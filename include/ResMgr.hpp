#pragma once
#include<iostream>
#include<vector>
#include"IncHeader.hpp"

namespace ast{
class StmtLoc;

// reference from scribe language
class ResourceMgr{
private:    
    std::vector<Module*>mod;
    std::vector<Ast*>stmt;
    std::vector<StmtLoc*>loc;
    std::vector<VALUE*>val;
    std::vector<Type*>type;
public:
    ResourceMgr() {}
    ~ResourceMgr();

    template<typename T, typename... Args> T *CreateStmt(Args... args)
	{
		T *res = new T(args...);
        stmt.push_back(res);
		return res;
	} 

    template<typename T, typename... Args> T *CreateTy(Args... args)
	{
		T *res = new T(args...);
        type.push_back(res);
		return res;
	} 

    template<typename T, typename... Args> T *CreateVal(Args... args)
	{
		T *res = new T(args...);
        val.push_back(res);
		return res;
	} 

    Module *CreateMod(const ModuleInfo &_modinfo) noexcept;

    StmtLoc *getLoc(Module *_mod, int line, int col) noexcept;
    inline Module *getMod() const noexcept { return mod.back(); }

};


// class ResourceMgr{
// private:    
//     std::vector<Module*>mod;
//     std::vector<Ast*>stmt;
//     std::vector<StmtLoc*>loc;
//     std::vector<VALUE*>val;
//     std::vector<Type*>type;

//     IntType *Int1Ty{nullptr};
//     IntType *Int8Ty{nullptr};
//     IntType *Int16Ty{nullptr};
//     IntType *Int32Ty{nullptr};
//     IntType *Int64Ty{nullptr};

//     IntType *uInt8Ty{nullptr};
//     IntType *uInt16Ty{nullptr};
//     IntType *uInt32Ty{nullptr};
//     IntType *uInt64Ty{nullptr};

//     FloatType *DoubleTy{nullptr};
//     FloatType *FloatTy{nullptr};
//     VoidType *VoidTy{nullptr};
// public:
//     ResourceMgr() {}
//     ~ResourceMgr();

//     template<typename T, typename... Args> T *CreateStmt(Args... args)
// 	{
// 		T *res = new T(args...);
//         stmt.push_back(res);
// 		return res;
// 	} 

//     template<typename T, typename... Args> T *CreateTy(Args... args)
// 	{
// 		T *res = new T(args...);
//         type.push_back(res);
// 		return res;
// 	} 


//     IntType *getInt1Ty() {
//         if(Int1Ty == nullptr) {
//             Int1Ty = new IntType(1, true);
//         }
//         return Int1Ty;
//     }
//     IntType *getInt8Ty() {
//         if(Int8Ty == nullptr) {
//             Int8Ty = new IntType(8, true);
//         }
//         return Int8Ty;
//     }
//     IntType *getInt16Ty() {
//         if(Int16Ty == nullptr) {
//             Int16Ty = new IntType(16, true);
//         }
//         return Int16Ty;
//     }
//     IntType *getInt32Ty(){
//         if(Int32Ty == nullptr) {
//             Int32Ty = new IntType(32, true);
//         }
//         return Int32Ty;
//     }
//     IntType *getInt64Ty() {
//         if(Int64Ty == nullptr) {
//             Int64Ty = new IntType(64, true);
//         }
//         return Int64Ty;
//     }

//     IntType *getuInt8Ty() {
//         if(uInt8Ty == nullptr) {
//             uInt8Ty = new IntType(8, false);
//         }
//         return uInt8Ty;
//     }
//     IntType *getuInt16Ty() {
//         if(uInt16Ty == nullptr) {
//             uInt16Ty = new IntType(16, false);
//         }
//         return uInt16Ty;
//     }
//     IntType *getuInt32Ty() {
//         if(uInt32Ty == nullptr) {
//             uInt32Ty = new IntType(32, true);
//         }
//         return uInt32Ty;
//     }
//     IntType *getuInt64Ty() {
//         if(uInt64Ty == nullptr) {
//             uInt64Ty = new IntType(64, true);
//         }
//         return uInt64Ty;
//     }

//     FloatType *getDoubleTy() {
//         if(DoubleTy == nullptr) {
//             DoubleTy = new FloatType(64);
//         }
//         return DoubleTy;
//     }

//     FloatType *getFloatTy()  {
//         if(FloatTy == nullptr) {
//             FloatTy = new FloatType(32);
//         }
//         return FloatTy;
//     }

//     VoidType *getVoidTy() {
//         if(VoidTy == nullptr) {
//             VoidTy = new VoidType();
//         }
//         return VoidTy;
//     }

//     template<typename T, typename... Args> T *CreateVal(Args... args)
// 	{
// 		T *res = new T(args...);
//         val.push_back(res);
// 		return res;
// 	} 

//     Module *CreateMod(const ModuleInfo &_modinfo) noexcept;

//     StmtLoc *getLoc(Module *_mod, int line, int col) noexcept;
//     inline Module *getMod() const noexcept { return mod.back(); }

// };



class StmtLoc{
public:
    StmtLoc(Module *_mod, int _line, int _col)
    : mod(_mod), line(_line), col(_col) {}
    ~StmtLoc(){}

    inline std::string getString() const noexcept {
        return std::to_string(line) + ":" + std::to_string(col);
    }
    
    inline int getCol() const noexcept {
        return col;
    }

    inline int getLine() const noexcept {
        return line;
    }
    inline Module* getMod() const noexcept {
        return mod;
    }

    static StmtLoc *Create(ResourceMgr &mgr, Module *_mod, int _line, int _col) {
        return mgr.getLoc(_mod, _line, _col);
    }
private:
    Module *mod;
    int line;
    int col;
};

}
