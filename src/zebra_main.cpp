#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <iterator>

#include "ast/tree/fLangAstVisitor.hpp"
#include "lex/fTokzr.hpp"
#include "lex/fReader.hpp"
#include "lex/fLexerImpl.hpp"
#include "parse/fParser.hpp"

static constexpr const char* ROOT = PROJECT_ROOT;




void run_compiler(const std::string& filepath) {
	std::ifstream f(filepath);
	if (!f) throw std::runtime_error("failed to open file: " + filepath);
	std::string text(std::istreambuf_iterator<char>(f), {});
	std::cout << text;
	std::cout << "--- " << '\n';
	zebra::lex::fReader reader(text);
	zebra::lex::util::fTBuffer tBuffer;
	zebra::lex::fTokzr tokenizer(reader, tBuffer);
	zebra::lex::fLexerImpl lexImpl(tokenizer);
	zebra::parse::fParser parser(lexImpl);
	zebra::util::sp<zebra::ast::leaf::fCompileUnit> cu = parser.compileUnit();

	using zebra::ast::node::fLangAstVisitor;

	zebra::util::sp<fLangAstVisitor> visitor = zebra::util::ms<fLangAstVisitor>(cu);
	visitor->visit();
}

int main(int argc, char *argv[]) {
	try {

		if (argc == 1) {
			std::cerr <<"Error: No input file provided. "<< '\n';
			return 1;
		}

		std::string filepath =  std::string(ROOT) + "/resources/" + argv[1];
		std::cout << "Compiling file: " << filepath << '\n';
		run_compiler(filepath);

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	std::cout << "--- Exiting normally ... " << '\n';
	return 0;
}