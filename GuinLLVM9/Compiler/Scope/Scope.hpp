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

class Scope {
	
public:
	
	ConstantType* argumentType = nullptr;
	ConstantType* returnType = nullptr;
	Value* argument = nullptr;
	// maybe more stuff to access out of scope identifiers
	
};

#endif /* Scope_hpp */
