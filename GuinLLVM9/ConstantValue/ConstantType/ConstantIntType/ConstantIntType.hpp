//
//  ConstantIntType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantIntType_hpp
#define ConstantIntType_hpp

#include "ConstantType.hpp"

class ConstantIntType: public ConstantType {
	
public:
	
	ConstantIntType() { };
	
	std::string identifierString() override;
	
	Type* getLLVMType(Compiler* compiler) override;
	
};

#endif /* ConstantIntType_hpp */
