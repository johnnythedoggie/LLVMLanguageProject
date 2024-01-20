//
//  PFunctionType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef PFunctionType_hpp
#define PFunctionType_hpp

#include "PValue.hpp"

class PFunctionType: public PValue {
	
public:
	
	bool isPure;
	PValue* inputType;
	PValue* outputType;
	
	PFunctionType(bool isPure, PValue* inputType, PValue* outputType)
		: isPure(isPure), inputType(inputType), outputType(outputType) { }
	
	CValue* asConstantValue(Compiler* compiler) override;
	CType* getConstantType(Compiler* compiler) override;
	
	Value* asLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PFunctionType_hpp */
