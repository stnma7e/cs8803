#include "TokenInfo.h"

#include <sstream>

const std::string TokenInfo::graphviz() const {
    TokenInfo::GraphPrinter gp;
    std::stringstream ss;
    ss << "digraph {" << std::endl;
    ss << gp.print(*this);
    ss << "}" << std::endl;
    return ss.str();
}

std::string TokenInfo::GraphPrinter::print(const TokenInfo& ti) {
    print_rec(ti);
    return this->output_ss.str();
}

std::string TokenInfo::GraphPrinter::print_rec(const TokenInfo& ti) {
    const auto node_id = "node" + std::to_string(this->node_counter++);
    const auto node_label = ti.token_type ;

    this->output_ss << node_id << " [label=\"" << node_label << "\"]" << std::endl;

    for (const auto c : ti.children) {
        const auto child_id = print_rec(*c);
        this->output_ss << node_id << " -> " << child_id << std::endl;
    }

    return node_id;
}
