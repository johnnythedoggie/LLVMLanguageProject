//
//  Scope.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "Scope.hpp"
#include "Compiler.hpp"
#include "ValueHandler.hpp"
#include "CImpureFunctionType.hpp"

CompilerValue* Scope::valueForIdentifier(Compiler* compiler, std::string id) {
	if (scopedIdentifierToValue.contains(id)) {
		return scopedIdentifierToValue[id];
	} else if (capturedIdentifierToValue.contains(id)) {
		return capturedIdentifierToValue[id];
	} else {
		if (parentScope == nullptr) return nullptr;
		auto x = compiler->llvmBuilder->saveIP();
		compiler->llvmBuilder->restoreIP(parentInsertPoint);
		CompilerValue* externalValue = parentScope->valueForIdentifier(compiler, id);
		compiler->llvmBuilder->restoreIP(x);
		if (!externalValue) return nullptr;
		bool isConst = externalValue->variance == PVariance::CONST;
		if (isConst) {
			return externalValue;
		} else {
			if (isPureScope) return nullptr;
			Value* index = ConstantInt::get(compiler->llvmBuilder->getInt32Ty(), numCapturedValues);
			Value* newValue = compiler->llvmBuilder->CreateGEP(captureArgument, index);
			Value* castedOutOfOpaque = compiler->llvmBuilder->CreatePointerCast(
				compiler->llvmBuilder->CreateLoad(newValue),
			    externalValue->constantType->asLLVMType(compiler)->getPointerTo()
			);
			CompilerValue* internalValue;
			
			if (externalValue->variance == PVariance::LET) {
				Value* dereferenced = compiler->llvmBuilder->CreateLoad(castedOutOfOpaque);
				internalValue = new CompilerValue {
					PVariance::LET,
					externalValue->constantType,
					nullptr,
					dereferenced,
					nullptr
				};
			} else {
				internalValue = new CompilerValue {
					PVariance::VAR,
					externalValue->constantType,
					castedOutOfOpaque,
					nullptr,
					nullptr
				};
			}
			capturedValues.push_back(externalValue);
			numCapturedValues += 1;
			capturedIdentifierToValue[id] = internalValue;
			return internalValue;
		}
	}
}
