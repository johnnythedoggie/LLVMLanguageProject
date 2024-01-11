//
//  Compiler.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef IRGenerator_h
#define IRGenerator_h

#include "llvm.h"
#include <memory>

class Compiler {
	
	Function* mainFunction = nullptr;
	
public:
	
	void close();
	
	LLVMContext* llvmContext;
	Module* llvmModule;
	IRBuilder<>* llvmBuilder;
	
	std::map<std::string, Value*> valueForIdentifier = {};
	
	Compiler();
	
};

#endif /* IRGenerator_h */
