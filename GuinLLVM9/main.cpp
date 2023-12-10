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

#include "IRGenerator.h"

int main() {
	
	auto tokens = Tokenizer::getTokensFrom(R"(
		const A: Type = Int
		const B: Type = Bool
		const C: Type = pure A -> B
	)");
	auto statements = Parser().getStatementsFrom(tokens);
	
	while (!statements.empty()) {
		std::cout << statements.front()->description() << ";\n";
		statements.pop();
	}
	
	std::cout << "\n\n";
	
	IRGenerator compiler = IRGenerator(statements);
	
	/*
	auto entryBlock = BasicBlock::Create(*myContext, "entry", function);
	myBuilder->SetInsertPoint(entryBlock);
	
	Value* tmp = myBuilder->CreateBinOp(Instruction::Mul, function->arg_begin(), ConstantFP::get(*myContext, APFloat((double)3.45)), "tmp");
	
	Value* tmp2 = myBuilder->CreateBinOp(Instruction::Mul, tmp, tmp, "tmp2");
	
	myBuilder->CreateRet(tmp2);
	
	verifyFunction(*function);
	
	function->print(errs());
	*/
	
	return 0;
	
}
