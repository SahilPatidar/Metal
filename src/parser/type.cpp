#include"../../include/ResMgr.hpp"
#include"../../include/parser/type.hpp"
#include"../../include/Error.hpp"
// #include"parser/type.hpp"
namespace ast {

//////////////////////////////////StructType/////////////////////////////////////////

bool StructType::UnaryOpMatch(lex::Tok op) {
    if(op.getTokType() != lex::STAR && op.getTokType() != lex::AND) {
        return false;
    }
    return true;
}

Type *StructType::getType(const std::string &n) const {
    if(EleNameTypeList.find(n) == EleNameTypeList.end()) {
        return nullptr;
    }
    return TypeList[EleNameTypeList.at(n)];
}

bool StructType::IsCloneOf(Type *To) {
    if(this->getuId() == To->getuId()) {
        return true;
    }
    if(!To->isStructTy()){
        return false;
    }
    StructType *type = static_cast<StructType*>(To);
    const std::vector<Type*> &_TypeList = type->getTypeList();
    const std::map<std::string, uint32_t> &Field = type->getNameTypeList();
    // std::vector<TypeTy*>Temp;
    // ssize_t siz = Field.size();
    if(_TypeList.size() != EleNameTypeList.size()){
        return false;
    }
    // if(Field.size() != EleNameTypeList.size()){
    //     return false;
    // }
    // for(auto &F: Field) {
    //     if(EleNameTypeList.find(F.first) == EleNameTypeList.end()) {
    //         return false;
    //     }
    //     if(!EleNameTypeList[F.first]->IsCloneOf(F.second)) {
    //         return false;
    //     }
    // }
    for(auto &F: Field) {
        if(EleNameTypeList.find(F.first) == EleNameTypeList.end()) {
            return false;
        }
        uint32_t idx = EleNameTypeList[F.first]; 
        if(!TypeList[idx]->IsCloneOf(_TypeList[idx])) {
            return false;
        }
    }
    return true;
}

bool StructType::IsCasteble(Type *To) {
    if(!To->isStructTy()){
        return false;
    }
    StructType *type = static_cast<StructType*>(To);
    const std::vector<Type*> &Field = type->getTypeList();
    int idx = 0;
    for(auto &F: Field) {
        if(!TypeList[idx]->IsCasteble(F)) {
            return false;
        }
        idx++;
    }
    return true;
}


std::string StructType::toStr() noexcept {
    return "struct";
}

StructType *StructType::Create(ResourceMgr &mgr, const std::map<std::string, uint32_t>&_EleNameTypeList) {
    return mgr.CreateTy<StructType>(_EleNameTypeList);
}


 //////////////////////////////////IntType/////////////////////////////////////////



 bool IntType::UnaryOpMatch(lex::Tok op) {
    switch (op.getTokType())
    {
    case lex::MINUS:
    {
        if(bit < 8){
            return false;
        }
        if(!isSign) {
            return false;
        }
    }
    break;
    case lex::STAR:
    case lex::AND:
    case lex::CND_NOT:
    break;
    case lex::NOT:
    {
        if(bit >= 8){
            return false;
        }
    }
        break;
    default:
        return false;
    }
    return true;
 }



 bool IntType::IsCasteble(Type *To) {
    switch (To->type())
    {
    case FltTy:
    {
        if(bit < 8) {
            return false;
        }
    }
        break;
    case IntTy:
    {
        if(as<IntType>(To)->getbit() < 8) {
            return false;
        }
    }
        break;
    case PointerTy:
    {
        if(bit < 8){
            return false;
        }
        PointerType *PtrTy = static_cast<PointerType *>(To);
        if(!IsCasteble(PtrTy->getTo())){
            return false;
        }
    }
        break;
    default:
        return false;
    }
    return true;
 }


bool IntType::IsCloneOf(Type *To) {
    if(this->getuId() == To->getuId()) {
        return true;
    }
    if(To->type() != IntTy){
        return false;
    }

    IntType *ITy = as<IntType>(To);
    if(bit != ITy->getbit()) {
        return false;
    }
    if(!((!ITy->isSignInt())^isSign)) {
        return false;
    }

    return true;
}

std::string IntType::toStr() noexcept {
    if(bit == 1) {
        return "bool";
    }
    std::string str = "";
    str += isSign?"i":"u";
    str += std::to_string(bit);
    return str;
}

IntType *IntType::Create(ResourceMgr &mgr, uint16_t _bit, bool _isSign) {
    return mgr.CreateTy<IntType>(_bit, _isSign);
}


