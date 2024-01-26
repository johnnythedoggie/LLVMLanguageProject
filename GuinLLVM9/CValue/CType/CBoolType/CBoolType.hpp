//
//  CBoolType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CBoolType_hpp
#define CBoolType_hpp

#include "CType.hpp"

class CBoolType: public CType {
	
public:
	
	CBoolType() { };
	
	std::string id() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
};

#endif /* CBoolType_hpp */
