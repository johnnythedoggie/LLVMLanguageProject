//
//  PStatement.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PStatement_hpp
#define PStatement_hpp

#include "Tokenizer.h"
#include <queue>
#include "Compiler.hpp"

class PStatement {
	
public:
	
	virtual void compile(Compiler* compiler) = 0;
	
};

#endif /* PStatement_hpp */