 //////////////////////////////////FloatType/////////////////////////////////////////


 bool FloatType::UnaryOpMatch(lex::Tok op) {
    switch (op.getTokType())
    {
    case lex::STAR:
    case lex::AND:
    case lex::MINUS:
    {
        return true;
    }
        break;
    default:
        break;
    }
    return true;
 }
 
 bool FloatType::IsCasteble(Type *To) {
    switch (To->type())
    {
    case FltTy:
        break;
    case IntTy:
    {
        if(as<IntType>(To)->getbit() < 8){
            return false;
        }
    }
        break;
    default:
        return false;
    }
    return true;
 }



 bool FloatType::IsCloneOf(Type *To) {
    if(this->getuId() == To->getuId()) {
        return true;
    }
    if(To->type() != FltTy){
        return false;
    }
    auto type = static_cast<FloatType*>(To);
    if(bit != type->getbit()) {
        return false;
    }
    return true;
}


std::string FloatType::toStr() noexcept {
    std::string str = "f";
    str += std::to_string(bit);
    return str;
}

FloatType *FloatType::Create(ResourceMgr &mgr, uint16_t _bit) {
    return mgr.CreateTy<FloatType>(_bit);
}


 //////////////////////////////////PtrType/////////////////////////////////////////


 bool PointerType::UnaryOpMatch(lex::Tok op) {
    if(op.getTokType() != lex::STAR && op.getTokType() != lex::AND){
        return false;
    }
    return true;
 }

 PointerType *PointerType::getPtrOf(ResourceMgr &mgr, int DefCount) {
    bool _mut;
    PointerType *Ty = Create(mgr, _mut, To);
    return Ty;
}

 bool PointerType::IsCasteble(Type *otherTo) {
    switch (otherTo->type())
    {
    case IntTy:
    {
        IntType *Ty = static_cast<IntType *>(otherTo);
        if(Ty->getbit() < 8)
            return false;

        return true;
    }
        break;
    case PointerTy:
    {

        auto PT = static_cast<PointerType*>(otherTo);

        if(PT->HasMut() && !mut){
            return false;
        }

        if(!To->IsCloneOf(PT->getTo())){
            if(!To->IsCasteble(PT->getTo())){
                return false;
            }
        }
    }
        break;
    default:
        ///@todo
        return false;
    }

    return true;
 }
 

bool PointerType::IsCloneOf(Type *otherTo) {
    if(this->getuId() == otherTo->getuId()) {
        return true;
    }

    if(otherTo->type() != PointerTy && otherTo->type() != RefTy){
        return false;
    }

    if(otherTo->type() == PointerTy){
        PointerType *ptrtype = static_cast<PointerType*>(otherTo);
        if(!To->IsCloneOf(ptrtype->getTo())){
            return false;
        }

        // if((!ptrtype->HasMut() && mut) || (ptrtype->HasMut() && !mut)){
        //     return false;
        // }
        if(!(!mut ^ ptrtype->HasMut())){
            return false;
        }
    }else if(otherTo->type() == RefTy){
        RefType *refTy = static_cast<RefType *>(otherTo);
        if(refTy->getTo()->Is(PointerTy)) {
            auto ptrTy = static_cast<PointerType*>(refTy->getTo());
            if(!To->IsCloneOf(ptrTy->getTo())){
                return false;
            }

            // if((!ptrTy->HasMut() && mut) || (ptrTy->HasMut() && !mut)){
            //     return false;
            // }
            if(!(!mut ^ ptrTy->HasMut())){
                return false;
            }

        }else {
            if(!To->IsCloneOf(refTy->getTo())){
                return false;
            }
        }
        if(!(!mut ^ refTy->IsMutRef())){
            return false;
        }
        // if( (mut && !refTy->IsMutRef()) || (!mut && refTy->IsMutRef()) ) {
        //     return false;
        // }
    }
    return true;
}

// bool PointerType::IsCloneOf(Type *otherTo) {
//     if(this->getuId() == otherTo->getuId()) {
//         return true;
//     }

//     if(otherTo->type() != PointerTy){
//         return false;
//     }

//     PointerType *ptrtype = static_cast<PointerType*>(otherTo);
//     if(!To->IsCloneOf(ptrtype->getTo())){
//         return false;
//     }

//     if(!mut && ptrtype->HasMut()) {
//         return false;
//     }
//     return true;
// }

size_t PointerType::getCount() const noexcept {
    int count = 1;
    if(To->Is(PointerTy)) {
        count += as<PointerType>(To)->getCount();
    }
    return count;
}


std::string PointerType::toStr() noexcept {
    std::string str = "";
    str += "*";
    str += mut?"mut ":"const ";
    str += To->toStr();
    return str;
}

PointerType *PointerType::Create(ResourceMgr &mgr, bool _mut, Type* _To) {
    return mgr.CreateTy<PointerType>(_mut, _To);
}

