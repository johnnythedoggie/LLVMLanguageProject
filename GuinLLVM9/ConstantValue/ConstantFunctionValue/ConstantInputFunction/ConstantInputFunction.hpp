//
//  ConstantInputFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantInputFunction_hpp
#define ConstantInputFunction_hpp

#include "ConstantFunctionValue.hpp"
#include "ConstantVoidType.hpp"
#include "ConstantIntType.hpp"

class ConstantInputFunction: public ConstantFunctionValue {
	
	static Function* input;
	
	static void setup(Compiler* compiler);
	
public:
	
	ConstantInputFunction()
	 : ConstantFunctionValue("input", new ConstantVoidType(), new ConstantIntType()) { }
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* ConstantInputFunction_hpp */
