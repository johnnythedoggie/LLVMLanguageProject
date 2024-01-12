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

int main() {
	
	auto tokens = Tokenizer::getTokensFrom(R"(
		let callThreeTimes = ((Void -> Void) -> Void) {
			$ void
			$ void
			$ void
		}
		callThreeTimes ((Void -> Void) {
			output (input void)
		})
	)");
	
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
