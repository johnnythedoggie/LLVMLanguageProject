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
	
	
	Value* getValue(Compiler* compiler) override;
	
	void compile(Compiler* compiler) override;
	
	
};

#endif /* PIdentifier_hpp */
