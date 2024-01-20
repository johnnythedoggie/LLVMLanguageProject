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

// #include <fstream>
// I don't understand why fstream doesn't work
// I want to get input from a file but I cannot.

int main(int argc, char* argv[]) {
	
	std::string input = R"(
  
const call = pure (impure Void -> Void) -> Void {
 $()
 return ()
}

const if = pure Bool -> (pure (impure Void -> Void) -> Void) {
 return call
}



var x = 0

(if true) (impure Void -> Void {
 
 x = input()
 
 return()
 
})

output(x)

  
)";
	
	auto tokens = Tokenizer::getTokensFrom(input);
	
	auto statements = Parser().parse(tokens);
	
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
