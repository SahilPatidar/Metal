#include<algorithm>
#include"../../include/analyzer/Resolve.hpp"
#include"../../include/parser/type.hpp"
#include"../../include/analyzer/symbol_table.hpp"
#include"../../include/Module.hpp"
#include"../../include/Error.hpp"


namespace ast{

void dumpresolve(String msg){
    std::cout<<"step :: "<<"entering in -> "<<msg<<" "<<std::endl;
}
void dumpresolve2(String msg){
    std::cout<<"step :: "<<"returning from -> "<<msg<<" "<<std::endl;
}

bool IsTy(Ast *Expr) {
    if(Expr->Is(NodeIdent)) {
        Ast *Decl = Expr->getDecl();
        if(!Decl) {
            return false;
        }
        if(!Decl->Is(NodeStructStm) && !Decl->Is(NodeEnum)) {
            return false;
        }
    }else if(!(Expr->Is(NodeVoid) || Expr->Is(NodeArray) || Expr->Is(NodePreDefTy) || (Expr->Is(NodePrefix) && as<PrefixExpr>(Expr)->IsType()) || Expr->Is(NodeFnTy))) {
        return false;
    }
    return true;
}

bool Resolve::visit(Ast *AstNode, Ast **Base, Valid Is) {
    dumpresolve("Ast");
    // ThisModule = AstNode->getStmtLoc()->getMod();
    switch(AstNode->getStmtTy())
    {
    case NodeExtern: if(!visit(static_cast<Extern *>(AstNode), Base)){return false;} break;
    case NodeFNStm: if(!visit(static_cast<FunctionDef *>(AstNode), Base)){return false;} break;
    case NodeFnProto: if(!visit(static_cast<FunctionProto *>(AstNode), Base)){return false;} break;
    case NodeBlockStm: if(!visit(static_cast<BlockStmt *>(AstNode), Base)){return false;} break;
    case NodeNewStmt: if(!visit(static_cast<NewStmt *>(AstNode), Base)){return false;} break;
    case NodeDelStmt: if(!visit(static_cast<DelStmt *>(AstNode), Base)){return false;} break;
    case NodeNumLit: if(!visit(static_cast<NumericLiteral *>(AstNode), Base)){return false;} break;
    case NodeBoolLit: if(!visit(static_cast<BoolLiteral *>(AstNode), Base)){return false;} break;
    case NodeFloatLit: if(!visit(static_cast<FloatLiteral *>(AstNode), Base)){return false;} break;
    case NodeStrLit: if(!visit(static_cast<StringLiteral *>(AstNode), Base)){return false;} break;
    case NodeNullLit: if(!visit(static_cast<NullLiteral *>(AstNode), Base)){return false;} break;
    case NodeIdent: if(!visit(static_cast<Identifier *>(AstNode), Base)){return false;} break;
    case NodeEnum: if(!visit(static_cast<EnumExpr *>(AstNode), Base)){return false;} break;
    case NodeExpr: if(!visit(static_cast<Expression *>(AstNode), Base)){return false;} break;
    case NodePrefix: if(!visit(static_cast<PrefixExpr *>(AstNode), Base)){return false;} break;
    case NodeField: if(!visit(static_cast<FieldExpr *>(AstNode), Base)){return false;} break;
    case NodeGroupExpr: if(!visit(static_cast<GroupedExpr *>(AstNode), Base)){return false;} break;

    case NodePreDefTy: if(!visit(static_cast<PremitiveType *>(AstNode), Base)){return false;} break;
    case NodeArray: if(!visit(static_cast<Array *>(AstNode), Base)){return false;} break;
    case NodeFnTy: if(!visit(static_cast<FnType *>(AstNode), Base)){return false;} break;
    case NodeUserDefTy: if(!visit(static_cast<UserDefinedTy *>(AstNode), Base)){return false;} break;

    case NodeIfStm: if(!visit(static_cast<IfStmt *>(AstNode), Base)){return false;} break;
    case NodeWhileStm: if(!visit(static_cast<WhileLoop *>(AstNode), Base)){return false;} break;
    case NodeForStm: if(!visit(static_cast<ForLoop *>(AstNode), Base)){return false;} break;
    case NodeVarStm: if(!visit(static_cast<VarStmt *>(AstNode), Base)){return false;} break;
    case NodeRetStm: if(!visit(static_cast<ReturnStmt *>(AstNode), Base)){return false;} break;
    case NodeBranchStm: if(!visit(static_cast<BranchStmt *>(AstNode), Base)){return false;} break;
    case NodeStructStm: if(!visit(static_cast<StructStmt *>(AstNode), Base)){return false;} break;
    case NodeImpl: if(!visit(static_cast<Method *>(AstNode), Base)){ return false; } break;
    case NodeUseStmt: if(!visit(static_cast<UseStmt *>(AstNode), Base)){return false;} break;
    case NodeVoid: if(!visit(static_cast<Void *>(AstNode), Base)){return false;} break;
    default:
        return false;
        break;
    }
    if(AstNode != *Base) {
        AstNode = *Base;
    }

    if(IsTy(AstNode)) {
        if(Is == Val) {
            err::err_out(AstNode, "invalid value");
            return false;
        }
        return true;
    }
    if((Is == Val) && AstNode->Is(NodeIdent) && !AstNode->getDecl()) {
        err::err_out(AstNode, "invalid value");
        return false;
    }
    if(Is == Ty) {
        err::err_out(AstNode, "invalid type");
        return false;
    }
    dumpresolve2("Ast");
    return true;
}


bool Resolve::visit(BranchStmt *AstNode, Ast** Base) {
    dumpresolve("BranchStmt");
    dumpresolve2("BranchStmt");
    return true;
}
bool Resolve::visit(Void *AstNode, Ast** Base) {
    dumpresolve("Void");
    dumpresolve2("Void");
    return true;
}

bool Resolve::visit(NewStmt *AstNode, Ast** Base) {
    dumpresolve("NewStmt");
    Ast *&Size = AstNode->getSize();
    Ast *&Ty = AstNode->getTy();
    if(!visit(Ty, &Ty, Valid::Ty)) {
        return false;
    }
    if(!visit(Size, &Size)) {
        return false;
    }
    dumpresolve2("NewStmt");
    return true;
}

bool Resolve::visit(DelStmt *AstNode, Ast** Base) {
    dumpresolve("DelStmt");
    Ast *&VPtr = AstNode->getPtr();
    if(!visit(VPtr, &VPtr)) {
        return false;
    }
    dumpresolve2("DelStmt");
    return true;
}


Ast *Resolve::getModItem(Module *mod, String ID) {
    Vec<Ast *> &Stmts = static_cast<BlockStmt *>(mod->getAst())->getStmts();
    for(Ast *&S :Stmts) {
        String stmtId = "";
        switch(S->getStmtTy()) {
        case NodeStructStm: stmtId = static_cast<StructStmt *>(S)->getName().getStr(); break;
        case NodeFNStm: stmtId = static_cast<FunctionDef *>(S)->getFnProto()->getFuncName().getStr(); break;
        case NodeFnProto: stmtId = static_cast<FunctionProto *>(S)->getFuncName().getStr(); break;
        case NodeVarStm: stmtId = static_cast<VarStmt *>(S)->getVar().getStr(); break;
        case NodeEnum: stmtId = static_cast<EnumExpr *>(S)->getName().getStr(); break;
        case NodeExtern: stmtId = static_cast<Extern *>(S)->getID().getStr(); break;
        default:
            break;
        } 
        if(stmtId.empty()){
            continue;
        }   
        if(ID == stmtId){
            if(S->getStmtTy() == NodeExtern) {
                if(!visit(S, &S)) {
                    return nullptr;
                }
            }
            return S;
        }
        // modctx->insertModItem(stmtId, &S);
    }
    return nullptr;
}

bool Resolve::visit(Identifier *AstNode, Ast **Base) {
    dumpresolve("Identifier");
    String Id = AstNode->getLexeme().getStr();
    const StmtLoc *Loc = AstNode->getStmtLoc();
    bool found = false;
    if(STable.Has(Id)){
        Ast *decl = STable.getInfo(Id);
        AstNode->setDecl(decl);
        found = true;
    }else if(ThisModule->HasStmt(Id)) {
        Ast *N = getModItem(ThisModule, Id);
        AstNode->setDecl(N);
        found = true;
    }else if(Mods.find(Id) != Mods.end()) {
        *Base = Identifier::Create(mgr, mgr.getLoc(Mods[Id], Loc->getLine(), Loc->getCol()), AstNode->getLexeme());
        found = true;
    }else {
        Module *SMod = RootModule->getSubMod(Id);
        Ast *ModItem = getModItem(RootModule, Id);
        if(!SMod && !ModItem) {
            err::err_out(AstNode, "unable to resolve\n\t\t"
                                   "no `" ,  Id , "` in this scope");

            return false;
        }
        if(SMod) {
            *Base = Identifier::Create(mgr, mgr.getLoc(SMod, Loc->getLine(), Loc->getCol()), AstNode->getLexeme());
        }else if(ModItem) {
            AstNode->setDecl(ModItem);
        }
        found = true;
    }

    dumpresolve2("Identifier");
    return found;
}



bool Resolve::visit(UserDefinedTy *AstNode, Ast **Base){
    dumpresolve("UserDefinedTy");
    if(!visit(AstNode->getExpr(), &AstNode->getExpr())){
        err::err_out(AstNode, "unable to resolve expression ");
        return false;
    }
    dumpresolve2("UserDefinedTy");
    return true;
}

bool Resolve::visit(PremitiveType  *AstNode, Ast **Base) {
    dumpresolve("PremitiveType");
    dumpresolve2("PremitiveType");
    return true;
}

bool Resolve::visit(FnType  *AstNode, Ast **Base) {
    dumpresolve("FnType");
    Vec<Type*>pTy;
    if(!AstNode->getParamType().empty()) {
        for(auto &P :AstNode->getParamType()) {
            if(!visit(P, &P, Valid::Ty)){
                err::err_out(P, "unable to resolve type of parameter \n" , P->toString());
                return false;
            }
        }
    }
    Ast *&Ret = AstNode->getRetType();
    if(Ret&&!visit(Ret, &Ret)){
        err::err_out(Ret, "unable to resolve return type\n" , Ret->toString() , "is not in scope");
        return false;
    }
    dumpresolve2("FnType");
    return true;
}


bool Resolve::visit(StructStmt *AstNode, Ast **Base) {
    dumpresolve("StructStmt");
    String name = AstNode->getName().getStr();

    if(STable.Has(name, STable.HasFunc())) {
        err::err_out(AstNode, "the name `", name , "` is defined multiple times");
        return false;
    }


    STable.addInfo(name, AstNode, !STable.HasFunc());
    STable.Push_Func();
    STable.addInfo("Self", AstNode, false);
    Vec<VarStmt *>&vars = AstNode->getfield();
    for(size_t i = 0, siz = vars.size(); i < siz; i++) {
        if(!visit(vars[i]->getType(), &vars[i]->getType(), Valid::Ty)){
            err::err_out(vars[i], "failed to determined type of " , vars[i]->getVar().getStr());
            return false;
        }
    }
    STable.Pop_Func();
    dumpresolve2("StructStmt");
    return true;
}


bool Resolve::visit(EnumExpr *AstNode, Ast **Base) {
    dumpresolve("EnumExpr");
    String name = AstNode->getName().getStr();
    if(STable.Has(name)) {
        err::err_out(AstNode, "the name `", name , "` is defined multiple times");
        return false;
    }
    int64_t Eval = 0;
    Vec<VarStmt *>&Vals = AstNode->getEVals();
    STable.Push_Func();
    for(auto &V :Vals) {
        String EName = V->getVar().getStr();
        Ast *&val = V->getVal();
        
        if(STable.Has(EName)) {
            err::err_out(V, "redeclaration of `" , EName , "` enum element");
            return false;
        }

        if(val) {
            if(!visit(val, &val)) {
                err::err_out(AstNode, "failed to resolve val of " ,EName);
                return false;
            }
        }
        STable.addInfo(EName, nullptr);
    }
    STable.Pop_Func();

    STable.addInfo(AstNode->getName().getStr(), AstNode, !STable.HasFunc());
    dumpresolve2("EnumExpr");
    return true;
}


bool Resolve::visit(FunctionProto *FnProto, Ast **Base) {
    dumpresolve("FunctionDef");
    String name = FnProto->getFuncName().getStr();
    if(STable.Has(name)){
        err::err_out(FnProto, "the name `", name , "` is defined multiple times");
        return false;
    }

    STable.Push_Func();

    Ast *&Ret = FnProto->getResultType();
    if(Ret && !visit(Ret, &Ret, Valid::Ty)) {
        return false;
    }

    // std::map<String, Type*>ElementType;
    Vec<Type*>ElementType;
    if(!FnProto->getParameter().empty()){
        Vec<VarStmt*>&param = FnProto->getParameter();
        for(size_t i = 0, size = param.size(); i < size; i++) {
            Ast *&PVarTy = param[i]->getType();
            String ParamName = param[i]->getVar().getStr();

            if(!PVarTy) {
                err::err_out(param[i], "invalid function expression" , ParamName);
                return false;
            }

            if(!visit(PVarTy, &PVarTy, Valid::Ty)){
                return false;
            }

            if(STable.Has(ParamName, true)){
                err::err_out(param[i], "redefinition of parameter" , ParamName);
                return false;
            }

            STable.addInfo(ParamName, param[i], false);
        }
    }
    STable.addInfo(FnProto->getFuncName().getStr(), FnProto, true);
    STable.Pop_Func();
    dumpresolve2("FunctionDef");
    return true;
}

bool Resolve::visit(FunctionDef *FnStmt, Ast **Base) {
    dumpresolve("FunctionDef");
    FunctionProto *FnProto = FnStmt->getFnProto();
    String name = FnProto->getFuncName().getStr();
    if(STable.Has(name, STable.HasFunc())){
        err::err_out(FnProto, "the name `", name , "` is defined multiple times");
        return false;
    }

    STable.Push_Func();

    Ast *&Ret = FnProto->getResultType();
    if(Ret && !visit(Ret, &Ret, Valid::Ty)) {
        return false;
    }

    // std::map<String, Type*>ElementType;
    Vec<Type*>ElementType;
    if(!FnProto->getParameter().empty()){
        Vec<VarStmt*>&param = FnProto->getParameter();
        for(size_t i = 0, size = param.size(); i < size; i++) {
            Ast *&PVarTy = param[i]->getType();
            String ParamName = param[i]->getVar().getStr();

            if(!PVarTy) {
                err::err_out(param[i], "invalid function expression" , ParamName);
                return false;
            }

            if(!visit(PVarTy, &PVarTy, Valid::Ty)){
                return false;
            }

            if(STable.Has(ParamName, true)){
                err::err_out(param[i], "redefinition of parameter" , ParamName);
                return false;
            }

            STable.addInfo(ParamName, param[i], false);
        }
    }
    

    STable.addInfo(FnProto->getFuncName().getStr(), FnStmt, !(FnProto->IsMemberFunc() || FnProto->IsAssociateFunc()));


    BlockStmt *Blk = FnStmt->getFuncBlock();
    Func = FnStmt;
    if(!visit(Blk, asAst(&Blk))){
        err::err_out(Blk, "failed due to previous error");
        return false;
    }
    if(Ret && (Blk->getStmts().empty() || (!Blk->getStmts().empty() && !Blk->getStmts().back()->Is(NodeRetStm)))) {
        err::err_out(Ret, "expected return because of return type");
        return false;
    }
    Func = nullptr;
    STable.Pop_Func();
    dumpresolve2("FunctionDef");
    return true;
}


bool Resolve::visit(Array  *AstNode, Ast **Base) {
    dumpresolve("Array");
    Ast *&ArrTy = AstNode->getArrayTy();
    if(!visit(ArrTy, &ArrTy, Valid::Ty)){
        err::err_out(ArrTy, "failed determind array type");
        return false;
    }

    Ast *&ArrSiz = AstNode->getArraySize();

    if(!visit(ArrSiz, &ArrSiz)){
        err::err_out(ArrSiz, "unable to resolve size of array");
        return false;
    }

    dumpresolve2("Array");
    return true;
}

bool Resolve::visit(PrefixExpr  *AstNode, Ast **Base) {
    dumpresolve("PrefixExpr");
    Ast *&base = AstNode->getBase();
    if(!visit(base, &base, AstNode->IsType()?Valid::Ty:Valid::Val)){
        err::err_out(base, "unable to resolve type");
        return false;
    }
    dumpresolve2("PrefixExpr");
    return true;
}


bool Resolve::visit(Method *AstNode, Ast **Base) {
    dumpresolve("Method");
    Ast *&MTy = AstNode->getName();
    if(!visit(MTy, &MTy, Valid::Ty)){
        err::err_out(MTy, "unable to resolve interface type" , MTy->toString());
        return false;
    }

    static_cast<StructStmt *>(MTy->getDecl())->setImpl(AstNode);

    STable.Push_Func();
    Vec<Ast*> &impls = AstNode->getImpl();
    STable.addInfo("Self", MTy->getDecl(), false);
    
    for(size_t i = 0, siz = impls.size(); i < siz; i++) {
        Type *fnty = nullptr;
        FunctionDef *FnStmt = static_cast<FunctionDef *>(impls[i]);
        FunctionProto *FnProto = FnStmt->getFnProto();
        if(STable.Has(FnProto->getFuncName().getStr(), true)) {
            err::err_out(FnProto, "redefination of function name ", FnProto->getFuncName().getStr());
            return false;
        }

        Vec<VarStmt*> &args = FnProto->getParameter();

        if(!args.empty() && args[0]->getVar().getTokTy() == SELF) {
            Ast *Ty = nullptr;
            if(args[0]->getType())
                Ty = args[0]->getType();
            else 
                Ty = AstNode->getName();

            const StmtLoc *loc = args[0]->getStmtLoc();
            VarStmt *P = VarStmt::Create(mgr, loc,  Lexeme(loc, "self", SELF), PrefixExpr::Create(mgr, args[0]->getStmtLoc(), Tok(STAR), Ty, args[0]->HasMut(), true), nullptr, args[0]->HasMut()?_MUT:0);
            args.erase(args.begin());
            args.insert(args.begin(), P);
            FnProto->setMemberFunc();
        }else
            FnProto->setAssociateFunc();

        if(!visit(impls[i], &impls[i])){
            err::err_out(impls[i], "failed to resolve method");
            return false;
        }
    }

    STable.Pop_Func();
    dumpresolve2("Method");
    return true;
}

bool Resolve::resolve(Ast **AstNode) {
    dumpresolve("resolve");
    ThisModule = (*AstNode)->getStmtLoc()->getMod();
    const std::map<String, Module*> &submods = ThisModule->getSubMods();
    for(auto &m : submods) {
        std::cout<<m.first<<std::endl;
        Mods.insert({m.first, m.second}); 
    }

    if(!visit(*AstNode, AstNode)) {
        return false;
    }

    if(!STable.Has("main") && ThisModule == RootModule) {
        err::err_out(*AstNode, "the `main` function must be defined"); 
        return false;
    }
    dumpresolve2("resolve");
    return true;
}


bool Resolve::visit(BlockStmt *AstNode, Ast **Base) {
    dumpresolve("BlockStmt");
    STable.Push_Stack();
    Vec<Ast*> &stmts = AstNode->getStmts();

    for(size_t i = 0, siz = stmts.size(); i < siz; i++) {
        if(!visit(stmts[i], &stmts[i])){
            return false;
        }

        if(stmts[i]->getStmtTy() == NodeBlockStm) {
			BlockStmt *blk		 = static_cast<BlockStmt*>(stmts[i]);
			Vec<Ast*>&blkstmts = blk->getStmts();
			stmts.erase(stmts.begin() + i);
			stmts.insert(stmts.begin() + i, blkstmts.begin(), blkstmts.end());
			i += blkstmts.size();
			--i;
		}
    
    }
    STable.Pop_Stack();

    dumpresolve2("BlockStmt");
    return true;
}


bool Resolve::visit(UseStmt *AstNode, Ast **Base){
    dumpresolve("UseStmt");
    Ast *&Path = AstNode->getPath();
    Ast *IDN = nullptr;
    if(Path->Is(NodeExpr) && as<Expression>(Path)->isCastExpr()) {
        Expression *Expr = as<Expression>(Path);
        Path = Expr->getLhs();
        IDN = Expr->getRhs();
        if(Mods.find(IDN->toString()) != Mods.end()) {
            err::err_out(IDN, "name'd ", IDN->toString()," expression already exist"); 
            return false;
        }
    }

    if(!IDN && Path->getStmtTy() == NodeIdent) {
        if(STable.Has(Path->toString())) {
            err::err_out(Path,  Path->toString() , " name'd expression already exist"); 
            return false;
        }
    }


    if(!visit(Path, &Path)) {
        return false;
    }

    if(!Path->getDecl() && Path->getStmtLoc()->getMod() != ThisModule) {
        err::err_out(Path, "invalid Path expression");
        return false;
    }


    if(!IDN) {
        IDN = Path;
    }

    if( ( Mods.find(IDN->toString()) != Mods.end() ) || 
                ( !IDN && STable.Has(Path->toString()) ) ) {
        err::err_out(IDN, "name'd `", Path->toString() , "` path expression already exist");
        return false;
    }

    STable.addInfo(IDN->toString(), Path->getDecl(), true);
    dumpresolve2("UseStmt");
    return true;
}



bool Resolve::visit(FloatLiteral  *AstNode, Ast **Base ) {
    dumpresolve("FloatLiteral");

    dumpresolve2("FloatLiteral");
    return true;
}

bool Resolve::visit(BoolLiteral  *AstNode, Ast **Base ) {
    dumpresolve("BoolLiteral");

    dumpresolve2("BoolLiteral");
    return true;
}

bool Resolve::visit(NumericLiteral  *AstNode, Ast **Base ) {
    dumpresolve("NumericLiteral");
    dumpresolve2("NumericLiteral");
    return true;
}

bool Resolve::visit(NullLiteral  *AstNode, Ast **Base ) {
    dumpresolve("NullLiteral");
    dumpresolve2("NullLiteral");
    return true;
}

bool Resolve::visit(StringLiteral  *AstNode, Ast **Base ) {
    dumpresolve("StringLiteral");
    dumpresolve2("StringLiteral");
    return true;
}



bool Resolve::visit(ReturnStmt *AstNode, Ast **Base) {
    dumpresolve("ReturnStmt");
    Ast *&Ret = AstNode->getRetValue();
    AstNode->setFnBlk(Func->getFuncBlock());
    if(Ret&&!visit(Ret, &Ret, Valid::Val)){
        err::err_out(AstNode, "unable to resolve return expression due previous error");
        return false;
    }
    dumpresolve2("ReturnStmt");
    return true;
}



bool Resolve::visit(FieldExpr  *AstNode, Ast **Base) {
    dumpresolve("FieldExpr");
    if(AstNode->getArgs().empty()){
        err::err_out(AstNode, "unable to resolve");
        return false;
    }
    for(auto &val: AstNode->getArgs()){
        if(!visit(val, &val, Valid::Val)){
            err::err_out(AstNode, "unable to resolve");
            return false;
        }
    }
    dumpresolve2("FieldExpr");
    return true;
}


bool Resolve::visit(VarStmt *AstNode, Ast **Base) {
    dumpresolve("VarStmt");
    String varn = AstNode->getVar().getStr();

    if(STable.Has(varn, STable.HasFunc())){
        err::err_out(AstNode, "the name `", varn , "` is defined multiple times");
        return false;
    }
    Ast *&Ty = AstNode->getType();
    Ast *&Val = AstNode->getVal();
    if(AstNode->IsGlobVar() && !Ty) {
        err::err_out(AstNode, "global variable must have type declared");
        return false;
    }
     if(Ty&&!visit(Ty, &Ty, Valid::Ty)){
        err::err_out(AstNode, "failed to resolve expression due to previous error");
        return false;
    }
    if(Val&&!visit(Val, &Val, Valid::Val)){
        err::err_out(AstNode, "failed to resolve expression due to previous error");
        return false;
    }

    STable.addInfo(varn, AstNode, !STable.HasFunc());

dumpresolve2("VarStmt");
    return true;
}



bool Resolve::visit(GroupedExpr  *AstNode, Ast **Base) {
    dumpresolve("GroupedExpr");
    if(!visit(AstNode->getExpression(), &AstNode->getExpression())){
        err::err_out(AstNode, "unable to resolve");
        return false;
    }
    dumpresolve2("GroupedExpr");
    return true;
}


bool Resolve::visit(Expression *AstNode, Ast **Base) {
    dumpresolve("Expression");
    Ast *&Lhs = AstNode->getLhs();
    Ast *&Rhs = AstNode->getRhs();

    if(!AstNode->isExtCallExpr() && !visit(Lhs, &Lhs)){
        return false;
    }
    switch (AstNode->getExprID())
    {
    case Expression::KMemExpr: break;
    case Expression::KBinaryExpr:
    case Expression::KIndexExpr:
    {
        if(!visit(Rhs, &Rhs, Valid::Val)){
            err::err_out(AstNode, "failed to due to previous error");
            return false;
        }
    }
        break;
    case Expression::KAsExpr:
    case Expression::KIsExpr:
    {
        if(!visit(Rhs, &Rhs, Valid::Ty)){
            err::err_out(AstNode, "failed to due to previous error");
            return false;
        }
    }
        break;
    case Expression::KPathExpr:
    {
        Module *Mod = Lhs->getStmtLoc()->getMod();
        const StmtLoc *Loc = Rhs->getStmtLoc();
        if(Mod->getModId() != Loc->getMod()->getModId()) {
            String Id = Rhs->toString();
            Module *SMod = Mod->getSubMod(Id);
            Ast *Mitem = getModItem(Mod, Id);

            if(!SMod && !Mitem) {
                err::err_out(Rhs, "unable to resolve\n\t" ,
                                    Id , " is not in scope");
                return false;
            }

            if(SMod) {
                Rhs = Identifier::Create(mgr, 
                                        mgr.getLoc(SMod, Loc->getLine(), Loc->getCol()), 
                                        static_cast<Identifier *>(Rhs)->getLexeme()
                                        );
            }else {
                Rhs->setDecl(Mitem);
            }
            *Base = Rhs;
        }
    }
    break;
    case Expression::KCallExpr:
    {
        if(Rhs->getStmtTy() != NodeField){
            err::err_out(AstNode, "unable to resolve");
            return false;
        }
        FieldExpr *field = static_cast<FieldExpr*>(Rhs);
        Vec<Ast*>&Vals = field->getArgs();
        if(!Vals.empty()){
            for(auto &V :Vals) {
                if(!visit(V, &V, Valid::Val)){
                    return false;
                }
            }
        }
    }
    break;
    case Expression::KExtCallExpr:
    {
        if(Rhs->getStmtTy() != NodeField){
            err::err_out(AstNode, "unable to resolve");
            return false;
        }
        FieldExpr *field = static_cast<FieldExpr*>(Rhs);
        Vec<Ast*>&Vals = field->getArgs();
        if(!Vals.empty()){
            for(auto &V :Vals) {
                if(!visit(V, &V)){
                    return false;
                }
            }
        }
    }
    break;
    case Expression::KStructExpr:
    {
        STable.Push_Stack();
        FieldExpr *field = static_cast<FieldExpr*>(Rhs);
        Vec<Ast*>&Vals = field->getArgs();
        if(!Vals.empty()){
            for(auto &V: Vals) {
                Ast *&Val = static_cast<VarStmt*>(V)->getVal();
                if(!visit(Val, &Val, Valid::Val)) {
                    return false;
                }
            }
        }
        STable.Pop_Stack();
    }
    break;
    default:
        break;
    }
    dumpresolve2("Expression");
    return true;
} 



bool Resolve::visit(ForLoop  *AstNode, Ast **Base) {
    dumpresolve("ForLoop");
    Ast *&Var = AstNode->getVar();
    Ast *&Cond = AstNode->getCond();
    Ast *&Incr = AstNode->getIncr();
    BlockStmt *&Blk = AstNode->getBlock();
    STable.Push_Stack();
    if(Var&&!visit(Var, &Var)){
        err::err_out(AstNode, "failed to resolve expression due to previous error");
        return false;
    }

    if(Cond&&!visit(Cond, &Cond)){
        err::err_out(AstNode, "failed to resolve expression due to previous error");
        return false;
    }

    if(Incr&&!visit(Incr, &Incr)){
        err::err_out(AstNode, "failed to resolve expression due to previous error");
        return false;
    }

    if(Blk&&!visit(Blk, asAst(&Blk))){
        err::err_out(AstNode, "failed to resolve block due to previous error");
        return false;
    }
    STable.Pop_Stack();
    dumpresolve2("ForLoop");
    return true;
}

bool Resolve::visit(WhileLoop  *AstNode, Ast **Base) {
    dumpresolve("WhileLoop");
    Ast *&Cond = AstNode->getCond();
    BlockStmt *&Blk = AstNode->getBlock();
    if(Cond&&!visit(Cond, &Cond)){
        err::err_out(AstNode, "failed to resolve expression due to previous error");
        return false;
    }
    
    STable.Push_Stack();
    if(Blk&&!visit(Blk, asAst(&Blk))){
        err::err_out(AstNode, "failed to resolve block due to previous error");
        return false;
    }
    STable.Pop_Stack();
    dumpresolve2("WhileLoop");
    return true;
}

bool Resolve::visit(IfStmt  *AstNode, Ast **Base) {
    dumpresolve("IfStmt");
    Ast *&Cond = AstNode->getCondV();
    BlockStmt *&Blk = AstNode->getIfBlock();
    Ast *&ElBlk = AstNode->getElBlock();
    if(Cond&&!visit(Cond, &Cond)){
        err::err_out(Cond, "failed to resolve expression due to previous error");
        return false;
    }

    STable.Push_Stack();

    if(Blk&&!visit(Blk, asAst(&Blk))){
        err::err_out(Blk, "failed to resolve if-block due to previous error");
        return false;
    }

    if(ElBlk&&!visit(ElBlk, &ElBlk)){
        err::err_out(AstNode, "failed to resolve elif-block due to previous error");
        return false;
    }

    STable.Pop_Stack();
    dumpresolve2("IfStmt");
    return true;
}

bool Resolve::visit(Extern *AstNode, Ast **Base) {
    Lexeme &L = AstNode->getID();
    String Id = L.getStr();
    if(STable.Has(Id)) {
        err::err_out(L.getLoc(), L.getStr() , " is already exist in scope");
        return false;
    }

    if(Id == "malloc") {
        ExtHandler.Extern_malloc(mgr, L.getLoc(), Base);
    }else if(Id == "memccpy") {
        ExtHandler.Extern_memccpy(mgr, L.getLoc(), Base);

    }else if(Id == "memset") {
        ExtHandler.Extern_memset(mgr, L.getLoc(), Base);

    }else if(Id == "memcpy") {
        ExtHandler.Extern_memcpy(mgr, L.getLoc(), Base);

    }else if(Id == "free") {
        ExtHandler.Extern_free(mgr, L.getLoc(), Base);

    }else if(Id == "realloc") {
        ExtHandler.Extern_realloc(mgr, L.getLoc(), Base);

    }else if(Id == "calloc") {
        ExtHandler.Extern_calloc(mgr, L.getLoc(), Base);

    }else if(Id == "memcmp") {
        ExtHandler.Extern_memcmp(mgr, L.getLoc(), Base);

    }else if(Id == "__sbuf") {
        ExtHandler.Extern___sbuf(mgr, L.getLoc(), Base);

    }else if(Id == "FILE") {
        ExtHandler.Extern_FILE(mgr, L.getLoc(), Base);

    }else if(Id == "__sFILEX") {
        ExtHandler.Extern___sFILEX(mgr, L.getLoc(), Base);

    }else if(Id == "fclose") {
        ExtHandler.Extern_fopen(mgr, L.getLoc(), Base);
        
    }else if(Id == "creat") {
        ExtHandler.Extern_creat(mgr, L.getLoc(), Base);
        
    }else if(Id == "fopen") {
        ExtHandler.Extern_fclose(mgr, L.getLoc(), Base);

    }else if(Id == "open") {
        ExtHandler.Extern_open(mgr, L.getLoc(), Base);

    }else if(Id == "close") {
        ExtHandler.Extern_close(mgr, L.getLoc(), Base);

    }else if(Id == "write") {
        ExtHandler.Extern_write(mgr, L.getLoc(), Base);

    }else if(Id == "read") {
        ExtHandler.Extern_read(mgr, L.getLoc(), Base);

    }else if(Id == "printf") {
        ExtHandler.Extern_printf(mgr, L.getLoc(), Base);

    }else if(Id == "scanf") {
        ExtHandler.Extern_scanf(mgr, L.getLoc(), Base);

    }else if(Id == "strlen") {
        ExtHandler.Extern_strlen(mgr, L.getLoc(), Base);

    }else if(Id == "exit") {
        ExtHandler.Extern_exit(mgr, L.getLoc(), Base);

    }else {
        err::err_out(L.getLoc(), "there's no `" , Id , "` named extern struct or function found");
        return false;
    }
    if(AstNode->getStmtLoc()->getMod()->getModId() == ThisModule->getModId()) {
        if(!visit(*Base, Base)) {
            return false;
        }
    }

    (*Base)->setMangled();
    return true;
}


}

 