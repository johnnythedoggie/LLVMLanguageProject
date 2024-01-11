//
//  PValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PValue_hpp
#define PValue_hpp

#include "PVariance.hpp"
#include "PStatement.hpp"
#include "ConstantValue.hpp"
#include "ConstantType.hpp"

class PValue: public PStatement {
	
public:
	
	virtual ConstantValue* getConstantValue(Compiler* compiler) = 0;
	virtual ConstantType* getConstantType(Compiler* compiler) = 0;
	
	virtual Value* getLLVMValue(Compiler* compiler) = 0;
	virtual PVariance getVariance(Compiler* compiler) = 0;
	
	virtual Value* getMemoryLocation(Compiler* compiler) { return nullptr; }
	
	void compile(Compiler* compiler) override {
		getLLVMValue(compiler);
	}
	
};

#endif /* PValue_hpp */
