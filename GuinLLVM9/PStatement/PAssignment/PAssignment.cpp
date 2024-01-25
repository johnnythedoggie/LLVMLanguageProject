//
//  PAssignment.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "PAssignment.hpp"

void PAssignment::compile(Compiler* compiler) {
	Value* memLocation = left->getMemoryLocation(compiler);
	assert(memLocation && "Cannot assign to value with no memory location.");
	std::string leftType = left->getConstantType(compiler)->identifierString();
	std::string rightType = right->getConstantType(compiler)->identifierString();
	assert(leftType == rightType && "Cannot assign value to variable of different type.");
	compiler->llvmBuilder->CreateStore(right->asLLVMValue(compiler), memLocation);
}
