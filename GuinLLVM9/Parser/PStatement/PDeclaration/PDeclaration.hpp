//
//  PDeclaration.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PDeclaration_hpp
#define PDeclaration_hpp

#include "PStatement.hpp"
#include "PValue.hpp"
#include <string>

enum class PVariance {
	CONST,
	LET,
	VAR
};

class PDeclaration: public PStatement {
	
public:
	
	PVariance variance;
	std::string identifier;
	PValue* value;
	
	PDeclaration(PVariance variance, std::string identifier, PValue* value)
		: variance(variance), identifier(identifier), value(value) { }
	
	void compile(Compiler* compiler) override;
	
};

#endif /* PDeclaration_hpp */
