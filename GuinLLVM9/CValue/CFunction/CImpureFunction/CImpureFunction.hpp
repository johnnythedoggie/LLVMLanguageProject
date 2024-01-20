//
//  CImpureFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#ifndef CImpureFunction_hpp
#define CImpureFunction_hpp

#include "CFunction.hpp"
#include "CImpureFunctionType.hpp"

class CImpureFunction: public CFunction {
	
public:
	
	std::vector<CompilerValue*> captureList = {};
	
	CImpureFunction(CType* inputType, CType* outputType)
	: CFunction(inputType, outputType) { }
	
	CType* getConstantType() override;
	
	void makeFunction(Compiler* compiler) override;
	
	Value* getLLVMValue(Compiler* compiler) override {
		if (!function) makeFunction(compiler);
		
		std::vector<Value*> captureValues = {};
		
		for (CompilerValue* capture : captureList) {
			if (capture->variance == PVariance::LET) {
				Value* referenced = compiler->llvmBuilder->CreateAlloca(capture->constantType->asLLVMType(compiler));
				compiler->llvmBuilder->CreateStore(capture->staticValue, referenced);
				Value* castedIntoOpaque = compiler->llvmBuilder->CreatePointerCast(
					referenced,
					CImpureFunctionType::opaqueContextLLVMType(compiler)
				);
				captureValues.push_back(castedIntoOpaque);
			} else if (capture->variance == PVariance::VAR) {
				Value* castedIntoOpaque = compiler->llvmBuilder->CreatePointerCast(
				   capture->dynamicValueLocation,
				   CImpureFunctionType::opaqueContextLLVMType(compiler)
				);
				captureValues.push_back(castedIntoOpaque);
			} else {
				throw 3456;
			}
		}
		
		StructType* type = CImpureFunctionType(inputType, outputType).asLLVMType(compiler);
		Value* struture = ConstantStruct::get(type, {});
		struture = compiler->llvmBuilder->CreateInsertValue(struture, function, 0);
		ArrayType* arrayType = ArrayType::get(CImpureFunctionType::opaqueContextLLVMType(compiler), captureList.size());
		Value* zero = ConstantInt::get(compiler->llvmBuilder->getInt32Ty(), 0);
		Value* captureArgument = compiler->llvmBuilder->CreateAlloca(arrayType);
		for (int i = 0; i < captureValues.size(); i += 1) {
			Value* index = ConstantInt::get(compiler->llvmBuilder->getInt32Ty(), i);
			Value* ptr = compiler->llvmBuilder->CreateGEP(captureArgument, { zero, index });
			compiler->llvmBuilder->CreateStore(captureValues[i], ptr);
		}
		captureArgument = compiler->llvmBuilder->CreateGEP(captureArgument, { zero, zero });
		struture = compiler->llvmBuilder->CreateInsertValue(struture, captureArgument, 1);
		return struture;
	}
	
};

#endif /* CImpureFunction_hpp */
