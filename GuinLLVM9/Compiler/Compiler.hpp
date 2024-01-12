//
//  Compiler.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef Compiler_h
#define Compiler_h

#include "llvm.h"
#include "CompilerValue.hpp"
#include "Scope.hpp"

class Compiler {
	
	Function* mainFunction = nullptr;
	
public:
	
	LLVMContext* llvmContext;
	Module* llvmModule;
	IRBuilder<>* llvmBuilder;
	
	std::map<std::string, CompilerValue*> valueForIdentifier;
	Scope scope;
	
	
	void close();
	Compiler();
	
};


#endif /* Compiler_h */
