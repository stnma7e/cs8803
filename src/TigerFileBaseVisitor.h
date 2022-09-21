#ifndef TIGERFILEBASEVISITOR_H_
#define TIGERFILEBASEVISITOR_H_


#include <any>
#include <string>
#include <vector>

#include "TigerParser.h"
#include "TigerVisitor.h"


class TigerFileBaseVisitor : public TigerVisitor {
    virtual antlrcpp::Any visitTiger_program(TigerParser::Tiger_programContext *context);
    virtual antlrcpp::Any visitDecl_segment(TigerParser::Decl_segmentContext *context);
    virtual antlrcpp::Any visitType_decl_list(TigerParser::Type_decl_listContext *context);
    virtual antlrcpp::Any visitVar_decl_list(TigerParser::Var_decl_listContext *context);
    virtual antlrcpp::Any visitFunct_list(TigerParser::Funct_listContext *context);
    virtual antlrcpp::Any visitType_decl(TigerParser::Type_declContext *context);
    virtual antlrcpp::Any visitType(TigerParser::TypeContext *context);
    virtual antlrcpp::Any visitBase_type(TigerParser::Base_typeContext *context);
    virtual antlrcpp::Any visitVar_decl(TigerParser::Var_declContext *context);
    virtual antlrcpp::Any visitStorage_class(TigerParser::Storage_classContext *context);
    virtual antlrcpp::Any visitId_list(TigerParser::Id_listContext *context);
    virtual antlrcpp::Any visitOptional_init(TigerParser::Optional_initContext *context);
    virtual antlrcpp::Any visitFunct(TigerParser::FunctContext *context);
    virtual antlrcpp::Any visitParam_list(TigerParser::Param_listContext *context);
    virtual antlrcpp::Any visitParam_list_tail(TigerParser::Param_list_tailContext *context);
    virtual antlrcpp::Any visitRet_type(TigerParser::Ret_typeContext *context);
    virtual antlrcpp::Any visitParam(TigerParser::ParamContext *context);
    virtual antlrcpp::Any visitStat_seq(TigerParser::Stat_seqContext *context);
    virtual antlrcpp::Any visitValueAssign(TigerParser::ValueAssignContext *context);
    virtual antlrcpp::Any visitIfThen(TigerParser::IfThenContext *context);
    virtual antlrcpp::Any visitIfThenElse(TigerParser::IfThenElseContext *context);
    virtual antlrcpp::Any visitWhile(TigerParser::WhileContext *context);
    virtual antlrcpp::Any visitFor(TigerParser::ForContext *context);
    virtual antlrcpp::Any visitFunctCall(TigerParser::FunctCallContext *context);
    virtual antlrcpp::Any visitBreak(TigerParser::BreakContext *context);
    virtual antlrcpp::Any visitReturn(TigerParser::ReturnContext *context);
    virtual antlrcpp::Any visitLet(TigerParser::LetContext *context);
    virtual antlrcpp::Any visitOptreturn(TigerParser::OptreturnContext *context);
    virtual antlrcpp::Any visitOptprefix(TigerParser::OptprefixContext *context);
    virtual antlrcpp::Any visitExpr(TigerParser::ExprContext *context);
    virtual antlrcpp::Any visitConstt(TigerParser::ConsttContext *context);
    virtual antlrcpp::Any visitBinary_operator(TigerParser::Binary_operatorContext *context);
    virtual antlrcpp::Any visitExpr_list(TigerParser::Expr_listContext *context);
    virtual antlrcpp::Any visitExpr_list_tail(TigerParser::Expr_list_tailContext *context);
    virtual antlrcpp::Any visitValue(TigerParser::ValueContext *context);
    virtual antlrcpp::Any visitValue_tail(TigerParser::Value_tailContext *context);
};

class TigerError : public std::exception {
private:
    const bool _isLex;

public:
    TigerError(bool isLex)
        : _isLex(isLex)
    {}

    bool isLex() const {
        return _isLex;
    }
};

class TigerLexErrorListener : public antlr4::BaseErrorListener {
    virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e);
};

class TigerParseErrorListener : public antlr4::BaseErrorListener {
    virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e);
};

#endif
