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
	
public:
	
	std::queue<PStatement*> statements;
	
	ConstantUserDefinedFunction(
		std::queue<PStatement*> statements,
		ConstantType* inputType,
		ConstantType* outputType
	): statements(statements), ConstantFunctionValue(inputType, outputType) { }
	
	void makeBody(Compiler* compiler, Value* argument) override;
	
};

#endif /* ConstantUserDefinedFunction_hpp */
