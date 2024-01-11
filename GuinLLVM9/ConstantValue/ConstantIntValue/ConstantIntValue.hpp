//
//  ConstantInt.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantInt_hpp
#define ConstantInt_hpp

#include "ConstantValue.hpp"

class ConstantIntValue: public ConstantValue {
	
public:
	
	int value;
	
	ConstantIntValue(int value) : value(value) { }
	
	ConstantType* getConstantType() override;
	
	std::string identifierString() override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* ConstantInt_hpp */
