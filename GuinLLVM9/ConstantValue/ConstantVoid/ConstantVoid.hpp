//
//  ConstantVoid.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantVoid_hpp
#define ConstantVoid_hpp

#include "ConstantValue.hpp"

class ConstantVoid: public ConstantValue {
	
public:
	
	ConstantVoid() { }
	
	ConstantType* getConstantType() override;
	
	std::string identifierString() override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* ConstantVoid_hpp */
