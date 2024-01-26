//
//  PSelect.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/21/24.
//

#include "PSelect.hpp"
#include "CBoolValue.hpp"
#include "CBoolType.hpp"

// TODO: Combine some of this logic with other functions
Value* PSelect::asLLVMValue(Compiler* compiler) {
	std::string errorMessage = "Invalid arguments to select statement.";
	std::string conditionType = condition->getConstantType(compiler)->id();
	std::string boolType = CBoolType().id();
	assert(conditionType == boolType && "First argument to #select must be a Bool.");
	std::string trueType = caseTrue->getConstantType(compiler)->id();
	std::string falseType = caseFalse->getConstantType(compiler)->id();
	assert(trueType == falseType && "Second and third argunents to #select must be the same type.");
	Value* llvmCond = condition->asLLVMValue(compiler);
	Value* llvmTrue = caseTrue->asLLVMValue(compiler);
	Value* llvmFalse = caseFalse->asLLVMValue(compiler);
	return compiler->llvmBuilder->CreateSelect(llvmCond, llvmTrue, llvmFalse);
}

CValue* PSelect::asConstantValue(Compiler* compiler) {
	std::string conditionType = condition->getConstantType(compiler)->id();
	std::string boolType = CBoolType().id();
	assert(conditionType == boolType && "First argument to #select must be a Bool.");
	std::string trueType = caseTrue->getConstantType(compiler)->id();
	std::string falseType = caseFalse->getConstantType(compiler)->id();
	assert(trueType == falseType && "Second and third argunents to #select must be the same type.");
	CBoolValue* booleanCondition = dynamic_cast<CBoolValue*>(condition->asConstantValue(compiler));
	if (!booleanCondition) return nullptr;
	if (booleanCondition->value) {
		return caseTrue->asConstantValue(compiler);
	} else {
		return caseFalse->asConstantValue(compiler);
	}
}

CType* PSelect::getConstantType(Compiler* compiler) {
	std::string trueType = caseTrue->getConstantType(compiler)->id();
	std::string falseType = caseFalse->getConstantType(compiler)->id();
	assert(trueType == falseType && "Second and third argunents to #select must be the same type.");
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
