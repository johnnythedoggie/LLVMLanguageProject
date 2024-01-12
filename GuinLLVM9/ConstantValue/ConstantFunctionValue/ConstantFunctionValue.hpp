//
//  ConstantFunctionValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantFunctionValue_hpp
#define ConstantFunctionValue_hpp

#include "ConstantValue.hpp"
#include "ConstantType.hpp"

class ConstantFunctionValue: public ConstantValue {
	
public:
	
	static int globalIdentifier;
	
	int identifier;
	
	ConstantType* inputType;
	ConstantType* outputType;
	
	ConstantFunctionValue(ConstantType* inputType, ConstantType* outputType)
		: identifier(globalIdentifier++), inputType(inputType), outputType(outputType) { }
	
	ConstantType* getConstantType() override;
	
	std::string identifierString() override;
	
	// Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* ConstantFunctionValue_hpp */
