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
	
	virtual void makeBody(Compiler* compiler, Value* argument) = 0;
	
	Function* function = nullptr;
	
	static int globalIdentifier;
	
	int identifier;
	
	ConstantType* inputType;
	ConstantType* outputType;
	
	ConstantFunctionValue(ConstantType* inputType, ConstantType* outputType)
		: identifier(globalIdentifier++), inputType(inputType), outputType(outputType) { }
	
	ConstantType* getConstantType() override;
	
	std::string identifierString() override;
	
	virtual void makeFunction(Compiler* compiler);
	
	Value* getLLVMValue(Compiler* compiler) override {
		if (!function) makeFunction(compiler);
		return function;
	}
	
};

#endif /* ConstantFunctionValue_hpp */
