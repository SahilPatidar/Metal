// #pragma once
#include "../../include/analyzer/ValCheck.hpp"
#include"../../include/parser/type.hpp"
#include "../../include/analyzer/Value.hpp"
#include "../../include/Error.hpp"

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
                return false;
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
            AstNode->setValue(IntVal::Create(mgr, AstNode->getLexeme().getTokTy() == TRUE ? 1 : 0, VALUE::VBool));
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
        if (!AstNode->getValueInfo() && AstNode->ischar())
        {
            AstNode->setValue(IntVal::Create(mgr, AstNode->getLexeme().getDataInt()));
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
        return true;
    }

    bool ValChecker::visit(FunctionDef *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(VarStmt *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(Array *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(PrefixExpr *AstNode, Ast **Base)
    {
        Ast *&BaseVar = AstNode->getBase();
        if (!visit(BaseVar, &BaseVar)) {
            return false;
        }
        VALUE *Val = BaseVar->getValueInfo();
        VALUE *AstVal = nullptr;
        auto Op = AstNode->getOp();
        if (!AstNode->getValueInfo())
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
        case STAR:
        break;
        case AND:
        break;
        case MINUS:
        {
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
        }
        break;
        case CND_NOT:
        {
            if (Val->Is(VALUE::VInt))
            {
                int64_t CV = as<IntVal>(Val)->getVal();
                as<IntVal>(AstVal)->updateValue(!CV);
            }
            else if (Val->Is(VALUE::VFlt))
            {
                double CV = static_cast<FltVal *>(Val)->getVal();
                static_cast<FltVal *>(AstVal)->updateValue(!CV);
            }
        }
        break;
        case NOT:
        {
            if (Val->Is(VALUE::VInt))
            {
                int64_t CV = static_cast<IntVal *>(Val)->getVal();
                static_cast<IntVal *>(AstVal)->updateValue(~CV);
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
        return true;
    }

    bool ValChecker::visit(Method *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(BranchStmt *AstNode, Ast **Base)
    {
        return true;
    }


    bool ValChecker::visit(Expression *AstNode, Ast **Base)
    {
        Ast *Lhs = AstNode->getLhs();
        Ast *Rhs = AstNode->getRhs();
        switch (AstNode->getExprID())
        {
        case Expression::KMemExpr:
        break;
        case Expression::KBinaryExpr:
        {
            if (!visit(Lhs, &Lhs)) {
                return false;
            }

            if (!visit(Rhs, &Rhs)) {
                return false;
            }

            Token_type Op = AstNode->getOp().getTokType();
            VALUE *LhsVal = Lhs->getValueInfo();
            VALUE *RhsVal = Rhs->getValueInfo();
            if (LhsVal->Is(VALUE::VInt) && RhsVal->Is(VALUE::VInt))
            {
                int64_t CV1= as<IntVal>(LhsVal)->getVal();
                int64_t CV2= as<IntVal>(RhsVal)->getVal();
                if (Op == MODULO || Op == DIV && (CV2 == 0)) {
                    err::err_out(Lhs->getStmtLoc(), "attempt to calculate the remainder or divide with a divisor of zero");
                    return false;
                }
                switch (Op)
                {
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
                case NEQL:
                    CV1 = CV1 != CV2;
                    break;
                case PLUS:
                    CV1 = CV1 + CV2;
                    break;
                case MINUS:
                    CV1 = CV1 - CV2;
                    break;
                case STAR:
                    CV1 = CV1 * CV2;
                    break;
                case DIV:
                    CV1 = CV1 / CV2;
                    break;
                case MOD:
                    CV1 =  CV1 %= CV2;
                    break;
                case LSHIFT:
                    CV1 =  CV1 << CV2;
                    break;
                case RSHIFT:
                    CV1 =  CV1 >> CV2;
                    break;
                case XOR:
                    CV1 =  CV1 ^ CV2;
                    break;
                case OR:
                    CV1 =  CV1 | CV2;
                    break;
                case AND:
                    CV1 =  CV1 & CV2;
                    break;
                default:
                    return false;
                }

                if(AstNode->getOp().IsConditionalOP()){
                    AstNode->setValue(IntVal::Create(mgr, (int64_t)(CV1?1:0), VALUE::VBool));
                }else if (!AstNode->getValueInfo())
                {
                    AstNode->setValue(IntVal::Create(mgr, CV1));
                }else {
                    VALUE *Val = AstNode->getValueInfo();
                    as<IntVal>(Val)->updateValue(CV1);
                }
            }else if(LhsVal->Is(VALUE::VFlt) && RhsVal->Is(VALUE::VFlt)) {
                double CV1= as<FltVal>(LhsVal)->getVal();
                double CV2= as<FltVal>(RhsVal)->getVal();
                if (Op == DIV && (CV2 == 0)) {
                    err::err_out(Lhs->getStmtLoc(), "attempt to calculate the remainder or divide with a divisor of zero");
                }

                switch (Op)
                {
                case CND_AND:
                    CV1 =  CV1 && CV2;
                    break;
                case CND_OR:
                    CV1 =  CV1 || CV2;
                    break;
                case GT:
                    CV1 =  CV1 > CV2;
                    break;
                case LT:
                    CV1 =  CV1 < CV2;
                    break;
                case GEQL:
                    CV1 =  CV1 >= CV2;
                    break;
                case LEQL:
                    CV1 =  CV1 <= CV2;
                    break;
                case EQL:
                    CV1 =  CV1 == CV2;
                    break;
                case NEQL:
                    CV1 =  CV1 != CV2;
                    break;
                case PLUS:
                    CV1 =  CV1 + CV2;
                    break;
                case MINUS:
                    CV1 =  CV1 - CV2;
                    break;
                case STAR:
                    CV1 =  CV1 * CV2;
                    break;
                case DIV:
                    CV1 =  CV1 / CV2;
                    break;
                default:
                    return false;
                }

                if(AstNode->getOp().IsConditionalOP()){
                    AstNode->setValue(IntVal::Create(mgr, CV1?1:0, VALUE::VBool));
                }else if (!AstNode->getValueInfo())
                {
                    AstNode->setValue(FltVal::Create(mgr, CV1));
                }else {
                    VALUE *Val = AstNode->getValueInfo();
                    static_cast<FltVal *>(Val)->updateValue(CV1);
                }
            }else if(LhsVal->Is(VALUE::VBool) && RhsVal->Is(VALUE::VBool)) {
                bool CV1= (bool)as<IntVal>(LhsVal)->getVal();
                bool CV2= (bool)as<IntVal>(RhsVal)->getVal();
                switch (Op)
                {
                case XOR:
                    CV1 =  CV1 ^ CV2;
                    break;
                case OR:
                    CV1 =  CV1 | CV2;
                    break;
                case AND:
                    CV1 =  CV1 & CV2;
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
                case NEQL:
                    CV1 = CV1 == CV2;
                    break;
                default:
                    return false;
                }

                if (!AstNode->getValueInfo())
                {
                    AstNode->setValue(IntVal::Create(mgr, CV1?1:0, VALUE::VBool));
                }else {
                    VALUE *Val = AstNode->getValueInfo();
                    static_cast<IntVal *>(Val)->updateValue(CV1);
                }
            }
            std::cout<<"here"<<std::endl;
        }
        break;
        case Expression::KIndexExpr:
        break;
        case Expression::KAsExpr:
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
                if(Val->Is(VALUE::VFlt) && ITy->isSignInt())
                    AstNode->setValue(IntVal::Create(mgr, (uint64_t)as<FltVal>(Val)->getVal()));
                else if(Val->Is(VALUE::VFlt) && !ITy->isSignInt())
                    AstNode->setValue(IntVal::Create(mgr, (int64_t)as<FltVal>(Val)->getVal()));

            }
                break;
            case Type::FltTy:
            {
                if(Val->Is(VALUE::VInt)){
                    AstNode->setValue(FltVal::Create(mgr, (double)as<IntVal>(Val)->getVal()));
                }
            }   
                break;
            default:
                return false;
            }
        }
        break;
        case Expression::KStructExpr:
        break;
        case Expression::KCallExpr:
        break;
        default:
            return false;
        }
        return true;
    }

    bool ValChecker::visit(BlockStmt *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(ForLoop *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(WhileLoop *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(IfStmt *AstNode, Ast **Base)
    {
        return true;
    }

    bool ValChecker::visit(UseStmt *AstNode, Ast **Base)
    {
        return true;
    }

}
