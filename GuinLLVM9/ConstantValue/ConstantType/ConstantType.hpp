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
		// Don't output anything to LLVM for types
		return nullptr;
	}
	
	ConstantType* getConstantType() override;
	
};

#endif /* ConstantType_hpp */
