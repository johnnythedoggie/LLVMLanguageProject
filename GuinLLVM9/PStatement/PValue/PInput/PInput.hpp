//
//  PInput.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PInput_hpp
#define PInput_hpp

#include "PValue.hpp"
#include "PIdentifier.hpp"

class PInput: public PValue {
	
	static Value* format;
	static Function* scanf;
	
	static void setup(Compiler* compiler);
	
public:
	
	PInput() { }
	
	ConstantValue* getConstantValue(Compiler* compiler) override;
	ConstantType* getConstantType(Compiler* compiler) override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PInput_hpp */
