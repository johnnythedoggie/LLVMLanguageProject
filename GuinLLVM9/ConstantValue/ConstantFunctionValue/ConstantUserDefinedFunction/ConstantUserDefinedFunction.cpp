//
//  ConstantUserDefinedFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "ConstantUserDefinedFunction.hpp"
#include "ConstantVoid.hpp"

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
	compiler->scope = { inputType, function->args().begin() };
	
	for (auto x : savedIdentifiers) {
		if (x.second->variance == PVariance::CONST) {
			compiler->valueForIdentifier[x.first] = x.second;
		}
	}
	
	compiler->llvmBuilder->SetInsertPoint(entryBlock);
	
	while(!statements.empty()) {
		statements.front()->compile(compiler);
		statements.pop();
	}
	
	// TODO: Allow non-void returning functions somehow
	
	compiler->llvmBuilder->CreateRet(ConstantVoid().getLLVMValue(compiler));
	
	// Put back how things were
	compiler->valueForIdentifier = savedIdentifiers;
	compiler->llvmBuilder->restoreIP(previousLocation);
	compiler->scope = savedScope;
}

Value* ConstantUserDefinedFunction::getLLVMValue(Compiler* compiler) {
	if (!function) setup(compiler);
	return function;
}
