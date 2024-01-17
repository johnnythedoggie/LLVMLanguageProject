//
//  PIdentifier.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PIdentifier.hpp"
#include "ValueHandler.hpp"

Value* PIdentifier::asLLVMValue(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	return ValueHandler::getLLVMValue(compiler->valueForIdentifier[identifier], compiler);
}

PVariance PIdentifier::getVariance(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	return compiler->valueForIdentifier[identifier]->variance;
}

Value* PIdentifier::getMemoryLocation(Compiler* compiler) {
	std::string errorMessage = "Error getting memory location.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	return ValueHandler::getLLVMLocation(compiler->valueForIdentifier[identifier], compiler);
}

ConstantValue* PIdentifier::asConstantValue(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	if (compiler->valueForIdentifier[identifier]->variance != PVariance::CONST) return nullptr;
	return compiler->valueForIdentifier[identifier]->constantValue;
}

ConstantType* PIdentifier::getConstantType(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	if (!compiler->valueForIdentifier.contains(identifier)) throw errorMessage;
	return compiler->valueForIdentifier[identifier]->constantType;
}