 ////////////////////////////////ArrayType/////////////////////////////////////////

 bool ArrayType::UnaryOpMatch(lex::Tok op) {
    if(op.getTokType() != lex::STAR && op.getTokType() != lex::AND){
        return false;
    }
    return true;
 }

 bool ArrayType::IsCasteble(Type *To) {
    // if(To->type() != PointerTy) {
    //     return false;
    // }
    // PointerType *ptrTy = static_cast<PointerType *>(To);
    // if(ptrTy->getDefCount() != Dim.size()) {
    //     return false;
    // }
    // if(!To->IsCasteble(ptrTy->getTo())){
    //     return false;
    // }
    return false;
 }

bool ArrayType::IsCloneOf(Type *To) {
    if(this->getuId() == To->getuId()) {
        return true;
    }
    if(To->type() != ArrayTy){
        return false;
    }
    ArrayType *type = static_cast<ArrayType*>(To);
    if(Size != type->getSize()){
        return false;
    }
    if(!Ty->IsCloneOf(type->getArrType())){
        return false;
    }

    return true;
}


std::string ArrayType::toStr() noexcept {
    std::string str = "[";
    str += std::to_string(Size);
    str += "]";
    str += Ty->toStr();
    return str;
}

ArrayType *ArrayType::Create(ResourceMgr &mgr, Type *_Ty, size_t _Size) {
    return mgr.CreateTy<ArrayType>(_Ty, _Size);
}

////////////////////////////////ArrayType/////////////////////////////////////////


bool RefType::UnaryOpMatch(lex::Tok op) {
    if(op.getTokType() != lex::STAR){
        return false;
    }
    return true;
}

PointerType *RefType::getPtr(ResourceMgr &mgr) noexcept {
    return PointerType::Create(mgr, mut, To);
}

bool RefType::IsCloneOf(Type *otherTo) {
    if(this->getuId() == otherTo->getuId()) {
        return true;
    }
    if(otherTo->type() != PointerTy){
        return false;
    }
    PointerType *ToPTy = static_cast<PointerType*>(otherTo);
    // if(To->type() == PointerTy && ToPTy->getTo()->Is(PointerTy)){
    //     // if((!mut && ToPTy->HasMut()) || (mut && !ToPTy->HasMut())){
    //     //     return false;
    //     // }
    //     if(!(!mut ^ ToPTy->HasMut())){
    //         return false;
    //     }

    //     if(!To->IsCloneOf(ToPTy->getTo())){
    //         return false;
    //     }
    // }else {
        if(!To->IsCloneOf(ToPTy->getTo())){
            return false;
        }
        // if((!mut && ToPTy->HasMut()) || (mut && !ToPTy->HasMut())){
        //     return false;
        // }
        if(!(!mut ^ ToPTy->HasMut())){
            return false;
        }
    // }
    return true;
}



bool RefType::IsCasteble(Type *To) {
    return false;
}


std::string RefType::toStr() noexcept {
    std::string str = "&";
    if(mut)
        str += "mut ";
    str += To->toStr();
    return str;
}

RefType *RefType::Create(ResourceMgr &mgr, Type* _To, bool _mut) {
    return mgr.CreateTy<RefType>(_To, _mut);
}

