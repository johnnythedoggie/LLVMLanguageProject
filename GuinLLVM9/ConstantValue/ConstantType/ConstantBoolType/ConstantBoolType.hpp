//
//  ConstantBoolType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantBoolType_hpp
#define ConstantBoolType_hpp

#include "ConstantType.hpp"

class ConstantBoolType: public ConstantType {
	
public:
	
	ConstantBoolType() { };
	
	std::string identifierString() override;
	
	Type* getLLVMType(Compiler* compiler) override;
	
};

#endif /* ConstantBoolType_hpp */
