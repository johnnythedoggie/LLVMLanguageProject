//
//  PDeclaration.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PDeclaration.hpp"

void PDeclaration::compile(Compiler* compiler) {
	switch (variance) {
		case PVariance::CONST: {
			std::string errorMessage = "Cannot assign non-const value to const identifier.";
			if (value->getVariance(compiler) != PVariance::CONST) throw errorMessage;
			Value* llvmValue = value->getLLVMValue(compiler);
			llvmValue->setName(identifier);
			compiler->valueForIdentifier[identifier] = {
				variance,
				llvmValue,
			};
			break;
		}
		case PVariance::LET: {
			Value* llvmValue = value->getLLVMValue(compiler);
			llvmValue->setName(identifier);
			compiler->valueForIdentifier[identifier] = {
				variance,
				llvmValue,
			};
			break;
		}
		case PVariance::VAR: {
			Value* llvmValue = value->getLLVMValue(compiler);
			AllocaInst* variable = compiler->llvmBuilder->CreateAlloca(llvmValue->getType(), nullptr, identifier);
			compiler->llvmBuilder->CreateStore(llvmValue, variable);
			compiler->valueForIdentifier[identifier] = {
				variance,
				variable,
			};
			break;
		}
	}
	
	
}
