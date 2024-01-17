//
//  PAssignment.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "PAssignment.hpp"

void PAssignment::compile(Compiler* compiler) {
	Value* memLocation = left->getMemoryLocation(compiler);
	std::string errorMessage = "Failed to compile assignment.";
	if (!memLocation) throw errorMessage;
	std::string leftType = left->getConstantType(compiler)->identifierString();
	std::string rightType = right->getConstantType(compiler)->identifierString();
	if (leftType != rightType) throw errorMessage;
	compiler->llvmBuilder->CreateStore(right->asLLVMValue(compiler), memLocation);
}
