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
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	if (!compilerValue) throw errorMessage;
	Value* result = ValueHandler::getLLVMValue(compilerValue, compiler);
	result->setName(identifier);
	return result;
}

PVariance PIdentifier::getVariance(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	if (!compilerValue) throw errorMessage;
	return compilerValue->variance;
}

Value* PIdentifier::getMemoryLocation(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	if (!compilerValue) throw errorMessage;
	return ValueHandler::getLLVMLocation(compilerValue, compiler);
}

CValue* PIdentifier::asConstantValue(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	if (!compilerValue) throw errorMessage;
	if (compilerValue->variance != PVariance::CONST) return nullptr;
	return compilerValue->constantValue;
}

CType* PIdentifier::getConstantType(Compiler* compiler) {
	std::string errorMessage = "Identifer cannot be used before it is defined.";
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	if (!compilerValue) throw errorMessage;
	return compilerValue->constantType;
}
