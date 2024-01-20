//
//  CPureFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CPureFunction_hpp
#define CPureFunction_hpp

#include "CFunction.hpp"
#include "CType.hpp"

class CPureFunction: public CFunction {
	
public:
	
	CPureFunction(CType* inputType, CType* outputType)
		: CFunction(inputType, outputType) { }
	
	CType* getConstantType() override;
	
	void makeFunction(Compiler* compiler) override;
	
	Value* getLLVMValue(Compiler* compiler) override {
		if (!function) makeFunction(compiler);
		return function;
	}
	
};

#endif /* CPureFunction_hpp */
