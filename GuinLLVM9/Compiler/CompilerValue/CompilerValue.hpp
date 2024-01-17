//
//  CompilerValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef CompilerValue_hpp
#define CompilerValue_hpp

// #include "PValue.hpp"
#include "llvm.h"
#include "PVariance.hpp"

// I really don't understand what's going on, this fixes it though.
class CValue; // #include "CValue.hpp"
class CType; // #include "CType.hpp"

struct CompilerValue {
	
	PVariance variance;
	CType* constantType = nullptr;
	
	Value* dynamicValueLocation = nullptr; // VAR
	Value* staticValue = nullptr; // LET
	CValue* constantValue = nullptr; // CONST
	
};

#endif /* CompilerValue_hpp */

