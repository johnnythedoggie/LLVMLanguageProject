//
//  CType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CType_hpp
#define CType_hpp

#include "CValue.hpp"

class CType: public CValue {
	
public:
	
	virtual Type* asLLVMType(Compiler* compiler) = 0;
	
	Value* getLLVMValue(Compiler* compiler) override {
		StructType* type = StructType::get(*compiler->llvmContext, { });
		return ConstantStruct::get(type, { });
	}
	
	CType* getConstantType() override;
	
};

#endif /* CType_hpp */
