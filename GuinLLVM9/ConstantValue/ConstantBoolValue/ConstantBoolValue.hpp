//
//  ConstantBoolValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantBoolValue_hpp
#define ConstantBoolValue_hpp

#include "ConstantValue.hpp"

class ConstantBoolValue: public ConstantValue {
	
public:
	
	bool value;
	
	ConstantBoolValue(bool value) : value(value) { }
	
	ConstantType* getConstantType() override;
	
	std::string identifierString() override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* ConstantBoolValue_hpp */
