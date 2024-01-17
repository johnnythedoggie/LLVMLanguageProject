//
//  PTupleType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#include "PTupleType.hpp"
#include "CTupleType.hpp"
#include "CTypeType.hpp"

Value* PTupleType::asLLVMValue(Compiler* compiler) {
	StructType* type = StructType::get(*compiler->llvmContext, { });
	return ConstantStruct::get(type, { });
}

CValue* PTupleType::asConstantValue(Compiler* compiler) {
	std::vector<CTupleTypeElement> constantElements = {};
	for (const PTupleTypeElement& element : elements) {
		CValue* typeValue = element.type->asConstantValue(compiler);
		if (!typeValue) return nullptr;
		CType* type = dynamic_cast<CType*>(typeValue);
		if (!type) return nullptr;
		constantElements.push_back({ element.label, type });
	}
	return new CTupleType(constantElements);
}

CType* PTupleType::getConstantType(Compiler* compiler) {
	return new CTypeType();
}

PVariance PTupleType::getVariance(Compiler* compiler) {
	for (PTupleTypeElement element : elements) {
		if (element.type->getVariance(compiler) != PVariance::CONST) {
			return PVariance::LET;
		}
	}
	return PVariance::CONST;
}
