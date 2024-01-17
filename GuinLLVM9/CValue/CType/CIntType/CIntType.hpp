//
//  CIntType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CIntType_hpp
#define CIntType_hpp

#include "CType.hpp"

class CIntType: public CType {
	
public:
	
	CIntType() { };
	
	std::string identifierString() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
};

#endif /* CIntType_hpp */
