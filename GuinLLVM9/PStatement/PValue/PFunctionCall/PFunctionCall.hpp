//
//  PFunctionCall.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef PFunctionCall_hpp
#define PFunctionCall_hpp

#include "PValue.hpp"

class PFunctionCall: public PValue {
	
public:
	
	PValue* functionValue;
	PValue* argumentValue;
	
	PFunctionCall(PValue* functionValue, PValue* argumentValue)
	: functionValue(functionValue), argumentValue(argumentValue) { }
	
	ConstantValue* asConstantValue(Compiler* compiler) override;
	ConstantType* getConstantType(Compiler* compiler) override;
	
	Value* asLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PFunctionCall_hpp */
