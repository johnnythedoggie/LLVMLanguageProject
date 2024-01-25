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
#include "CValue.hpp"
#include "CType.hpp"

class PValue: public PStatement {
	
public:
	
	virtual CValue* asConstantValue(Compiler* compiler) = 0;
	virtual CType* getConstantType(Compiler* compiler) = 0;
	
	virtual Value* asLLVMValue(Compiler* compiler) = 0;
	Type* getLLVMType(Compiler* compiler);
	
	virtual PVariance getVariance(Compiler* compiler) = 0;
	
	virtual Value* getMemoryLocation(Compiler* compiler);
	
	void compile(Compiler* compiler) override;
	
	
	
};

#endif /* PValue_hpp */
