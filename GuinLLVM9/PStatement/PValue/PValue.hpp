//
//  PValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PValue_hpp
#define PValue_hpp

#include "PStatement.hpp"

class PValue: public PStatement {
	
public:
	
	virtual Value* getLLVMValue(Compiler* compiler) = 0;
	virtual PVariance getVariance(Compiler* compiler) = 0;
	
	// virtual void compile(Compiler* compiler) = 0;
	
};

#endif /* PValue_hpp */
