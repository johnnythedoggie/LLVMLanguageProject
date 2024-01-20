//
//  Scope.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef Scope_hpp
#define Scope_hpp

#include "llvm.h"
#include "CompilerValue.hpp"

class Compiler;

struct Scope {
	
	CType* argumentType = nullptr;
	CType* returnType = nullptr;
	Value* argument = nullptr;
	
	Value* captureArgument = nullptr;
	
	IRBuilder<>::InsertPoint parentInsertPoint;
	
	std::map<std::string, CompilerValue*> scopedIdentifierToValue = {};
	
	bool isPureScope = true;
	
	int numCapturedValues = 0;
	
	std::vector<CompilerValue*> capturedValues = {};
	
	
	
	std::map<std::string, CompilerValue*> capturedIdentifierToValue = {};
	
	Scope* parentScope = nullptr;
	
	CompilerValue* valueForIdentifier(Compiler* compiler, std::string id);
	
};

#endif /* Scope_hpp */
