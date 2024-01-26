//
//  CImpureFunctionType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#ifndef CImpureFunctionType_hpp
#define CImpureFunctionType_hpp

#include "CFunctionType.hpp"

class CImpureFunctionType: public CFunctionType {
	
public:
	
	CImpureFunctionType(CType* inputType, CType* outputType)
	: CFunctionType(false, inputType, outputType) { }
	
	std::string id() override;
	
	FunctionType* getLLVMFunctionType(Compiler* compiler);
	
	StructType* asLLVMType(Compiler* compiler) override;
	
	static Type* opaqueContextLLVMType(Compiler* compiler);
	
};

#endif /* CImpureFunctionType_hpp */
