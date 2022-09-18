#ifndef TOKENINFO_H_
#define TOKENINFO_H_

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "TigerParser.h"

struct TokenInfo {
    struct GraphPrinter {
        std::stringstream output_ss;
        int node_counter = 0;

        std::string print_rec(const TokenInfo& ti);
    public:
        std::string print(const TokenInfo& ti);
    };

    typedef std::vector<std::shared_ptr<TokenInfo>> Children;

    TokenInfo(antlr4::tree::TerminalNode *node, TokenInfo::Children&& children)
        : token_type(node->getText()),
          node(node),
          children(children)
    {}

    TokenInfo(const std::string &token_type, TokenInfo::Children&& children)
        : token_type(token_type),
          children(children)
    {}

    TokenInfo(const std::string& token_type, antlr4::tree::TerminalNode *node)
        : token_type(token_type),
          node(node)
    {}

    TokenInfo(antlr4::tree::TerminalNode *node)
        : token_type(node->getText()),
          node(node)
    {}

    TokenInfo(std::string token_type)
        : token_type(token_type)
    {}

    TokenInfo() {}

    const std::string graphviz() const;

    const std::string token_type;
    antlr4::tree::TerminalNode *node;
    const Children children;
};


#endif // TOKENINFO_H_
