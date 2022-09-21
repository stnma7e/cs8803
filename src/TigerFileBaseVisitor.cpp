#include <string>
#include <memory>
#include <iostream>
#include <ostream>

#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"
#include "TokenInfo.h"

antlrcpp::Any TigerFileBaseVisitor::visitTiger_program(TigerParser::Tiger_programContext *context) {
    return TokenInfo(context->PROGRAM(), TokenInfo::Children{
        std::make_shared<TokenInfo>("ID", context->ID()),
        std::make_shared<TokenInfo>(context->LET()),
        std::make_shared<TokenInfo>(context->decl_segment()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->BEGIN()),
        std::make_shared<TokenInfo>(context->funct_list()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->END()),
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitDecl_segment(TigerParser::Decl_segmentContext *context) {
    TokenInfo::Children children;

    if (context->type_decl_list()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->type_decl_list()->accept(this).as<TokenInfo>()
        ));
    }

    if (context->var_decl_list()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->var_decl_list()->accept(this).as<TokenInfo>()
        ));
    }

    return TokenInfo("decl_segment", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitType_decl_list(TigerParser::Type_decl_listContext *context) {
    TokenInfo::Children children;

    if (context->type_decl()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->type_decl()->accept(this).as<TokenInfo>()
        ));
    }

    if (context->type_decl_list()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->type_decl_list()->accept(this).as<TokenInfo>()
        ));
    }

    return TokenInfo("type_decl_list", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitVar_decl_list(TigerParser::Var_decl_listContext *context) {
    TokenInfo::Children children;

    if (context->var_decl()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->var_decl()->accept(this).as<TokenInfo>()
        ));
    }
    if (context->var_decl_list()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->var_decl_list()->accept(this).as<TokenInfo>()
        ));
    }

    return TokenInfo("var_decl_list", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitFunct_list(TigerParser::Funct_listContext *context) {
    TokenInfo::Children children;

    if (context->funct()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->funct()->accept(this).as<TokenInfo>()
        ));
    }
    if (context->funct_list()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->funct_list()->accept(this).as<TokenInfo>()
        ));
    }
    return TokenInfo("funct_list", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitType_decl(TigerParser::Type_declContext *context) {
    TokenInfo::Children children;

    return TokenInfo("type_decl", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->TYPE()),
        std::make_shared<TokenInfo>("ID: " + context->ID()->getText()),
        std::make_shared<TokenInfo>("TASSIGN", context->TASSIGN()),
        std::make_shared<TokenInfo>(context->type()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON()),
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitType(TigerParser::TypeContext *context) {
    TokenInfo::Children children;

    //TODO how do I select only one of these?
    if (context->ARRAY()) {
        //TODO fix this syntax with spaces around bracks
        children.push_back(std::make_shared<TokenInfo>(context->ARRAY()));
        children.push_back(std::make_shared<TokenInfo>("OPENBRACK", context->OPENBRACK()));
        children.push_back(std::make_shared<TokenInfo>("INTLIT: " + context->INTLIT()->getText()));
        children.push_back(std::make_shared<TokenInfo>("CLOSEBRACK", context->CLOSEBRACK()));
        children.push_back(std::make_shared<TokenInfo>(context->OF()));
        children.push_back(std::make_shared<TokenInfo>(
            context->base_type()->accept(this).as<TokenInfo>()
        ));
    } else if (context->base_type()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->base_type()->accept(this).as<TokenInfo>()
        ));
    }
    if (context->ID()) {
        children.push_back(std::make_shared<TokenInfo>("ID: " + context->ID()->getText()));
    }

    return TokenInfo("type", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitBase_type(TigerParser::Base_typeContext *context) {
    //TODO make this a split type
    if (context->INT()) {
        return TokenInfo("base_type: " + context->INT()->getText());
    }
    if (context->FLOAT()) {
        return TokenInfo("base_type: " + context->FLOAT()->getText());
    }
    return nullptr;
}

antlrcpp::Any TigerFileBaseVisitor::visitVar_decl(TigerParser::Var_declContext *context) {
    return TokenInfo("var_decl", std::move(TokenInfo::Children{
        std::make_shared<TokenInfo>(context->storage_class()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->id_list()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("COLON", context->COLON()),
        std::make_shared<TokenInfo>(context->type()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->optional_init()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON()),
    }));
}

antlrcpp::Any TigerFileBaseVisitor::visitStorage_class(TigerParser::Storage_classContext *context) {
    if (context->VAR()) {
        return TokenInfo("storage_class: " + context->VAR()->getText());
    }
    if (context->STATIC()) {
        return TokenInfo("storage_class: " + context->STATIC()->getText());
    }
}

antlrcpp::Any TigerFileBaseVisitor::visitId_list(TigerParser::Id_listContext *context) {
    TokenInfo::Children children;

    if (context->ID()) {
        children.push_back(std::make_shared<TokenInfo>("ID: " + context->ID()->getText()));
    }
    if (context->COMMA()) {
        children.push_back(std::make_shared<TokenInfo>("COMMA", context->COMMA()));
    }
    if (context->id_list()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->id_list()->accept(this).as<TokenInfo>()
        ));
    }
    return TokenInfo("id_list", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitOptional_init(TigerParser::Optional_initContext *context) {
    TokenInfo::Children children;

    if (context->ASSIGN()) {
        children.push_back(std::make_shared<TokenInfo>("ASSIGN", context->ASSIGN()));
        children.push_back(std::make_shared<TokenInfo>(context->constt()->accept(this).as<TokenInfo>()));
    }

    return TokenInfo("optional_init", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitFunct(TigerParser::FunctContext *context) {
    return TokenInfo("funct", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->FUNCTION()),
        std::make_shared<TokenInfo>("ID: " + context->ID()->getText()),
        std::make_shared<TokenInfo>("OPENPAREN", context->OPENPAREN()),
        std::make_shared<TokenInfo>(context->param_list()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("CLOSEPAREN", context->CLOSEPAREN()),
        std::make_shared<TokenInfo>(context->ret_type()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->BEGIN()),
        std::make_shared<TokenInfo>(context->stat_seq()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->END()),
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitParam_list(TigerParser::Param_listContext *context) {
    TokenInfo::Children children;

    if (context->param()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->param()->accept(this).as<TokenInfo>()
        ));
    }
    if (context->param_list_tail()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->param_list_tail()->accept(this).as<TokenInfo>()
        ));
    }

    return TokenInfo("param_list", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitParam_list_tail(TigerParser::Param_list_tailContext *context) {
    if (context->COMMA()) {
        if (context->param_list_tail()) {
            context->param_list_tail()->accept(this);
        }
    }
    return TokenInfo();
}

antlrcpp::Any TigerFileBaseVisitor::visitRet_type(TigerParser::Ret_typeContext *context) {
    if (context->COLON()) {
        return TokenInfo("return", TokenInfo::Children{
            std::make_shared<TokenInfo>("COLON", context->COLON()),
            std::make_shared<TokenInfo>(context->type()->accept(this).as<TokenInfo>()),
        });
    }
    return TokenInfo("ret_type: void");
}

antlrcpp::Any TigerFileBaseVisitor::visitParam(TigerParser::ParamContext *context) {
    return TokenInfo("param", TokenInfo::Children{
        std::make_shared<TokenInfo>("ID: " + context->ID()->getText()),
        std::make_shared<TokenInfo>("COLON", context->COLON()),
        std::make_shared<TokenInfo>(context->type()->accept(this).as<TokenInfo>()),
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitStat_seq(TigerParser::Stat_seqContext *context) {
    TokenInfo::Children children;

    children.push_back(std::make_shared<TokenInfo>(
        context->stat()->accept(this).as<TokenInfo>()
    ));

    if (context->stat_seq()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->stat_seq()->accept(this).as<TokenInfo>()
        ));
    }

    return TokenInfo("stat_seq", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitValueAssign(TigerParser::ValueAssignContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->value()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("ASSIGN", context->ASSIGN()),
        std::make_shared<TokenInfo>(context->expr()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitIfThen(TigerParser::IfThenContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->IF()),
        std::make_shared<TokenInfo>(context->expr()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->THEN()),
        std::make_shared<TokenInfo>(context->stat_seq()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->ENDIF()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitIfThenElse(TigerParser::IfThenElseContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->IF()),
        std::make_shared<TokenInfo>(context->expr()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->THEN()),
        std::make_shared<TokenInfo>(context->stat_seq(0)->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->ELSE()),
        std::make_shared<TokenInfo>(context->stat_seq(1)->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->ENDIF()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitWhile(TigerParser::WhileContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->WHILE()),
        std::make_shared<TokenInfo>(context->expr()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->DO()),
        std::make_shared<TokenInfo>(context->stat_seq()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->ENDDO()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitFor(TigerParser::ForContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->FOR()),
        std::make_shared<TokenInfo>("ID: " + context->ID()->getText()),
        std::make_shared<TokenInfo>("ASSIGN: " + context->ASSIGN()->getText()),
        std::make_shared<TokenInfo>(context->expr(0)->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->TO()),
        std::make_shared<TokenInfo>(context->expr(1)->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->DO()),
        std::make_shared<TokenInfo>(context->stat_seq()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->ENDDO()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitFunctCall(TigerParser::FunctCallContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->optprefix()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("ID: " + context->ID()->getText()),
        std::make_shared<TokenInfo>("OPENPAREN: " + context->OPENPAREN()->getText()),
        std::make_shared<TokenInfo>(context->expr_list()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("CLOSEPAREN: " + context->CLOSEPAREN()->getText()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitBreak(TigerParser::BreakContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->BREAK()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitReturn(TigerParser::ReturnContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->RETURN()),
        std::make_shared<TokenInfo>(context->optreturn()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>("SEMICOLON", context->SEMICOLON())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitLet(TigerParser::LetContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>(context->LET()),
        std::make_shared<TokenInfo>(context->decl_segment()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->BEGIN()),
        std::make_shared<TokenInfo>(context->stat_seq()->accept(this).as<TokenInfo>()),
        std::make_shared<TokenInfo>(context->END())
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitOptreturn(TigerParser::OptreturnContext *context) {
    TokenInfo::Children children;

    if (context->expr()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->expr()->accept(this).as<TokenInfo>()
        ));
    }

    return TokenInfo("optreturn", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitOptprefix(TigerParser::OptprefixContext *context) {
    TokenInfo::Children children;

    if (context->value()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->value()->accept(this).as<TokenInfo>()
        ));
        children.push_back(std::make_shared<TokenInfo>("ASSIGN", context->ASSIGN()));
    }

    return TokenInfo("optprefix", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitExpr(TigerParser::ExprContext *context) {
    TokenInfo::Children children;

    if (context->constt()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->constt()->accept(this).as<TokenInfo>()
        ));
    }
    if (context->value()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->value()->accept(this).as<TokenInfo>()
        ));
    }
    if (context->binary_operator()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->expr(0)->accept(this).as<TokenInfo>()
        ));
        children.push_back(std::make_shared<TokenInfo>(
            context->binary_operator()->accept(this).as<TokenInfo>()
        ));
        children.push_back(std::make_shared<TokenInfo>(
            context->expr(1)->accept(this).as<TokenInfo>()
        ));
    }
    if (context->OPENPAREN()) {
        children.push_back(std::make_shared<TokenInfo>("OPENPAREN", context->OPENPAREN()));
        children.push_back(std::make_shared<TokenInfo>(
            context->expr(0)->accept(this).as<TokenInfo>()
        ));
        children.push_back(std::make_shared<TokenInfo>("CLOSEPAREN", context->CLOSEPAREN()));
    }

    return TokenInfo("expr", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitConstt(TigerParser::ConsttContext *context) {
    if (context->INTLIT()) {
        return TokenInfo("const: " + context->INTLIT()->getText());
    }
    if (context->FLOATLIT()) {
        return TokenInfo("const: " + context->FLOATLIT()->getText());
    }
    return nullptr;
}

antlrcpp::Any TigerFileBaseVisitor::visitBinary_operator(TigerParser::Binary_operatorContext *context) {
    if (context->PLUS()) {
        return TokenInfo("binary_operator: " + context->PLUS()->getText());
    }
    if (context->MINUS()) {
        return TokenInfo("binary_operator: " + context->MINUS()->getText());
    }
    if (context->MULT()) {
        return TokenInfo("binary_operator: " + context->MULT()->getText());
    }
    if (context->DIV()) {
        return TokenInfo("binary_operator: " + context->DIV()->getText());
    }
    if (context->POW()) {
        return TokenInfo("binary_operator: " + context->POW()->getText());
    }
    if (context->EQUAL()) {
        return TokenInfo("binary_operator: " + context->EQUAL()->getText());
    }
    if (context->NEQUAL()) {
        return TokenInfo("binary_operator: " + context->NEQUAL()->getText());
    }
    if (context->LESS()) {
        return TokenInfo("binary_operator: " + context->LESS()->getText());
    }
    if (context->LESSEQ()) {
        return TokenInfo("binary_operator: " + context->LESSEQ()->getText());
    }
    if (context->GREAT()) {
        return TokenInfo("binary_operator: " + context->GREAT()->getText());
    }
    if (context->GREATEQ()) {
        return TokenInfo("binary_operator: " + context->GREATEQ()->getText());
    }
    if (context->OR()) {
        return TokenInfo("binary_operator: " + context->OR()->getText());
    }
    if (context->AND()) {
        return TokenInfo("binary_operator: " + context->AND()->getText());
    }
    return nullptr;
}

antlrcpp::Any TigerFileBaseVisitor::visitExpr_list(TigerParser::Expr_listContext *context) {
    TokenInfo::Children children;

    if (context->expr()) {
        children.push_back(std::make_shared<TokenInfo>(
            context->expr()->accept(this).as<TokenInfo>()
        ));
        children.push_back(std::make_shared<TokenInfo>(
            context->expr_list_tail()->accept(this).as<TokenInfo>()
        ));
    }
    return TokenInfo("expr_list", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitExpr_list_tail(TigerParser::Expr_list_tailContext *context) {
    TokenInfo::Children children;

    if (context->COMMA()) {
        children.push_back(std::make_shared<TokenInfo>("COMMA", context->COMMA()));
        children.push_back(std::make_shared<TokenInfo>(
            context->expr()->accept(this).as<TokenInfo>()
        ));
        children.push_back(std::make_shared<TokenInfo>(
            context->expr_list_tail()->accept(this).as<TokenInfo>()
        ));
    }

    return TokenInfo("expr_list_tail", std::move(children));
}

antlrcpp::Any TigerFileBaseVisitor::visitValue(TigerParser::ValueContext *context) {
    return TokenInfo("stat", TokenInfo::Children{
        std::make_shared<TokenInfo>("ID: " + context->ID()->getText()),
        std::make_shared<TokenInfo>(context->value_tail()->accept(this).as<TokenInfo>()),
    });
}

antlrcpp::Any TigerFileBaseVisitor::visitValue_tail(TigerParser::Value_tailContext *context) {
    TokenInfo::Children children;

    if (context->OPENBRACK()) {
        children.push_back(std::make_shared<TokenInfo>("OPENBRACK", context->OPENBRACK()));
        children.push_back(std::make_shared<TokenInfo>(
            context->value()->accept(this).as<TokenInfo>()
        ));
        children.push_back(std::make_shared<TokenInfo>("CLOSEBRACK", context->CLOSEBRACK()));
    }
    return TokenInfo("value_tail", std::move(children));
}

void TigerLexErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) {
    throw TigerError(true);
}

void TigerParseErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) {
    throw TigerError(false);
}
