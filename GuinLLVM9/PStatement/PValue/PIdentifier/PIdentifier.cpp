//
//  PIdentifier.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PIdentifier.hpp"


Value* PIdentifier::getLLVMValue(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	
	CompilerValue compilerValue = compiler->valueForIdentifier[identifier];
	
	if (compilerValue.variance == PVariance::VAR) {
		return compiler->llvmBuilder->CreateLoad(compilerValue.llvmValue);
	} else {
		return compilerValue.llvmValue;
	}
}

void PIdentifier::compile(Compiler* compiler) {
	// do nothing
	return;
}

PVariance PIdentifier::getVariance(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	return compiler->valueForIdentifier[identifier].variance;
}

Value* PIdentifier::getMemoryLocation(Compiler* compiler) {
	std::string errorMessage = "Error getting memory location.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	CompilerValue compilerValue = compiler->valueForIdentifier[identifier];
	if (compilerValue.variance != PVariance::VAR) throw errorMessage;
	return compilerValue.llvmValue;
}
