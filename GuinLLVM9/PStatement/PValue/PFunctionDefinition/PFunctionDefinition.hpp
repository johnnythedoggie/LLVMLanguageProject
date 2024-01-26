//
//  PFunctionDefinition.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef PFunctionDefinition_hpp
#define PFunctionDefinition_hpp

#include "PValue.hpp"
#include "CImpureFunctionType.hpp"
#include <queue>

class PFunctionDefinition: public PValue {
	
public:
	
	CFunctionType* functionType;
	std::queue<PStatement*> functionBody;
	
	PFunctionDefinition(std::queue<PStatement*> functionBody)
	 : functionBody(functionBody) { }
	
	CValue* asConstantValue(Compiler* compiler) override;
	CFunctionType* getConstantType(Compiler* compiler) override;
	
	Value* asLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	
	void expectedType(CType* type) override;
	
};

#endif /* PFunctionDefinition_hpp */
