#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

#include "antlr4-runtime.h"
#include "TigerLexer.h"
#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"
#include "TokenInfo.h"

namespace fs = std::experimental::filesystem;

void print_usage() {
    std::cout << "USAGE: tigerc -i <input tiger file> [-l] [-p]" << std::endl;
}

int main(int argc, const char *argv[]) {
    const char *input_filename_str = nullptr;
    bool write_lex = false, write_parse = false;

    if (argc < 3) {
        print_usage();
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp("-i", argv[i]) == 0) {
            if (i + 1 < argc) {
                input_filename_str = argv[i+1];
                i += 1;
            } else {
                print_usage();
                return 1;
            }
        } else if (strcmp("-l", argv[i]) == 0) {
            write_lex = true;
        } else if (strcmp("-p", argv[i]) == 0) {
            write_parse = true;
        } else {
            print_usage();
            return 1;
        }
    }

    if (!input_filename_str) {
        print_usage();
        return 1;
    }

    const auto input_filename = fs::path(input_filename_str);
    std::cout << "parsing " << input_filename << std::endl;

    std::ifstream stream;
    stream.open(input_filename);
    if (!stream.good()) {
        std::cerr << "cannot open file " << input_filename << std::endl;
        return 1;
    }

    antlr4::ANTLRInputStream input(stream);
    stream.close();

    TigerLexer lexer(&input);
    TigerLexErrorListener lexErrorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&lexErrorListener);

    try {
        antlr4::CommonTokenStream tokens(&lexer);

        TigerParser parser(&tokens);
        TigerParseErrorListener parseErrorListener;
        parser.removeErrorListeners();
        parser.addErrorListener(&parseErrorListener);

        antlr4::tree::ParseTree *tree = parser.tiger_program();
        TigerFileBaseVisitor vis;

        const TokenInfo parseTree = vis.visit(tree).as<TokenInfo>();

        if (write_lex) {
            tokens.fill();
            const auto vocab = lexer.getVocabulary();

            auto token_filename = input_filename;
            token_filename.replace_extension(".tokens");
            std::ofstream tokenFile(token_filename);

            for (auto token : tokens.getTokens()) {
                tokenFile << "<"
                        << vocab.getSymbolicName(token->getType())
                        << ", "
                        << token->getText()
                        << ">"
                        << std::endl;
            }

            tokenFile.close();
        }

        if (write_parse) {
            auto dot_filename = input_filename;
            dot_filename.replace_extension(".tree.gv");
            std::ofstream dotfile(dot_filename);
            if (!dotfile.good()) {
                std::cerr << "cannot open file " << input_filename << std::endl;
                return 1;
            }
            dotfile << parseTree.graphviz() << std::endl;
            dotfile.close();
        }

    } catch (TigerError e) {
        std::cerr << e.what() << std::endl;
        if (e.isLex()) {
            return 2;
        }
        return 3;
    }

    return 0;
}
