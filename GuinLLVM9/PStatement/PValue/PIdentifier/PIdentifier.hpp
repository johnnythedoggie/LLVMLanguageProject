//
//  PIdentifier.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PIdentifier_hpp
#define PIdentifier_hpp

#include <string>
#include "PValue.hpp"

class PIdentifier : public PValue {
	
public:
	
	std::string identifier;
	
	PIdentifier(std::string identifier) : identifier(identifier) { }
	
	ConstantValue* asConstantValue(Compiler* compiler) override;
	ConstantType* getConstantType(Compiler* compiler) override;
	
	Value* asLLVMValue(Compiler* compiler) override;
	PVariance getVariance(Compiler* compiler) override;
	Value* getMemoryLocation(Compiler* compiler) override;
	
};

#endif /* PIdentifier_hpp */
