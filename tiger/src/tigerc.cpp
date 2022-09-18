#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "antlr4-runtime.h"
#include "TigerLexer.h"
#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"
#include "TokenInfo.h"

using std::cout;
using std::endl;

void print_usage(const char *program_name) {
    printf("USAGE: %s -i <input file>\n", program_name);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    const auto input_filename = argv[1];
    cout << "parsing \"" << input_filename << "\"" << endl;

    std::ifstream stream;
    stream.open(input_filename);
    antlr4::ANTLRInputStream input(stream);
    TigerLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens.get(i) << endl;
    }
    cout << tokens.getText() << endl;
    TigerParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.tiger_program();

    TigerFileBaseVisitor vis;
    const TokenInfo program = std::any_cast<TokenInfo>(vis.visit(tree));

    std::ofstream dotfile("graph.dot");
    dotfile << program.graphviz();
    dotfile.close();

    return 0;
}
