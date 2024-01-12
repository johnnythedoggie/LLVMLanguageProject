//
//  PFunctionDefinition.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef PFunctionDefinition_hpp
#define PFunctionDefinition_hpp

#include "PValue.hpp"
#include "ConstantFunctionType.hpp"
#include <queue>

class PFunctionDefinition: public PValue {
	
public:
	
	PValue* fucntionType;
	std::queue<PStatement*> functionBody;
	
	PFunctionDefinition(PValue* fucntionType, std::queue<PStatement*> functionBody)
	: fucntionType(fucntionType), functionBody(functionBody) { }
	
	ConstantValue* getConstantValue(Compiler* compiler) override;
	ConstantFunctionType* getConstantType(Compiler* compiler) override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PFunctionDefinition_hpp */
