//
//  ConstantNeverType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef ConstantNeverType_hpp
#define ConstantNeverType_hpp

#include "ConstantType.hpp"

class ConstantNeverType: public ConstantType {
	
public:
	
	ConstantNeverType() { };
	
	std::string identifierString() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
	static Value* secretInstance(Compiler* compiler) {
		StructType* type = StructType::get(*compiler->llvmContext, { });
		return ConstantStruct::get(type, { });
	}
	
};

#endif /* ConstantNeverType_hpp */
