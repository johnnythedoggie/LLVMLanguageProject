//
//  ConstantNeverType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef ConstantNeverType_hpp
#define ConstantNeverType_hpp

#include "ConstantType.hpp"
#include "ConstantVoid.hpp"

class ConstantNeverType: public ConstantType {
	
public:
	
	ConstantNeverType() { };
	
	std::string identifierString() override;
	
	Type* getLLVMType(Compiler* compiler) override;
	
	static Value* secretInstance(Compiler* compiler) {
		return ConstantVoid().getLLVMValue(compiler);
	}
	
};

#endif /* ConstantNeverType_hpp */