 ////////////////////////////////ArrayType/////////////////////////////////////////

bool EnumType::UnaryOpMatch(lex::Tok op) {
    return false;
}

bool EnumType::IsCloneOf(Type *To) {
    if(this->getuId() != To->getuId()) {
        return false;
    }
    return true;
}


bool EnumType::IsCasteble(Type *To) {
    if(To->Is(IntTy) && !as<IntType>(To)->IsIntWidth(1)){
        return true;
    }
    return false;
}

std::string EnumType::toStr() noexcept {
    return "enum";
}

EnumType *EnumType::Create(ResourceMgr &mgr, IntType *_ITy) {
    return mgr.CreateTy<EnumType>(_ITy);
}


//////////////////////////////////FunctionType/////////////////////////////////////////

bool FunctionType::UnaryOpMatch(lex::Tok op) {
    if(op.getTokType() != lex::STAR && op.getTokType() != lex::AND){
        return false;
    }
    return true;
}

bool FunctionType::IsCasteble(Type *To) {
    if(!To->isIntTy()){
        return false;
    }
    IntType *ITy = static_cast<IntType *>(To);
    if(ITy->getbit() < 8) {
        return false;
    }
    return true;
}

bool FunctionType::IsCloneOf(Type *To) {
    if(this->getuId() == To->getuId()) {
        return true;
    }
    if(!To->isFunctionTy()) {
        return false;
    }
    FunctionType *FnTy = static_cast<FunctionType *>(To);
    auto &P = FnTy->getParamTypes();
    int  i = 0;
    for(auto &p: P) {
        if(!param[i]->IsCloneOf(p)){
            return false;
        }
        i++;
    }
    return true;
}


std::string FunctionType::toStr() noexcept {
    std::string str = "fn ";
    str += "(";
    for(auto &p: param){
        str += p->toStr();
    }
    str += ")";
    if(retype)
        str += retype->toStr();

    return str;
}

FunctionType *FunctionType::Create(ResourceMgr &mgr, const std::vector<Type*>&_param, Type* _ret) {
    return mgr.CreateTy<FunctionType>(_param, _ret);
}

//////////////////////////////////FunctionType/////////////////////////////////////////

bool ScopeTy::IsCloneOf(Type *To) {
    if(this->getuId() == To->getuId()) {
        return true;
    }
    return false;
}

bool ScopeTy::UnaryOpMatch(lex::Tok op) {
    return false;
}

bool ScopeTy::IsCasteble(Type *To) {
    return false;
}

ScopeTy *ScopeTy::Create(ResourceMgr &mgr, Module *_mod) {
    return mgr.CreateTy<ScopeTy>(_mod);
}

std::string ScopeTy::toStr() noexcept {
    return "";
}


//////////////////////////////////VoidType/////////////////////////////////////////

VoidType *VoidType::Create(ResourceMgr &mgr) {
    return mgr.CreateTy<VoidType>();
}

bool VoidType::UnaryOpMatch(lex::Tok op) {
    return op.getTokType() == STAR;
}

bool VoidType::IsCloneOf(Type *To) {
    return To->type() == VoidTy;
}

std::string VoidType::toStr() noexcept {
    return "()";
}

bool VoidType::IsCasteble(Type *To) {
    return true;
}
 

}