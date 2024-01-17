//
//  ValueHandler.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ValueHandler.hpp"


CompilerValue* ValueHandler::newDynamicValue(Compiler* compiler, PValue* initalValue, std::string name) {
	Value* location = compiler->llvmBuilder->CreateAlloca(initalValue->getLLVMType(compiler), nullptr, name);
	compiler->llvmBuilder->CreateStore(initalValue->asLLVMValue(compiler), location);
	CType* type = initalValue->getConstantType(compiler);
	return new CompilerValue {
		PVariance::VAR,
		type,
		location,
		nullptr,
		nullptr
	};
}

CompilerValue* ValueHandler::newStaticValue(Compiler* compiler, PValue* value, std::string name) {
	CType* type = value->getConstantType(compiler);
	Value* staticValue = value->asLLVMValue(compiler);
	staticValue->setName(name);
	return new CompilerValue {
		PVariance::LET,
		type,
		nullptr,
		staticValue,
		nullptr
	};
}

CompilerValue* ValueHandler::newConstantValue(Compiler* compiler, CValue* value, std::string name) {
	CType* type = value->getConstantType();
	return new CompilerValue {
		PVariance::CONST,
		type,
		nullptr,
		nullptr,
		value
	};
}

CompilerValue* ValueHandler::newConstantValue(Compiler* compiler, PValue* value, std::string name) {
	CValue* constValue = value->asConstantValue(compiler);
	std::string errorMessage = "Cannot create const identifier with non-const value.";
	if (!constValue) throw errorMessage;
	return newConstantValue(compiler, constValue, name);
}

Value* ValueHandler::getLLVMValue(CompilerValue* value, Compiler* compiler) {
	std::string errorMessage = "Error making LLVM value.";
	switch (value->variance) {
		case PVariance::VAR: {
			if (value->dynamicValueLocation == nullptr) throw errorMessage;
			return compiler->llvmBuilder->CreateLoad(value->dynamicValueLocation);
		}
		case PVariance::LET: {
			if (value->staticValue == nullptr) throw errorMessage;
			return value->staticValue;
		}
		case PVariance::CONST: {
			// must be effectively demoted to LET to have an LLVM value
			if (value->constantValue == nullptr) throw errorMessage;
			return value->constantValue->getLLVMValue(compiler);
		}
	}
}

Value* ValueHandler::getLLVMLocation(CompilerValue* value, Compiler* compiler) {
	if (value->variance != PVariance::VAR) return nullptr;
	std::string errorMessage = "Error getting llvm location.";
	if (value->dynamicValueLocation == nullptr) throw errorMessage;
	return value->dynamicValueLocation;
}

