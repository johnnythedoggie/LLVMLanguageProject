//
//  CPureFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CPureFunction_hpp
#define CPureFunction_hpp

#include "CValue.hpp"
#include "CType.hpp"

class CPureFunction: public CValue {
	
public:
	
	virtual void makeBody(Compiler* compiler, Value* argument) = 0;
	
	Function* function = nullptr;
	
	static int globalIdentifier;
	
	int identifier;
	
	CType* inputType;
	CType* outputType;
	
	CPureFunction(CType* inputType, CType* outputType)
		: identifier(globalIdentifier++), inputType(inputType), outputType(outputType) { }
	
	CType* getConstantType() override;
	
	std::string identifierString() override;
	
	virtual void makeFunction(Compiler* compiler);
	
	Value* getLLVMValue(Compiler* compiler) override {
		if (!function) makeFunction(compiler);
		return function;
	}
	
};

#endif /* CPureFunction_hpp */
