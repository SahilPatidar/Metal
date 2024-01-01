// #pragma once
#include "../../include/analyzer/ValCheck.hpp"
#include"../../include/parser/type.hpp"
#include "../../include/analyzer/Value.hpp"
#define MAX_LOOP_LIMIT 100
namespace ast
{

    bool ValChecker::visit(Ast *AstNode, Ast **Base)
    {
        switch (AstNode->getStmtTy())
        {
        case NodeFNStm:
            visit(static_cast<FunctionDef *>(AstNode), Base);
            break;
        case NodeBlockStm:
            visit(static_cast<BlockStmt *>(AstNode), Base);
            break;
        case NodeNumLit:
            visit(static_cast<NumericLiteral *>(AstNode), Base);
            break;
        case NodeBoolLit:
            visit(static_cast<BoolLiteral *>(AstNode), Base);
            break;
        case NodeFloatLit:
            visit(static_cast<FloatLiteral *>(AstNode), Base);
            break;
        case NodeStrLit:
            visit(static_cast<StringLiteral *>(AstNode), Base);
            break;
        case NodeNullLit:
            visit(static_cast<NullLiteral *>(AstNode), Base);
            break;
        case NodeIdent:
            visit(static_cast<Identifier *>(AstNode), Base);
            break;
        case NodeEnum:
            visit(static_cast<EnumExpr *>(AstNode), Base);
            break;
        case NodeExpr:
            visit(static_cast<Expression *>(AstNode), Base);
            break;
        case NodePrefix:
            visit(static_cast<PrefixExpr *>(AstNode), Base);
            break;
        case NodeField:
            visit(static_cast<FieldExpr *>(AstNode), Base);
            break;
        case NodeGroupExpr:
            visit(static_cast<GroupedExpr *>(AstNode), Base);
            break;

        case NodePreDefTy:
            visit(static_cast<PremitiveType *>(AstNode), Base);
            break;
        case NodeArray:
            visit(static_cast<Array *>(AstNode), Base);
            break;
        case NodeFnTy:
            visit(static_cast<FnType *>(AstNode), Base);
            break;
        case NodeUserDefTy:
            visit(static_cast<UserDefinedTy *>(AstNode), Base);
            break;

        case NodeIfStm:
            visit(static_cast<IfStmt *>(AstNode), Base);
            break;
        case NodeWhileStm:
            visit(static_cast<WhileLoop *>(AstNode), Base);
            break;
        case NodeForStm:
            visit(static_cast<ForLoop *>(AstNode), Base);
            break;
        case NodeVarStm:
            visit(static_cast<VarStmt *>(AstNode), Base);
            break;
        case NodeRetStm:
            visit(static_cast<ReturnStmt *>(AstNode), Base);
            break;
        case NodeBranchStm:
            visit(static_cast<BranchStmt *>(AstNode), Base);
            break;
        case NodeStructStm:
            visit(static_cast<StructStmt *>(AstNode), Base);
            break;
        case NodeImpl:
            visit(static_cast<Method *>(AstNode), Base);
            break;
            // case NodeMatchStmt: visit(static_cast< *>(AstNode), Base); break;
        case NodeUseStmt:
            visit(static_cast<UseStmt *>(AstNode), Base);
            break;
        default:
            return false;
            break;
        }
        return true;
    }

    bool ValChecker::visit(Identifier *AstNode, Ast **Base)
    {
        auto val = AstNode->getValueInfo();
        if (!val)
        {
            auto declval = AstNode->getDecl()->getValueInfo();
            if (!declval)
            {
                ///@todo
            }

            AstNode->setUpdateValue(declval);
        }
        return true;
    }

    bool ValChecker::visit(FloatLiteral *AstNode, Ast **Base)
    {
        if (!AstNode->getValueInfo())
        {
            AstNode->setValue(FltVal::Create(mgr, AstNode->getLexeme().getDataFlt()));
        }
        return true;
    }

    bool ValChecker::visit(BoolLiteral *AstNode, Ast **Base)
    {
        if (!AstNode->getValueInfo())
        {
            AstNode->setValue(IntVal::Create(mgr, AstNode->getLexeme().getTokTy() == TRUE ? 1 : 0));
        }
        return true;
    }

