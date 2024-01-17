//
//  CTypeType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CTypeType_hpp
#define CTypeType_hpp

#include "CType.hpp"

class CTypeType: public CType {
	
public:
	
	CTypeType() { };
	
	std::string identifierString() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
};

#endif /* CTypeType_hpp */
