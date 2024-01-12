//
//  PArgument.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef PArgument_hpp
#define PArgument_hpp

#include "PValue.hpp"

class PArgument: public PValue {
	
public:
	
	PArgument() { }
	
	Value* getLLVMValue(Compiler* compiler) override;
	
	ConstantValue* getConstantValue(Compiler* compiler) override;
	ConstantType* getConstantType(Compiler* compiler) override;
	
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PArgument_hpp */
