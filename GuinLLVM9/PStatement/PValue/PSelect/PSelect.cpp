//
//  PSelect.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/21/24.
//

#include "PSelect.hpp"
#include "CBoolValue.hpp"
#include "CBoolType.hpp"

Value* PSelect::asLLVMValue(Compiler* compiler) {
	std::string errorMessage = "Invalid arguments to select statement.";
	std::string conditionType = condition->getConstantType(compiler)->identifierString();
	std::string boolType = CBoolType().identifierString();
	if (conditionType != boolType) throw errorMessage;
	std::string trueType = caseTrue->getConstantType(compiler)->identifierString();
	std::string falseType = caseFalse->getConstantType(compiler)->identifierString();
	if (trueType != falseType) throw errorMessage;
	Value* llvmCond = condition->asLLVMValue(compiler);
	Value* llvmTrue = caseTrue->asLLVMValue(compiler);
	Value* llvmFalse = caseFalse->asLLVMValue(compiler);
	return compiler->llvmBuilder->CreateSelect(llvmCond, llvmTrue, llvmFalse);
}

CValue* PSelect::asConstantValue(Compiler* compiler) {
	std::string errorMessage = "Invalid arguments to select statement.";
	std::string conditionType = condition->getConstantType(compiler)->identifierString();
	std::string boolType = CBoolType().identifierString();
	if (conditionType != boolType) throw errorMessage;
	std::string trueType = caseTrue->getConstantType(compiler)->identifierString();
	std::string falseType = caseFalse->getConstantType(compiler)->identifierString();
	if (trueType != falseType) throw errorMessage;
	CBoolValue* booleanCondition = dynamic_cast<CBoolValue*>(condition->asConstantValue(compiler));
	if (!booleanCondition) return nullptr;
	if (booleanCondition->value) {
		return caseTrue->asConstantValue(compiler);
	} else {
		return caseFalse->asConstantValue(compiler);
	}
}

CType* PSelect::getConstantType(Compiler* compiler) {
	std::string errorMessage = "Invalid arguments to select statement.";
	std::string trueType = caseTrue->getConstantType(compiler)->identifierString();
	std::string falseType = caseFalse->getConstantType(compiler)->identifierString();
	if (trueType != falseType) throw errorMessage;
	return caseTrue->getConstantType(compiler);
}

PVariance PSelect::getVariance(Compiler* compiler) {
	CBoolValue* booleanCondition = dynamic_cast<CBoolValue*>(condition->asConstantValue(compiler));
	if (!booleanCondition) return PVariance::LET;
	if (booleanCondition->value) {
		if (caseTrue->getVariance(compiler) == PVariance::CONST) {
			return PVariance::CONST;
		} else {
			return PVariance::LET;
		}
	} else {
		if (caseFalse->getVariance(compiler) == PVariance::CONST) {
			return PVariance::CONST;
		} else {
			return PVariance::LET;
		}
	}
}
