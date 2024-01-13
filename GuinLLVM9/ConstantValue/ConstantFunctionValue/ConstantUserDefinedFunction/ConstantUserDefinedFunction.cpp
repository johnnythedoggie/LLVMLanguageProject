//
//  ConstantUserDefinedFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "ConstantUserDefinedFunction.hpp"
#include "ConstantVoid.hpp"
#include "PReturn.hpp"

void ConstantUserDefinedFunction::setup(Compiler* compiler) {
	
	std::vector<Type*> argTypes = { inputType->getLLVMType(compiler) };
	FunctionType* type = FunctionType::get(outputType->getLLVMType(compiler), argTypes, false);
	
	Function::Create(type, Function::ExternalLinkage, identifierString(), *compiler->llvmModule);
	
	function = compiler->llvmModule->getFunction(identifierString());
	
	BasicBlock* entryBlock = BasicBlock::Create(*compiler->llvmContext, "entry", function);
	
	// Prepare a new scope
	IRBuilder<>::InsertPoint previousLocation = compiler->llvmBuilder->saveIP();
	auto savedIdentifiers = compiler->valueForIdentifier;
	compiler->valueForIdentifier = {};
	Scope savedScope = compiler->scope;
	compiler->scope = { inputType, outputType, function->args().begin() };
	
	for (auto x : savedIdentifiers) {
		if (x.second->variance == PVariance::CONST) {
			compiler->valueForIdentifier[x.first] = x.second;
		}
	}
	
	compiler->llvmBuilder->SetInsertPoint(entryBlock);
	
	bool foundReturn = false;
	
	while(!statements.empty()) {
		PStatement* statement = statements.front();
		statements.pop();
		
		
		statement->compile(compiler);
		
		PReturn* value = dynamic_cast<PReturn*>(statement);
		if (value) {
			foundReturn = true;
			break;
		}
	}
	
	std::string errorMessage = "Function must end with a return.";
	
	if (!foundReturn) throw errorMessage;
	if (!statements.empty()) throw errorMessage;
	
	// Put back how things were
	compiler->valueForIdentifier = savedIdentifiers;
	compiler->llvmBuilder->restoreIP(previousLocation);
	compiler->scope = savedScope;
	
}

Value* ConstantUserDefinedFunction::getLLVMValue(Compiler* compiler) {
	if (!function) setup(compiler);
	return function;
}
