//
//  CPureFunctionType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CPureFunctionType_hpp
#define CPureFunctionType_hpp

#include "CFunctionType.hpp"

class CPureFunctionType: public CFunctionType {
	
public:
	
	CPureFunctionType(CType* inputType, CType* outputType)
	: CFunctionType(true, inputType, outputType) { }
	
	std::string identifierString() override;
	
	FunctionType* getLLVMFunctionType(Compiler* compiler);
	
	Type* asLLVMType(Compiler* compiler) override;
	
};


#endif /* CPureFunctionType_hpp */
