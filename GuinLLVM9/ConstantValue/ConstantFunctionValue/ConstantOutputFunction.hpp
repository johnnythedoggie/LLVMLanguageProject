//
//  ConstantOutputFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantOutputFunction_hpp
#define ConstantOutputFunction_hpp


#include "ConstantFunctionValue.hpp"
#include "ConstantVoidType.hpp"
#include "ConstantIntType.hpp"

class ConstantOutputFunction: public ConstantFunctionValue {
	
	static Function* output;
	
	static void setup(Compiler* compiler);
	
public:
	
	ConstantOutputFunction()
	: ConstantFunctionValue("output", new ConstantIntType(), new ConstantVoidType()) { }
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};


#endif /* ConstantOutputFunction_hpp */
