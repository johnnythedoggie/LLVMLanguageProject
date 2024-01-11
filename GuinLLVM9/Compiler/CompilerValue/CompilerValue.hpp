//
//  CompilerValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef CompilerValue_hpp
#define CompilerValue_hpp

#include "llvm.h"
#include "PVariance.hpp"

struct CompilerValue {
	PVariance variance;
	Value* llvmValue;
};

#endif /* CompilerValue_hpp */
