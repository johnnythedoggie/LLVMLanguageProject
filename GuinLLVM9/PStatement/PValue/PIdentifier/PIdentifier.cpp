//
//  PIdentifier.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PIdentifier.hpp"
#include "ValueHandler.hpp"

Value* PIdentifier::asLLVMValue(Compiler* compiler) {
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	assert(compilerValue && "Identifer cannot be used before it is defined.");
	Value* result = ValueHandler::getLLVMValue(compilerValue, compiler);
	result->setName(identifier);
	return result;
}

PVariance PIdentifier::getVariance(Compiler* compiler) {
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	assert(compilerValue && "Identifer cannot be used before it is defined.");
	return compilerValue->variance;
}

Value* PIdentifier::getMemoryLocation(Compiler* compiler) {
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	assert(compilerValue && "Identifer cannot be used before it is defined.");
	return ValueHandler::getLLVMLocation(compilerValue, compiler);
}

CValue* PIdentifier::asConstantValue(Compiler* compiler) {
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	assert(compilerValue && "Identifer cannot be used before it is defined.");
	if (compilerValue->variance != PVariance::CONST) return nullptr;
	return compilerValue->constantValue;
}

CType* PIdentifier::getConstantType(Compiler* compiler) {
	CompilerValue* compilerValue = compiler->scope->valueForIdentifier(compiler, identifier);
	assert(compilerValue && "Identifer cannot be used before it is defined.");
	return compilerValue->constantType;
}
