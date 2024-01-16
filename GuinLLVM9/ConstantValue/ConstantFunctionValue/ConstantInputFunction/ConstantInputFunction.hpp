//
//  ConstantInputFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantInputFunction_hpp
#define ConstantInputFunction_hpp

#include "ConstantFunctionValue.hpp"
#include "ConstantTupleType.hpp"
#include "ConstantIntType.hpp"

class ConstantInputFunction: public ConstantFunctionValue {
	
public:
	
	Value* scanfFormat = nullptr;
	
	ConstantInputFunction()
	: ConstantFunctionValue(new ConstantTupleType({}), new ConstantIntType()) { }
	
	void makeFunction(Compiler* compiler) override;
	
	void makeBody(Compiler* compiler, Value* argument) override;
	
};

#endif /* ConstantInputFunction_hpp */
