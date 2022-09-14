#include <string>

#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"

std::pair<std::string, std::string> token_pair(const std::string& token_type, const std::string& token_value) {
    return std::pair(token_type, token_value);
}

std::any TigerFileBaseVisitor::visitTiger_program(TigerParser::Tiger_programContext *context) {
    const std::string id = context->ID()->getText();
    tokens.insert(token_pair("PROGRAM", id));
    context->decl_segment()->accept(this);
    context->funct_list()->accept(this);
    return nullptr;
}

std::any TigerFileBaseVisitor::visitDecl_segment(TigerParser::Decl_segmentContext *context) {
    return nullptr;
}

std::any TigerFileBaseVisitor::visitType_decl_list(TigerParser::Type_decl_listContext *context) {

}

std::any TigerFileBaseVisitor::visitVar_decl_list(TigerParser::Var_decl_listContext *context) {

}

std::any TigerFileBaseVisitor::visitFunct_list(TigerParser::Funct_listContext *context) {
    if (context->funct()) {
        context->funct()->accept(this);
    }
    if (context->funct_list()) {
        context->funct_list()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitType_decl(TigerParser::Type_declContext *context) {

}

std::any TigerFileBaseVisitor::visitType(TigerParser::TypeContext *context) {

}

std::any TigerFileBaseVisitor::visitBase_type(TigerParser::Base_typeContext *context) {

}

std::any TigerFileBaseVisitor::visitVar_decl(TigerParser::Var_declContext *context) {

}

std::any TigerFileBaseVisitor::visitStorage_class(TigerParser::Storage_classContext *context) {

}

std::any TigerFileBaseVisitor::visitId_list(TigerParser::Id_listContext *context) {

}

std::any TigerFileBaseVisitor::visitOptional_init(TigerParser::Optional_initContext *context) {

}

std::any TigerFileBaseVisitor::visitFunct(TigerParser::FunctContext *context) {
    const std::string id = context->ID()->getText();
    tokens.insert(token_pair("FUNCTION", id));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitParam_list(TigerParser::Param_listContext *context) {

}

std::any TigerFileBaseVisitor::visitParam_list_tail(TigerParser::Param_list_tailContext *context) {

}

std::any TigerFileBaseVisitor::visitRet_type(TigerParser::Ret_typeContext *context) {

}

std::any TigerFileBaseVisitor::visitParam(TigerParser::ParamContext *context) {

}

std::any TigerFileBaseVisitor::visitStat_seq(TigerParser::Stat_seqContext *context) {

}

std::any TigerFileBaseVisitor::visitStat(TigerParser::StatContext *context) {

}

std::any TigerFileBaseVisitor::visitOptreturn(TigerParser::OptreturnContext *context) {

}

std::any TigerFileBaseVisitor::visitOptprefix(TigerParser::OptprefixContext *context) {

}

std::any TigerFileBaseVisitor::visitExpr(TigerParser::ExprContext *context) {

}

std::any TigerFileBaseVisitor::visitConst(TigerParser::ConstContext *context) {

}

std::any TigerFileBaseVisitor::visitBinary_operator(TigerParser::Binary_operatorContext *context) {

}

std::any TigerFileBaseVisitor::visitExpr_list(TigerParser::Expr_listContext *context) {

}

std::any TigerFileBaseVisitor::visitExpr_list_tail(TigerParser::Expr_list_tailContext *context) {

}

std::any TigerFileBaseVisitor::visitValue(TigerParser::ValueContext *context) {

}

std::any TigerFileBaseVisitor::visitValue_tail(TigerParser::Value_tailContext *context) {

}
