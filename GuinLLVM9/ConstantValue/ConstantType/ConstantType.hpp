//
//  ConstantType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ConstantType_hpp
#define ConstantType_hpp

#include "ConstantValue.hpp"

class ConstantType: public ConstantValue {
	
public:
	
	virtual Type* getLLVMType(Compiler* compiler) = 0;
	
	Value* getLLVMValue(Compiler* compiler) override {
		StructType* type = StructType::get(*compiler->llvmContext, { });
		return ConstantStruct::get(type, { });
	}
	
	ConstantType* getConstantType() override;
	
};

#endif /* ConstantType_hpp */
