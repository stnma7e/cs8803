#include <string>

#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"

std::pair<std::string, std::string> token(const std::string& token_type, antlr4::tree::TerminalNode *token_value) {
    return std::pair(token_type, token_value->getText());
}

std::pair<std::string, std::string> token(antlr4::tree::TerminalNode *node) {
    //TODO first element the actual token name (UPPERCASE)
    return token(node->getText(), node);
}

std::any TigerFileBaseVisitor::visitTiger_program(TigerParser::Tiger_programContext *context) {
    tokens.push_back(token(context->PROGRAM()));
    tokens.push_back(token("ID", context->ID()));
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
    tokens.push_back(token("ID", context->ID()));
    tokens.push_back(token("TASSIGN", context->TASSIGN()));
    context->type()->accept(this);
    tokens.push_back(token("SEMICOLON", context->SEMICOLON()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitType(TigerParser::TypeContext *context) {
    //TODO how do I select only one of these?
    if (context->base_type()) {
        context->base_type()->accept(this);
    }
    if (context->ARRAY()) {
        //TODO fix this syntax
        tokens.push_back(token(context->ARRAY()));
        tokens.push_back(token("OPENBRACK", context->OPENBRACK()));
        tokens.push_back(token("INTLIT", context->INTLIT()));
        tokens.push_back(token("CLOSEBRACK", context->CLOSEBRACK()));
        tokens.push_back(token(context->OF()));
        context->base_type()->accept(this);
    }
    if (context->ID()) {
        tokens.push_back(token("ID", context->ID()));
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitBase_type(TigerParser::Base_typeContext *context) {
    if (context->INT()) {
        tokens.push_back(token(context->INT()));
    }
    if (context->FLOAT()) {
        tokens.push_back(token(context->FLOAT()));
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitVar_decl(TigerParser::Var_declContext *context) {
    context->storage_class()->accept(this);
    context->id_list()->accept(this);
    tokens.push_back(token("COLON", context->COLON()));
    context->type()->accept(this);
    context->optional_init()->accept(this);
    tokens.push_back(token("SEMICOLON", context->SEMICOLON()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitStorage_class(TigerParser::Storage_classContext *context) {
    if (context->VAR()) {
        tokens.push_back(token(context->VAR()));
    }
    if (context->STATIC()) {
        tokens.push_back(token(context->STATIC()));
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitId_list(TigerParser::Id_listContext *context) {
    if (context->ID()) {
        tokens.push_back(token("ID", context->ID()));
    }
    if (context->COMMA()) {
        tokens.push_back(token("COMMA", context->COMMA()));
    }
    if (context->id_list()) {
        context->id_list()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitOptional_init(TigerParser::Optional_initContext *context) {
    if (context->ASSIGN()) {
        tokens.push_back(token("ASSIGN", context->ASSIGN()));
        context->const_()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitFunct(TigerParser::FunctContext *context) {
    tokens.push_back(token(context->FUNCTION()));
    tokens.push_back(token("ID", context->ID()));
    tokens.push_back(token("OPENPAREN", context->OPENPAREN()));
    context->param_list()->accept(this);
    tokens.push_back(token("CLOSEPAREN", context->CLOSEPAREN()));
    context->ret_type()->accept(this);
    tokens.push_back(token(context->BEGIN()));
    context->stat_seq()->accept(this);
    tokens.push_back(token(context->END()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitParam_list(TigerParser::Param_listContext *context) {
    if (context->param()) {
        context->param()->accept(this);
    }
    if (context->param_list_tail()) {
        context->param_list_tail()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitParam_list_tail(TigerParser::Param_list_tailContext *context) {
    if (context->COMMA()) {
        tokens.push_back(token("COMMA", context->COMMA()));
        context->param()->accept(this);
        if (context->param_list_tail()) {
            context->param_list_tail()->accept(this);
        }
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitRet_type(TigerParser::Ret_typeContext *context) {
    if (context->COLON()) {
        tokens.push_back(token("COLON", context->COLON()));
        context->type()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitParam(TigerParser::ParamContext *context) {
    tokens.push_back(token("ID", context->ID()));
    tokens.push_back(token("COLON", context->COLON()));
    context->type()->accept(this);
    return nullptr;
}

std::any TigerFileBaseVisitor::visitStat_seq(TigerParser::Stat_seqContext *context) {
    context->stat()->accept(this);
    if (context->stat_seq()) {
        context->stat_seq()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitValueAssign(TigerParser::ValueAssignContext *context) {
    context->value()->accept(this);
    tokens.push_back(token("ASSIGN", context->ASSIGN()));
    context->expr()->accept(this);
    tokens.push_back(token("SEMICOLON", context->SEMICOLON()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitIfThen(TigerParser::IfThenContext *context) {

}

std::any TigerFileBaseVisitor::visitIfThenElse(TigerParser::IfThenElseContext *context) {

}

std::any TigerFileBaseVisitor::visitWhile(TigerParser::WhileContext *context) {

}

std::any TigerFileBaseVisitor::visitFor(TigerParser::ForContext *context) {

}

std::any TigerFileBaseVisitor::visitOptAssign(TigerParser::OptAssignContext *context) {

}

std::any TigerFileBaseVisitor::visitBreak(TigerParser::BreakContext *context) {

}

std::any TigerFileBaseVisitor::visitReturn(TigerParser::ReturnContext *context) {
    tokens.push_back(token(context->RETURN()));
    context->optreturn()->accept(this);
    tokens.push_back(token("SEMICOLON", context->SEMICOLON()));
    return nullptr;
}

std::any TigerFileBaseVisitor::visitLet(TigerParser::LetContext *context) {

}

std::any TigerFileBaseVisitor::visitOptreturn(TigerParser::OptreturnContext *context) {
    if (context->expr()) {
        context->expr()->accept(this);
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitOptprefix(TigerParser::OptprefixContext *context) {

}

std::any TigerFileBaseVisitor::visitExpr(TigerParser::ExprContext *context) {
    if (context->const_()) {
        context->const_()->accept(this);
    }
    if (context->value()) {
        context->value()->accept(this);
    }
    if (context->binary_operator()) {
        context->expr(0)->accept(this);
        context->binary_operator()->accept(this);
        context->expr(1)->accept(this);
    }
    if (context->OPENPAREN()) {
        tokens.push_back(token("OPENPAREN", context->OPENPAREN()));
        context->expr(0)->accept(this);
        tokens.push_back(token("CLOSEPAREN", context->CLOSEPAREN()));
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitConst(TigerParser::ConstContext *context) {
    if (context->INTLIT()) {
        tokens.push_back(token("INTLIT", context->INTLIT()));
    }
    if (context->FLOATLIT()) {
        tokens.push_back(token("FLOATLIT", context->FLOATLIT()));
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitBinary_operator(TigerParser::Binary_operatorContext *context) {
    if (context->PLUS()) {
        tokens.push_back(token("PLUS", context->PLUS()));
    }
    if (context->MINUS()) {
        tokens.push_back(token("MINUS", context->MINUS()));
    }
    if (context->MULT()) {
        tokens.push_back(token("MULT", context->MULT()));
    }
    if (context->DIV()) {
        tokens.push_back(token("DIV", context->DIV()));
    }
    if (context->POW()) {
        tokens.push_back(token("POW", context->POW()));
    }
    if (context->EQUAL()) {
        tokens.push_back(token("EQUAL", context->EQUAL()));
    }
    if (context->NEQUAL()) {
        tokens.push_back(token("NEQUAL", context->NEQUAL()));
    }
    if (context->LESS()) {
        tokens.push_back(token("LESS", context->LESS()));
    }
    if (context->LESSEQ()) {
        tokens.push_back(token("LESSEQ", context->LESSEQ()));
    }
    if (context->GREAT()) {
        tokens.push_back(token("GREAT", context->GREAT()));
    }
    if (context->GREATEQ()) {
        tokens.push_back(token("GREATEQ", context->GREATEQ()));
    }
    if (context->OR()) {
        tokens.push_back(token("OR", context->OR()));
    }
    if (context->AND()) {
        tokens.push_back(token("AND", context->AND()));
    }
    return nullptr;
}

std::any TigerFileBaseVisitor::visitExpr_list(TigerParser::Expr_listContext *context) {

}

std::any TigerFileBaseVisitor::visitExpr_list_tail(TigerParser::Expr_list_tailContext *context) {

}

std::any TigerFileBaseVisitor::visitValue(TigerParser::ValueContext *context) {
    tokens.push_back(token("ID", context->ID()));
    context->value_tail()->accept(this);
    return nullptr;
}

std::any TigerFileBaseVisitor::visitValue_tail(TigerParser::Value_tailContext *context) {
    if (context->OPENBRACK()) {
        tokens.push_back(token("OPENBRACK", context->OPENBRACK()));
        context->value()->accept(this);
        tokens.push_back(token("CLOSEBRACK", context->CLOSEBRACK()));
    }
    return nullptr;
}
