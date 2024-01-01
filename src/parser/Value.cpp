#include"../../include/analyzer/Value.hpp"

namespace ast{

///////////////////////////////////////// IntVal ///////////////////////////////////////////////


bool IntVal::updateValue(VALUE *_val) {
    
    if(!_val->Is(VALUE::VInt)&&!_val->Is(VALUE::VFlt)) {
        return false;
    }

    int64_t v;
    if(_val->Is(VALUE::VInt)) {
        v = static_cast<IntVal *>(_val)->getVal();
    }
    if(_val->Is(VALUE::VFlt)) {
        v = static_cast<FltVal *>(_val)->getVal();
    }
    if(!v){
        return false;
    }
    val = v;
    return true;
}

VALUE *IntVal::clone(ResourceMgr &mgr) noexcept {
    return Create(mgr,val,vty);
}


IntVal *IntVal::Create(ResourceMgr &mgr, int64_t _val,  ValID vty) {
    return mgr.CreateVal<IntVal>(_val, vty);
}




///////////////////////////////////////// FltVal ///////////////////////////////////////////////

bool FltVal::updateValue(VALUE *_val) {
    
    if(!_val->Is(VALUE::VInt)&&!_val->Is(VALUE::VFlt)) {
        return false;
    }

    int64_t v;
    if(_val->Is(VALUE::VInt)) {
        v = static_cast<IntVal *>(_val)->getVal();
    }
    if(_val->Is(VALUE::VFlt)) {
        v = static_cast<FltVal *>(_val)->getVal();
    }
    if(!v){
        ///@todo
    }
    val = v;
    return true;
}



VALUE *FltVal::clone(ResourceMgr &mgr) noexcept {
    return Create(mgr,val);
}

FltVal *FltVal::Create(ResourceMgr &mgr, double _val)  {
    return mgr.CreateVal<FltVal>(_val);
}

///////////////////////////////////////// StructVal ///////////////////////////////////////////////


bool StructVal::updateValue(VALUE *_val) {
    if(!_val->Is(VStruct)){
        return false;
    }
    auto &Field = static_cast<StructVal *>(_val)->getVals();
    for(auto F :Field) {
        if(vals.find(F.first) == vals.end()) {
            return false;
        }
        vals[F.first] = F.second;
    }
    return true;
}


VALUE *StructVal::clone(ResourceMgr &mgr) noexcept {
    std::map<std::string, VALUE *>stvals;
    for(auto &val: vals){
        stvals.insert({val.first, val.second->clone(mgr)});
    }
    return Create(mgr,stvals);
}


StructVal *StructVal::Create(ResourceMgr &mgr, const std::map<std::string, VALUE*> &_vals) {
    return mgr.CreateVal<StructVal>(_vals);
}

///////////////////////////////////////// IntVal ///////////////////////////////////////////////

bool ArrayVal::updateValue(VALUE *_val) {
    if(!_val->Is(VArray)){
        return false;
    }
    auto &Field = static_cast<ArrayVal *>(_val)->getVals();
    int i = 0;
    for(auto F :Field) {
        vals[i] = F;
        i++;
    }
    return true;
}


VALUE *ArrayVal::clone(ResourceMgr &mgr) noexcept {
    std::vector<VALUE *>ArrVal;
    for(auto &val: vals){
        ArrVal.push_back(val->clone(mgr));
    }
    return Create(mgr, ArrVal);
}

ArrayVal *ArrayVal::Create(ResourceMgr &mgr, const std::vector<VALUE*>&_vals) {
    return mgr.CreateVal<ArrayVal>(_vals);
}

}