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

/*
 
 Way better error handleing
 
 Unnamed tuple elements if type can be innfered
 Left associative function calls
 
 sum(a, b)
 difference(a, b)
 areEqual(a, b)
 
 and(a, b)
 or(a, b)
 not(a)
 
 
 */



int main(int argc, char* argv[]) {
	
	std::string input = R"(

const IfReturnType = pure (impure Void -> Void) -> Void

const call = IfReturnType {
	$()
	return ()
}
const ignore = IfReturnType {
	return ()
}

const if = pure Bool -> IfReturnType {
	return #select($, call, ignore)
}



var x = 0

(if true) (impure Void -> Void {
	x = input()
	return ()
})

output(x)

let x = (a = 4, b = false)

let f = pure (a: Int, b: Bool) -> Int {
	return #select($.b, $.a, 0)
}

output(f(x))

  
)";
	
	auto tokens = Tokenizer::getTokensFrom(input);
	
	auto statements = Parser(tokens).parse();
	
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
