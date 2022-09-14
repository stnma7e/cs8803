#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "antlr4-runtime.h"
#include "TigerLexer.h"
#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"

using std::cout;
using std::endl;

int print_usage(const char *program_name) {
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
    TigerParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.tiger_program();

    TigerFileBaseVisitor vis;
    vis.visit(tree);

    for (const auto t : vis.getTokens()) {
        cout << "<" << t.first <<  ", \"" << t.second << "\">" << endl;
    }

    return 0;
}
