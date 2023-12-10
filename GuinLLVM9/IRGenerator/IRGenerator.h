//
//  IRGenerator.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef IRGenerator_h
#define IRGenerator_h

#include "llvm.h"
#include "Parser.h"
#include <memory>

class IRGenerator {
	
	void generate(std::queue<GStatement*> statements);
	
public:
	
	LLVMContext* llvmContext;
	Module* llvmModule;
	IRBuilder<>* llvmBuilder;
	
	std::map<std::string, Value*> identifierToValueMap;
	
	IRGenerator(std::queue<GStatement*> statements);
	
};

#endif /* IRGenerator_h */
