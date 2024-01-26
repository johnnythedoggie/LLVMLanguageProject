//
//  PFunctionCall.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef PFunctionCall_hpp
#define PFunctionCall_hpp

#include "PValue.hpp"

/*
 
 `Function Call` refers to one of three things:
	1. A call to a pure function
	2. A call to an impure function
	3. A type specification of a function
 
 It is all things that are parsed as "value value"
 
 */
class PFunctionCall: public PValue {
	
	Value* valueAsPureFunctionCall(Compiler* compiler);
	Value* valueAsImpureFunctionCall(Compiler* compiler);
	Value* valueAsFunctionTypeSpecification(Compiler* compiler);
	
public:
	
	PValue* firstValue;
	PValue* secondValue;
	
	PFunctionCall(PValue* firstValue, PValue* secondValue)
	: firstValue(firstValue), secondValue(secondValue) { }
	
	CValue* asConstantValue(Compiler* compiler) override;
	CType* getConstantType(Compiler* compiler) override;
	
	Value* asLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PFunctionCall_hpp */
