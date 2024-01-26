#include "llvm.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "Tokenizer.h"
#include "Parser.h"
#include "Compiler.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

/*
 
 Takes a source file as input, then outputs the resulting LLVM to the console.
 
 */
int main(int argc, char *argv[]) {
	
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}
	
	std::string filename = argv[1];
	
	std::ifstream file(filename);
	
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string file_contents = buffer.str();
	
	file.close();
	
	// Tokenize, Parse, and Compile
	
	std::queue<Token> tokens = Tokenizer::getTokensFrom(file_contents);
	std::queue<PStatement*> statements = Parser(tokens).parse();
	
	Compiler* compiler = new Compiler();
	
	while (!statements.empty()) {
		statements.front()->compile(compiler);
		statements.pop();
	}
	
	std::cout << "\n\n";
	
	compiler->close();
	
	compiler->llvmModule->print(outs(), nullptr);
	
	return 0;
	
}
