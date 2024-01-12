//
//  ConstantFunctionType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantFunctionType_hpp
#define ConstantFunctionType_hpp

#include "ConstantType.hpp"

class ConstantFunctionType: public ConstantType {
	
public:
	
	ConstantType* inputType;
	ConstantType* outputType;
	
	ConstantFunctionType(ConstantType* inputType, ConstantType* outputType)
	: inputType(inputType), outputType(outputType) { }
	
	std::string identifierString() override;
	
	Type* getLLVMType(Compiler* compiler) override;
	
};


#endif /* ConstantFunctionType_hpp */