    bool ValChecker::visit(NumericLiteral *AstNode, Ast **Base)
    {
        if (!AstNode->getValueInfo())
        {
            AstNode->setValue(IntVal::Create(mgr, AstNode->getLexeme().getDataInt()));
        }
        return true;
    }

    bool ValChecker::visit(NullLiteral *AstNode, Ast **Base)
    {
        if (!AstNode->getValueInfo())
        {
            AstNode->setValue(IntVal::Create(mgr, 0));
        }
        return true;
    }

    bool ValChecker::visit(StringLiteral *AstNode, Ast **Base)
    {
        if (!AstNode->getValueInfo())
        {
            std::vector<VALUE *> str;
            for (auto &c : AstNode->getLexeme().getStr())
            {
                str.push_back(IntVal::Create(mgr, c));
            }
            AstNode->setValue(ArrayVal::Create(mgr, str));
        }
        return true;
    }

    bool ValChecker::visit(PremitiveType *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(FnType *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(StructStmt *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(EnumExpr *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(ReturnStmt *AstNode, Ast **Base)
    {
        Ast *&Ret = AstNode->getRetValue();
        if (!visit(Ret, &Ret))
        {
            ///@todo
        }
        AstNode->getFnBlk()->setValue(Ret->getValueInfo());
        IsReturnStmt = true;
        return true;
    }

    /*
       [0][1][2]
    [0] 0  1  2
    [1] 3  4  5
    [2] 6  7  8
    [0,1,2,3,4,5,6,7,8]
    [1][2] ->
    */

    bool ValChecker::visit(FieldExpr *AstNode, Ast **Base)
    {
        auto &field = AstNode->getArgs();
        VALUE *val = AstNode->getValueInfo();
        if (val)
        {
            val = ArrayVal::Create(mgr, {});
        }
        auto &vals = static_cast<ArrayVal *>(val)->getVals();
        for (int i = 0, size = field.size(); i < size; i++)
        {
            auto ty = field[i]->getTypeInfo();

            // same array value {ArrayVal} pass to multi dim that it do not make
            // new array val because we want to store array val to single ArrayVal
            if (ty->Is(Type::ArrayTy))
                field[i]->setValue(val);

            if (!visit(field[i], &field[i]))
            {
                return false;
            }
            auto val = field[i]->getValueInfo();
            if (!ty->Is(Type::ArrayTy))
                vals.push_back(val);
        }

        return true;
    }

    bool ValChecker::visit(FunctionDef *AstNode, Ast **Base)
    {
        // if (visit(AstNode->getFuncBlock(), asAst(&AstNode->getFuncBlock())))
        // {
        //     ///@todo
        // }
        // IsReturnStmt = false;
        return true;
    }

    bool ValChecker::visit(VarStmt *AstNode, Ast **Base)
    {
        auto &vval = AstNode->getVal();
        if (!visit(vval, &vval))
        {
            ///@todo
        }
        auto val = vval->getValueInfo();

        auto ty = AstNode->getType()->getTypeInfo();
        if (AstNode->getValueInfo())
            AstNode->setUpdateValue(val);
        else
            AstNode->setUpdateValue(val->clone(mgr));
        return true;
    }

    bool ValChecker::visit(Array *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(PrefixExpr *AstNode, Ast **Base)
    {
        Ast *&BaseVar = AstNode->getBase();
        if (!visit(BaseVar, &BaseVar))
        {
            ///@todo
        }
        auto Val = BaseVar->getValueInfo();
        if (!Val)
        {
            ///@todo
        }
        VALUE *AstVal = nullptr;
        auto Op = AstNode->getOp();
        if (!AstNode->getValueInfo() && Op.getTokType() != STAR && Op.getTokType() != AND)
        {
            AstNode->setValue(Val->clone(mgr));
            AstVal = AstNode->getValueInfo();
        }
        else
        {
            AstVal = AstNode->getValueInfo();
        }
        switch (AstNode->getOp().getTokType())
        {
        case lex::STAR:
        {
            Type *Ty = AstNode->getTypeInfo();
            if (Ty->type() == Type::PointerTy)
            {
                ///@todo
            }
            else
                AstNode->setValue(Val);
        }
        break;
        case lex::AND:
        {
            AstNode->setValue(Val);
        }
        break;
        case lex::PLUS:
        {
            AstVal->updateValue(BaseVar->getValueInfo());
            // AstNode->setValue(BaseVar->getValueInfo()->clone(mgr));
        }
        break;
        case lex::MINUS:
        {
            VALUE *newVal = nullptr;
            if (Val->getValTy() == VALUE::VInt)
            {
                int64_t i32 = static_cast<IntVal *>(Val)->getVal();
                static_cast<IntVal *>(AstVal)->updateValue(-i32);
            }
            else if (Val->getValTy() == VALUE::VFlt)
            {
                double f32 = static_cast<FltVal *>(Val)->getVal();
                static_cast<FltVal *>(AstVal)->updateValue(-f32);
            }
            else
            {
                ///@todo
            }
        }
        break;
        case lex::CND_NOT:
        {
            if (Val->Is(VALUE::VInt))
            {
                auto v = static_cast<IntVal *>(Val)->getVal();
                v = !v;
                static_cast<IntVal *>(AstVal)->updateValue(v);
            }
            else if (Val->Is(VALUE::VFlt))
            {
                auto v = static_cast<FltVal *>(Val)->getVal();
                v = !v;
                static_cast<FltVal *>(AstVal)->updateValue(v);
            }
        }
        break;
        case lex::NOT:
        {
            if (Val->Is(VALUE::VFlt))
            {
                ///@todo
            }
            if (Val->Is(VALUE::VInt))
            {
                auto v = static_cast<IntVal *>(Val)->getVal();
                v = ~v;
                static_cast<FltVal *>(AstVal)->updateValue(v);
            }
        }
        break;
        default:
            break;
        }

        return true;
    }

    bool ValChecker::visit(GroupedExpr *AstNode, Ast **Base)
    {
        ///@todo
        return true;
    }

    bool ValChecker::visit(Method *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(BranchStmt *AstNode, Ast **Base)
    {
        AstNode->getLexeme().getTokTy() == BREAK ? IsBreakStmt = true : IsContinueStmt = true;
        return true;
    }


    template<typename L, typename R>
    L getConstantFold(L CV1, R CV2) {

        switch (op.getTokType())
            {
            case PLUS:
            case ASN_PLUS:
                CV1 += CV2;
                break;
            case MINUS:
            case ASN_MINUS:
                CV1 -= CV2;
                break;
            case STAR:
            case ASN_STAR:
                CV1 *= CV2;
                break;
            case DIV:
            case ASN_DIV:
                CV1 /= CV2;
                break;
            case MOD:
            case ASN_MOD:
                CV1 = CV1 % CV2;
                break;

            case LSHIFT:
            case ASN_LSHIFT:
                CV1 = CV1 << CV2;
                break;
            case RSHIFT:
            case ASN_RSHIFT:
                CV1 = CV1 >> CV2;
                break;
            case ASN_XOR:
            case XOR:
                CV1 = CV1 ^ CV2;
                break;
            case ASN_OR:
            case OR:
                CV1 = CV1 | CV2;
                break;

            case AND:
            case ASN_AND:
                CV1 = CV1 & CV2;
                break;

            case CND_AND:
                CV1 = CV1 && CV2;
                break;
            case CND_OR:
                CV1 = CV1 || CV2;
                break;

            case GT:
                CV1 = CV1 > CV2;
                break;

            case LT:
                CV1 = CV1 < CV2;
                break;

            case GEQL:
                CV1 = CV1 >= CV2;
                break;

            case LEQL:
                CV1 = CV1 <= CV2;
                break;

            case EQL:
                CV1 = CV1 == CV2;
                break;

            default:
                return false;
            }
    }


    bool ValChecker::visit(Expression *AstNode, Ast **Base)
    {
        Ast *Lhs = AstNode->getLhs();
        Ast *Rhs = AstNode->getRhs();
        switch (AstNode->ExprTy())
        {
        case KMemExpr:
        {
            if (!visit(Lhs, &Lhs))
            {
                ///@todo
                return false;
            }
            auto stval = static_cast<StructVal *>(Lhs->getValueInfo());
            if (!stval)
            {
                ///@todo
            }
            auto val = stval->getVal(Rhs->toString());
            if (!val)
            {
                ///@todo
            }
            AstNode->setValue(val);
        }
        break;
        case KBinaryExpr:
        {
            if (!visit(Lhs, &Lhs))
            {
                ///@todo
                return false;
            }

            if (!visit(Rhs, &Rhs))
            {
                ///@todo
                return false;
            }
            VALUE *LhsVal = Lhs->getValueInfo();
            if (!LhsVal)
            {
            }
            Type *LhsTy = Rhs->getTypeInfo();

            VALUE *RhsVal = Lhs->getValueInfo();
            if (!RhsVal)
            {
            }
            Type *RhsTy = Lhs->getTypeInfo();
            const Tok &op = AstNode->getOp();

            if (!LhsVal->Is(VALUE::VInt) && !RhsVal->Is(VALUE::VFlt))
            {
                ///@todo
            }

            double lval;


            if (op.getTokType() == ASN)
            {
                if (RhsTy->Is(Type::PointerTy) || RhsTy->Is(Type::RefTy))
                {
                    Lhs->setValue(RhsVal);
                    // Lhs->getDecl()->setValue(RhsVal);
                }
                else if (Lhs->getValueInfo())
                    Lhs->setUpdateValue(RhsVal);
                else
                    Lhs->setUpdateValue(RhsVal->clone(mgr));
            }

            if (LhsVal->Is(VALUE::VInt))
            {
                lval = static_cast<IntVal *>(LhsVal)->getVal();
            }
            if (LhsVal->Is(VALUE::VFlt))
            {
                lval = static_cast<FltVal *>(LhsVal)->getVal();
            }

            if (RhsVal->Is(VALUE::VInt))
            {
                rval = static_cast<IntVal *>(RhsVal)->getVal();
            }
            else if (RhsVal->Is(VALUE::VFlt))
            {
                rval = static_cast<FltVal *>(RhsVal)->getVal();
            }

            switch (op.getTokType())
            {
            case PLUS:
            case ASN_PLUS:
                lval += rval;
                break;
            case MINUS:
            case ASN_MINUS:
                lval -= rval;
                break;
            case STAR:
            case ASN_STAR:
                lval *= rval;
                break;
            case DIV:
            case ASN_DIV:
                lval /= rval;
                break;
            case MOD:
            case ASN_MOD:
                lval = (int32_t)lval % (int32_t)rval;
                break;

            case LSHIFT:
            case ASN_LSHIFT:
                lval = (int32_t)lval << (int32_t)rval;
                break;
            case RSHIFT:
            case ASN_RSHIFT:
                lval = (int32_t)lval >> (int32_t)rval;
                break;
            case ASN_XOR:
            case XOR:
                lval = (int32_t)lval ^ (int32_t)rval;
                break;
            case ASN_OR:
            case OR:
                lval = (int32_t)lval | (int32_t)rval;
                break;

            case AND:
            case ASN_AND:
                lval = (int32_t)lval & (int32_t)rval;
                break;

            case CND_AND:
                lval = (int32_t)lval && (int32_t)rval;
                break;
            case CND_OR:
                lval = (int32_t)lval || (int32_t)rval;
                break;

            case GT:
                lval = (int32_t)lval > (int32_t)rval;
                break;

            case LT:
                lval = (int32_t)lval < (int32_t)rval;
                break;

            case GEQL:
                lval = (int32_t)lval >= (int32_t)rval;
                break;

            case LEQL:
                lval = (int32_t)lval <= (int32_t)rval;
                break;

            case EQL:
                lval = (int32_t)lval == (int32_t)rval;
                break;

            default:
                return false;
            }

            if (op.IsAssnCombinedOP())
            {
                if (LhsVal->Is(VALUE::VFlt))
                {
                    static_cast<FltVal *>(LhsVal)->updateValue(lval);
                }
                else
                {
                    static_cast<IntVal *>(LhsVal)->updateValue(lval);
                }
            }
            else
            {
                auto Val = AstNode->getValueInfo();
                if (!Val)
                {
                    Val = FltVal::Create(mgr, lval);
                }
                else if (LhsVal->Is(VALUE::VFlt))
                {
                    static_cast<FltVal *>(Val)->updateValue(lval);
                }
                else
                {
                    static_cast<IntVal *>(Val)->updateValue(lval);
                }
                if (!Val)
                {
                    Val = FltVal::Create(mgr, lval);
                }
                else if (LhsVal->Is(VALUE::VFlt))
                {
                    static_cast<FltVal *>(Val)->updateValue(lval);
                }
                else
                {
                    static_cast<IntVal *>(Val)->updateValue(lval);
                }
            }
        }
        break;

        case KIndexExpr:
        {
            if (!visit(Lhs, &Lhs))
            {
                ///@todo
                return false;
            }

            auto &field = static_cast<FieldExpr *>(Rhs)->getArgs();

            auto arrvals = static_cast<ArrayVal *>(Lhs->getValueInfo());
            if (!arrvals)
            {
                ///@todo
            }

            auto ArrTy = static_cast<ArrayType *>(Lhs->getTypeInfo());
            auto ArrSize = ArrTy->getSize();
            auto &arrdata = arrvals->getVals();
            int i = 0;
            int idx = 1;
            auto size = field.size();
            for (auto &F : field)
            {
                if (!visit(F, &F))
                {
                    ///@todo
                }
                auto val = F->getValueInfo();
                if (!val)
                {
                    ///@todo
                }
                if (val && !val->Is(VALUE::VInt))
                {
                    ///@todo
                }
                auto intval = static_cast<IntVal *>(val);
                int idxval = intval->getVal();
                if (idxval < 0 || idxval > ArrSize)
                {
                    ///@todo
                }
                if (i < size - 1)
                    idx *= idxval + 1;
                else
                    idx += idxval;
                i++;
            }

            AstNode->setValue(arrdata[idx]);
        }
        break;
        case KAsExpr:
        {
            if(!visit(Lhs, &Lhs)) {
                return false;
            }
            VALUE *Val = Lhs->getValueInfo();
            if(Val->getValTy() != VALUE::VInt && Val->getValTy() != VALUE::VFlt) {
                return false;
            }
            Type *DestTy = Rhs->getTypeInfo();
            switch (DestTy->type())
            {
            case Type::IntTy:
            {
                IntType *ITy = as<IntType>(DestTy);
                switch (Val->getValTy())
                {
                case VALUE::VInt:
                    if(!ITy->isSignInt()) {

                    }
                    break;
                case VALUE::VFlt:

                    break;
                default:
                    break;
                }

            }
                break;
            case Type::FltTy:
                
                break;
            default:
                return false;
            }
        }
        break;
        case KStructExpr:
        {
            std::vector<Ast *> field = static_cast<FieldExpr *>(Rhs)->getArgs();
            StructVal *stval = StructVal::Create(mgr, {});
            auto &stidxval = stval->getVals();
            for (ssize_t i = 0, siz = field.size(); i < siz; i++)
            {
                auto Varn = static_cast<VarStmt *>(field[i])->getVar();
                auto &Val = static_cast<VarStmt *>(field[i])->getVal();
                if (visit(Val, &Val))
                {
                    ///@todo
                }
                auto val = Val->getValueInfo();
                if (!val)
                {
                    ///@todo
                }
                if (field[i]->getTypeInfo()->Is(Type::RefTy) || field[i]->getTypeInfo()->Is(Type::PointerTy))
                {
                    field[i]->setValue(val);
                }
                else
                    field[i]->setUpdateValue(val->clone(mgr));
                stidxval.insert({Varn.getStr(), val});
            }
            AstNode->setUpdateValue(stval);
        }
        break;
        case KCallExpr:
        {
            auto &decl = Lhs->getDecl();
            auto fn = static_cast<FunctionDef *>(decl);
            if (!fn)
            {
                ///@todo
            }
            if (!mustConst && !fn->IsConst())
            {
                return true;
            }
            if (!mustConst && fn->IsConst())
            {
                ///@todo
            }

            auto &field = static_cast<FieldExpr *>(Rhs)->getArgs();
            auto &fnparam = fn->getFnProto()->getParameter();
            auto *stval = StructVal::Create(mgr, {});
            auto &stidxval = stval->getVals();
            int i = 0;
            for (auto &arg : field)
            {
                if (visit(arg, &arg))
                {
                    ///@todo
                }
                auto val = arg->getValueInfo();
                auto cval = val->clone(mgr);
                if (fnparam[i]->getTypeInfo()->Is(Type::RefTy) || fnparam[i]->getTypeInfo()->Is(Type::PointerTy))
                {
                    fnparam[i]->setValue(val);
                }
                else
                    fnparam[i]->setUpdateValue(cval);
                // LocalVal.push_back(cval);
                i++;
            }
            if (!visit(decl, &decl))
            {
                ///@todo
            }
            auto BlkVal = fn->getFuncBlock()->getValueInfo();
            if (!BlkVal)
            {
                ///@todo
            }
            AstNode->setValue(BlkVal);
        }
        break;
        default:
            break;
        }
        return true;
    }

    bool ValChecker::visit(BlockStmt *AstNode, Ast **Base)
    {
        for (auto &stmt : AstNode->getStmts())
        {
            if (!visit(stmt, &stmt))
            {
                ///@todo
            }
            if (IsReturnStmt || IsBreakStmt || IsContinueStmt)
            {
                break;
            }
        }
        return true;
    }

    bool ValChecker::visit(ForLoop *AstNode, Ast **Base)
    {
        auto &Var = AstNode->getVar();
        auto &Cond = AstNode->getCond();
        auto &Incr = AstNode->getIncr();
        auto &Blk = AstNode->getBlock();
        auto &stmts = Blk->getStmts();
        auto limit = 0;
        if (Var && !visit(Var, &Var))
        {
            ///@todo
        }
        if (!visit(Cond, &Cond))
        {
            ///@todo
        }
        auto CondVal = Cond->getValueInfo();
        while (CondVal->Is(VALUE::VInt) && static_cast<IntVal *>(CondVal)->getVal())
        {
            if (mustConst && !CondVal)
            {
                ///@todo;
            }
            if (limit >= MAX_LOOP_LIMIT)
            {
                ///@todo break;
            }
            if (!visit(Blk, asAst(&Blk)))
            {
                ///@todo
            }
            if (IsReturnStmt || IsBreakStmt)
            {
                break;
            }
            IsContinueStmt = false;
            limit++;
            if (Incr && !visit(Incr, &Incr))
            {
                ///@todo
            }
            if (Cond && !visit(Cond, &Cond))
            {
                ///@todo
            }
        }
        return true;
    }

    bool ValChecker::visit(WhileLoop *AstNode, Ast **Base)
    {
        auto &Cond = AstNode->getCond();
        auto &Blk = AstNode->getBlock();
        auto &stmts = Blk->getStmts();
        auto limit = 0;
        if (!visit(Cond, &Cond))
        {
            ///@todo
        }
        auto CondVal = Cond->getValueInfo();
        while (CondVal->Is(VALUE::VInt) && static_cast<IntVal *>(CondVal)->getVal())
        {

            if (mustConst && !CondVal)
            {
                ///@todo;
            }

            if (limit >= MAX_LOOP_LIMIT)
            {
                ///@todo break;
            }

            if (!visit(Blk, asAst(&Blk)))
            {
                ///@todo
            }
            if (IsReturnStmt || IsBreakStmt)
            {
                break;
            }
            IsContinueStmt = false;
            limit++;
            if (!visit(Cond, &Cond))
            {
                ///@todo
            }
        }
        return true;
    }

    bool ValChecker::visit(IfStmt *AstNode, Ast **Base)
    {
        auto &Cond = AstNode->getCondV();
        auto &IfBlk = AstNode->getIfBlock();
        auto &EfBlk = AstNode->getElBlock();
        if (!visit(Cond, &Cond))
        {
            ///@todo
        }
        auto CondVal = Cond->getValueInfo();
        if (!CondVal)
        {
            ///@todo
        }
        if (!CondVal->Is(VALUE::VInt))
        {
            ///@todo
        }
        auto BoolVal = static_cast<IntVal *>(CondVal)->getVal();
        if (BoolVal)
        {
            if (!visit(IfBlk, asAst(&IfBlk)))
            {
                ///@todo
            }
        }
        else
        {
            if (!visit(EfBlk, &EfBlk))
            {
                ///@todo
            }
        }
        return true;
    }

    bool ValChecker::visit(UseStmt *AstNode, Ast **Base)
    {
        return true;
    }

}
