#ifndef TIGERFILEBASEVISITOR_H_
#define TIGERFILEBASEVISITOR_H_


#include <any>
#include <string>
#include <vector>

#include "TigerParser.h"
#include "TigerVisitor.h"


class TigerParseError : public std::exception {};

class TigerFileBaseVisitor : public TigerVisitor {
    virtual std::any visitTiger_program(TigerParser::Tiger_programContext *context);
    virtual std::any visitDecl_segment(TigerParser::Decl_segmentContext *context);
    virtual std::any visitType_decl_list(TigerParser::Type_decl_listContext *context);
    virtual std::any visitVar_decl_list(TigerParser::Var_decl_listContext *context);
    virtual std::any visitFunct_list(TigerParser::Funct_listContext *context);
    virtual std::any visitType_decl(TigerParser::Type_declContext *context);
    virtual std::any visitType(TigerParser::TypeContext *context);
    virtual std::any visitBase_type(TigerParser::Base_typeContext *context);
    virtual std::any visitVar_decl(TigerParser::Var_declContext *context);
    virtual std::any visitStorage_class(TigerParser::Storage_classContext *context);
    virtual std::any visitId_list(TigerParser::Id_listContext *context);
    virtual std::any visitOptional_init(TigerParser::Optional_initContext *context);
    virtual std::any visitFunct(TigerParser::FunctContext *context);
    virtual std::any visitParam_list(TigerParser::Param_listContext *context);
    virtual std::any visitParam_list_tail(TigerParser::Param_list_tailContext *context);
    virtual std::any visitRet_type(TigerParser::Ret_typeContext *context);
    virtual std::any visitParam(TigerParser::ParamContext *context);
    virtual std::any visitStat_seq(TigerParser::Stat_seqContext *context);
    virtual std::any visitValueAssign(TigerParser::ValueAssignContext *context);
    virtual std::any visitIfThen(TigerParser::IfThenContext *context);
    virtual std::any visitIfThenElse(TigerParser::IfThenElseContext *context);
    virtual std::any visitWhile(TigerParser::WhileContext *context);
    virtual std::any visitFor(TigerParser::ForContext *context);
    virtual std::any visitFunctCall(TigerParser::FunctCallContext *context);
    virtual std::any visitBreak(TigerParser::BreakContext *context);
    virtual std::any visitReturn(TigerParser::ReturnContext *context);
    virtual std::any visitLet(TigerParser::LetContext *context);
    virtual std::any visitOptreturn(TigerParser::OptreturnContext *context);
    virtual std::any visitOptprefix(TigerParser::OptprefixContext *context);
    virtual std::any visitExpr(TigerParser::ExprContext *context);
    virtual std::any visitConstt(TigerParser::ConsttContext *context);
    virtual std::any visitBinary_operator(TigerParser::Binary_operatorContext *context);
    virtual std::any visitExpr_list(TigerParser::Expr_listContext *context);
    virtual std::any visitExpr_list_tail(TigerParser::Expr_list_tailContext *context);
    virtual std::any visitValue(TigerParser::ValueContext *context);
    virtual std::any visitValue_tail(TigerParser::Value_tailContext *context);
};

#endif
