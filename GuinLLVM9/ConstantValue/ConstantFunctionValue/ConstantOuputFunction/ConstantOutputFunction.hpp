//
//  ConstantOutputFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantOutputFunction_hpp
#define ConstantOutputFunction_hpp

#include "ConstantFunctionValue.hpp"
#include "ConstantTupleType.hpp"
#include "ConstantIntType.hpp"

class ConstantOutputFunction: public ConstantFunctionValue {
	
public:
	
	Value* printfFormat = nullptr;
	
	ConstantOutputFunction()
	: ConstantFunctionValue(new ConstantIntType(), new ConstantTupleType({})) { }
	
	void makeFunction(Compiler* compiler) override;
	
	void makeBody(Compiler* compiler, Value* argument) override;
	
};

#endif /* ConstantOutputFunction_hpp */
