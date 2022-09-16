#include <string>

#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"

std::pair<std::string, std::string> token(antlr4::tree::TerminalNode *node) {
    //TODO first element the actual token name (UPPERCASE)
    return std::pair(node->getText(), node->getText());
}

std::pair<std::string, std::string> token_pair(const std::string& token_type, antlr4::tree::TerminalNode *token_value) {
    return std::pair(token_type, token_value->getText());
}

std::any TigerFileBaseVisitor::visitTiger_program(TigerParser::Tiger_programContext *context) {
    tokens.push_back(token(context->PROGRAM()));
    tokens.push_back(token_pair("ID", context->ID()));
    tokens.push_back(token(context->LET()));
    context->decl_segment()->accept(this);
    tokens.push_back(token(context->BEGIN()));
    context->funct_list()->accept(this);
    tokens.push_back(token(context->END()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitDecl_segment(TigerParser::Decl_segmentContext *context) {
    if (context->type_decl_list()) {
        context->type_decl_list()->accept(this);
    }
    if (context->var_decl_list()) {
        context->var_decl_list()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitType_decl_list(TigerParser::Type_decl_listContext *context) {
    if (context->type_decl()) {
        context->type_decl()->accept(this);
    }
    if (context->type_decl_list()) {
        context->type_decl_list()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitVar_decl_list(TigerParser::Var_decl_listContext *context) {
    if (context->var_decl()) {
        context->var_decl()->accept(this);
    }
    if (context->var_decl_list()) {
        context->var_decl_list()->accept(this);
    }
    return nullptr;
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
    tokens.push_back(token(context->TYPE()));
    tokens.push_back(token_pair("ID", context->ID()));
    tokens.push_back(token_pair("TASSIGN", context->TASSIGN()));
    context->type()->accept(this);
    tokens.push_back(token_pair("SEMICOLON", context->SEMICOLON()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitType(TigerParser::TypeContext *context) {
    return nullptr;
}

std::any TigerFileBaseVisitor::visitBase_type(TigerParser::Base_typeContext *context) {
    return nullptr;
}

std::any TigerFileBaseVisitor::visitVar_decl(TigerParser::Var_declContext *context) {
    return nullptr;
}

std::any TigerFileBaseVisitor::visitStorage_class(TigerParser::Storage_classContext *context) {

}

std::any TigerFileBaseVisitor::visitId_list(TigerParser::Id_listContext *context) {

}

std::any TigerFileBaseVisitor::visitOptional_init(TigerParser::Optional_initContext *context) {

}

std::any TigerFileBaseVisitor::visitFunct(TigerParser::FunctContext *context) {
    tokens.push_back(token(context->FUNCTION()));
    tokens.push_back(token_pair("ID", context->ID()));
    tokens.push_back(token_pair("OPENPAREN", context->OPENPAREN()));
    context->param_list()->accept(this);
    tokens.push_back(token_pair("CLOSEPAREN", context->CLOSEPAREN()));
    context->ret_type()->accept(this);
    tokens.push_back(token(context->BEGIN()));
    context->stat_seq()->accept(this);
    tokens.push_back(token(context->END()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitParam_list(TigerParser::Param_listContext *context) {
    return nullptr;
}

std::any TigerFileBaseVisitor::visitParam_list_tail(TigerParser::Param_list_tailContext *context) {

}

std::any TigerFileBaseVisitor::visitRet_type(TigerParser::Ret_typeContext *context) {
    return nullptr;
}

std::any TigerFileBaseVisitor::visitParam(TigerParser::ParamContext *context) {

}

std::any TigerFileBaseVisitor::visitStat_seq(TigerParser::Stat_seqContext *context) {
    return nullptr;
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
