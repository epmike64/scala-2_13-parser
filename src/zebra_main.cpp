#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <iterator>

#include "../include/ast/symbol/XVisitor.hpp"
#include "back/tree/ZVisitor.hpp"
#include "lex/fTokzr.hpp"
#include "lex/fReader.hpp"
#include "lex/fLexerImpl.hpp"
#include "parse/fParser.hpp"

static constexpr const char* ROOT = PROJECT_ROOT;


using namespace zebra::util;


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

	using zebra::back::tree::ZVisitor;

	zebra::util::sp<ZVisitor> zVisitor = zebra::util::ms<ZVisitor>(cu);
	zVisitor->visit();
	std::cout << "--- Z Visitor: Done normally ... " << '\n';
	sp<zebra::ast::XVisitor> xVisitor = zebra::util::ms<zebra::ast::XVisitor>(zVisitor->getZProgram());
	xVisitor->visit();
	std::cout << "--- X Visitor: Done normally ... " << '\n';
}

int main(int argc, char *argv[]) {
	try {

		if (argc == 1) {
			std::filesystem::path resourcesDir = std::filesystem::path(ROOT) / "resources";
			std::cout << "No file specified. Compiling all files in: " << resourcesDir << '\n';
			for (const auto& entry : std::filesystem::directory_iterator(resourcesDir)) {
				if (entry.is_regular_file()) {
					std::cout << "\n=== Compiling: " << entry.path().filename().string() << " ===\n";
					run_compiler(entry.path().string());
				}
			}
		} else {
			std::string filepath = std::string(ROOT) + "/resources/" + argv[1];
			std::cout << "Compiling file: " << filepath << '\n';
			run_compiler(filepath);
		}

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	std::cout << "--- WHOLE PROGRAM: Exiting normally ... " << '\n';
	return 0;
}