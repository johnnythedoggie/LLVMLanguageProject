//
//  ConstantTypeType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantTypeType_hpp
#define ConstantTypeType_hpp

#include "ConstantType.hpp"

class ConstantTypeType: public ConstantType {
	
public:
	
	ConstantTypeType() { };
	
	std::string identifierString() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
};

#endif /* ConstantTypeType_hpp */
