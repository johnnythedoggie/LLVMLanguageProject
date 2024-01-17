//
//  CPureFunctionType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CPureFunctionType_hpp
#define CPureFunctionType_hpp

#include "CType.hpp"

class CPureFunctionType: public CType {
	
public:
	
	CType* inputType;
	CType* outputType;
	
	CPureFunctionType(CType* inputType, CType* outputType)
	: inputType(inputType), outputType(outputType) { }
	
	std::string identifierString() override;
	
	FunctionType* getLLVMFunctionType(Compiler* compiler);
	
	// this will give a pointer to the LLVMFunctionType.
	Type* asLLVMType(Compiler* compiler) override;
	
};


#endif /* CPureFunctionType_hpp */
