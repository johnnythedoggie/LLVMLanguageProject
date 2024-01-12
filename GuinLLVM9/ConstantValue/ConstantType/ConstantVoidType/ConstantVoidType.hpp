//
//  ConstantVoidType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantVoidType_hpp
#define ConstantVoidType_hpp

#include "ConstantType.hpp"

class ConstantVoidType: public ConstantType {
	
public:
	
	ConstantVoidType() { };
	
	std::string identifierString() override;
	
	Type* getLLVMType(Compiler* compiler) override;
	
};

#endif /* ConstantVoidType_hpp */
