//
//  ConstantUserDefinedFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef ConstantUserDefinedFunction_hpp
#define ConstantUserDefinedFunction_hpp

#include "ConstantFunctionValue.hpp"
#include "ConstantVoidType.hpp"
#include "PValue.hpp"
#include <queue>

class ConstantUserDefinedFunction: public ConstantFunctionValue {
	
	Function* function = nullptr;
	
	void setup(Compiler* compiler);
	
public:
	
	std::queue<PStatement*> statements;
	
	ConstantUserDefinedFunction(
		std::queue<PStatement*> statements,
		ConstantType* inputType,
		ConstantType* outputType
	): statements(statements), ConstantFunctionValue(inputType, outputType) { }
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* ConstantUserDefinedFunction_hpp */
