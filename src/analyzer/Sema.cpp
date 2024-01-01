#include"../../include/analyzer/Sema.hpp"
#include"../../include/analyzer/Value.hpp"
#include"../../include/Error.hpp"
#include"../../include/Module.hpp"
// #include"analyzer/TypeChecker.hpp"

namespace ast {

bool TypeChecker::Analyze(Ast *tree) {
    Module *ThisMod = tree->getStmtLoc()->getMod();
    for(auto &m: ThisMod->getSubMods()){
        if(!Analyze(m.second->getTree())) {
            return false;
        }
    }

    if(!visit(tree, &tree)){
        return false;
    }
    return true;
}

Type *ExtractTy(Type *Ty) {
    if(Ty->type() == Type::ArrayTy)
        return ExtractTy(as<ArrayType>(Ty)->getArrType());
   
    return Ty;
}

bool TypeChecker::visit(Ast *AstNode, Ast **Base, Type *Ty) {
    dumpSema("Ast");
    Type *oldType = nullptr;
    bool set = false;
    if(Ty) {
        if(TyForConst) {
            oldType = TyForConst;
        }
        TyForConst = ExtractTy(Ty);
        set = true;
    }
    isConstF = false;
    switch (AstNode->getStmtTy())
    {
    case NodeNewStmt: if(!visit(static_cast<NewStmt *>(AstNode), Base)){return false;} break;
    case NodeDelStmt: if(!visit(static_cast<DelStmt *>(AstNode), Base)){return false;} break;
    case NodeFNStm: if(!visit(static_cast<FunctionDef *>(AstNode), Base)) { return false; } break;
    case NodeFnProto: if(!visit(static_cast<FunctionProto *>(AstNode), Base)) { return false; } break;
    case NodeBlockStm: if(!visit(static_cast<BlockStmt *>(AstNode), Base)) { return false; } break;
    case NodeNumLit: if(!visit(static_cast<NumericLiteral *>(AstNode), Base)) { return false; } break;
    case NodeBoolLit: if(!visit(static_cast<BoolLiteral *>(AstNode), Base)) { return false; } break;
    case NodeFloatLit: if(!visit(static_cast<FloatLiteral *>(AstNode), Base)) { return false; } break;
    case NodeStrLit: if(!visit(static_cast<StringLiteral *>(AstNode), Base)) { return false; } break;
    case NodeNullLit: if(!visit(static_cast<NullLiteral *>(AstNode), Base)) { return false; } break;
    case NodeIdent: if(!visit(static_cast<Identifier *>(AstNode), Base)) { return false; } break;
    case NodeEnum: if(!visit(static_cast<EnumExpr *>(AstNode), Base)) { return false; } break;
    case NodeExpr: if(!visit(static_cast<Expression *>(AstNode), Base)) { return false; } break;
    case NodePrefix: if(!visit(static_cast<PrefixExpr *>(AstNode), Base)) { return false; } break;
    case NodeField: if(!visit(static_cast<FieldExpr *>(AstNode), Base)) { return false; } break;
    case NodeGroupExpr: if(!visit(static_cast<GroupedExpr *>(AstNode), Base)) { return false; } break;

    case NodePreDefTy: if(!visit(static_cast<PremitiveType *>(AstNode), Base)) { return false; } break;
    case NodeArray: if(!visit(static_cast<Array *>(AstNode), Base)) { return false; } break;
    case NodeFnTy: if(!visit(static_cast<FnType *>(AstNode), Base)) { return false; } break;
    case NodeUserDefTy: if(!visit(static_cast<UserDefinedTy *>(AstNode), Base)) { return false; } break;

    case NodeIfStm: if(!visit(static_cast<IfStmt *>(AstNode), Base)) { return false; } break;
    case NodeWhileStm: if(!visit(static_cast<WhileLoop *>(AstNode), Base)) { return false; } break;
    case NodeForStm: if(!visit(static_cast<ForLoop *>(AstNode), Base)) { return false; } break;
    case NodeVarStm: if(!visit(static_cast<VarStmt *>(AstNode), Base)) { return false; } break;
    case NodeRetStm: if(!visit(static_cast<ReturnStmt *>(AstNode), Base)) { return false; } break;
    case NodeBranchStm: if(!visit(static_cast<BranchStmt *>(AstNode), Base)) { return false; } break;
    case NodeStructStm: if(!visit(static_cast<StructStmt *>(AstNode), Base)) { return false; } break;
    case NodeImpl: if(!visit(static_cast<Method *>(AstNode), Base)) { return false; } break;
        //case NodeMatchStmt: if(!visit(static_cast< *>(AstNode), Base)) { return false; } break;
    case NodeUseStmt: if(!visit(static_cast<UseStmt *>(AstNode), Base)) { return false; } break;
    case NodeVoid: if(!visit(static_cast<Void *>(AstNode), Base)) { return false; } break;
    default:
        err::err_out(
		AstNode, "invalid statement found for type assignment: ");
        return false;
    }

    if(AstNode != *Base) {
        AstNode = *Base;
    }

    if(AstNode->IsConst() && TyForConst) {
        Type *_Ty = AstNode->getTypeInfo();
        if(_Ty->type() != TyForConst->type()){
            return true;
        }
        if(AstNode->Is(NodeNumLit) || AstNode->Is(NodeNullLit) || AstNode->Is(NodeFloatLit) || (AstNode->Is(NodeStrLit) && _Ty->Is(Type::IntTy)))
            AstNode->setType(TyForConst);
    }
    if(set) {
        TyForConst = oldType;
    }

    if(isConst && !isConstF && (AstNode->Is(NodeExpr) || AstNode->Is(NodePrefix)) && (AstNode->IsConst() || AstNode->IsTydConst())) {
        Type *Ty = AstNode->getTypeInfo();
        Ast *Var = getConstVal(AstNode, Base);
        if(!Var) {
            err::err_out(AstNode, "element is not a compile-time constant");
            return false;
        }
        Var->setType(Ty);
        if(AstNode->IsConst())
            Var->setConst();
        else if(AstNode->IsTydConst())
            Var->setTydConst();
        *Base = Var;
    }
    dumpSema2("Ast");
    return true;
}



bool TypeChecker::CheckIsInitialized(Ast *Expr, bool MustInit) {
    Ast *Decl = Expr->getDecl();
    if(!Decl || !Decl->Is(NodeVarStm)) {
        return !MustInit;
    }
    VarStmt *VarS = static_cast<VarStmt *>(Decl);
    if(VarS->IsFieldVar()) {
        return true;
    }
    return VarS->IsInitialized();
}

void TypeChecker::setInitialized(Ast *Expr) {
    Ast *Decl = Expr->getDecl();
    if(Decl && Decl->Is(NodeVarStm)) {
        as<VarStmt>(Decl)->setInitialized();
    }
}

std::string TypeChecker::mangle_name(std::string str, std::string modid, Ast *stmt) {
    if(!stmt->isMangled()){
        str = modid + "_" + str;
        stmt->setMangled();
    }
    return str;
}


bool TypeChecker::TypeCorel(Type *&Ty, Type *&To, Ast *Expr, bool Const) {
    dumpSema(__func__);

    if(Expr->Is(NodeStrLit) && Ty->Is(Type::ArrayTy ) && To->Is(Type::PointerTy)) {
        ArrayType *StrArrTy = static_cast<ArrayType *>(Ty);
        if(To->type() == Type::PointerTy){
            PointerType *ptrTy = static_cast<PointerType *>(To);

            if(ptrTy->getTo()->type() != Type::IntTy || as<IntType>(ptrTy->getTo())->getbit() != 8) {
                err::err_out(Expr, "invalid const string assignment expected type is - *i8 or [?]i8");
                return false;
            }
        }
        dumpSema2(__func__);
        return true;
    }

    if(Expr->IsConst()) {
        if(Expr->Is(NodeNullLit) && !To->Is(Type::PointerTy)) {
            goto finalcheck;
        }else if(((Ty->Is(Type::TypeID::IntTy) && as<IntType>(Ty)->getbit() == 1) && 
                (To->Is(Type::TypeID::IntTy) && as<IntType>(To)->getbit() != 1)) && 
                (!Ty->Is(Type::TypeID::FltTy) && !To->Is(Type::TypeID::FltTy))) {
            goto finalcheck;
        }

        Ty = To;
        return true;
    }
    dumpSema2(__func__);
finalcheck:
    return Ty->IsCloneOf(To);
}


} 