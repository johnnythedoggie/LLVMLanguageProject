//
//  CNeverType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef CNeverType_hpp
#define CNeverType_hpp

#include "CType.hpp"

class CNeverType: public CType {
	
public:
	
	CNeverType() { };
	
	std::string identifierString() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
	static Value* secretInstance(Compiler* compiler) {
		StructType* type = StructType::get(*compiler->llvmContext, { });
		return ConstantStruct::get(type, { });
	}
	
};

#endif /* CNeverType_hpp */
