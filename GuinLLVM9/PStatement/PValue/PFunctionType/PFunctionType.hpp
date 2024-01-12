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
	
	PValue* inputType;
	PValue* outputType;
	
	PFunctionType(PValue* inputType, PValue* outputType)
		: inputType(inputType), outputType(outputType) { }
	
	ConstantValue* getConstantValue(Compiler* compiler) override;
	ConstantType* getConstantType(Compiler* compiler) override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PFunctionType_hpp */
