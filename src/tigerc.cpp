#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "argparse/argparse.hpp"
#include "antlr4-runtime.h"
#include "TigerLexer.h"
#include "TigerParser.h"
#include "TigerFileBaseVisitor.h"
#include "TokenInfo.h"

namespace fs = std::filesystem;


int main(int argc, char** argv) {
    argparse::ArgumentParser program("tigerc");
    program.add_argument("-i")
        .required()
        .help("input file");
    program.add_argument("-l")
        .help("write stream of tokens to file")
        .default_value(false)
        .implicit_value(true);
    program.add_argument("-p")
        .help("write graph of parse tree to file")
        .default_value(false)
        .implicit_value(true);
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    const auto input_filename_str = program.get<std::string>("-i");
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
    antlr4::CommonTokenStream tokens(&lexer);

    if (program.get<bool>("-l")) {
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

    if (program.get<bool>("-p")) {
        TigerParser parser(&tokens);
        antlr4::tree::ParseTree *tree = parser.tiger_program();
        TigerFileBaseVisitor vis;
        try {
            const TokenInfo parseTree = std::any_cast<TokenInfo>(vis.visit(tree));
            auto dot_filename = input_filename;
            dot_filename.replace_extension(".tree.gv");
            std::ofstream dotfile(dot_filename);
            if (!dotfile.good()) {
                std::cerr << "cannot open file " << input_filename << std::endl;
                return 1;
            }
            dotfile << parseTree.graphviz() << std::endl;
            dotfile.close();
        } catch (TigerParseError e) {
            e.what();
            return 3;
        }
    }

    return 0;
}
