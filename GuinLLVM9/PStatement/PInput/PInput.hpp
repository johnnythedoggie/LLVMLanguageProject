//
//  PInput.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PInput_hpp
#define PInput_hpp

#include "PStatement.hpp"
#include "PIdentifier.hpp"

class PInput: public PStatement {
	
	static Value* format;
	static Function* scanf;
	
	void setup(Compiler* compiler);
	
public:
	
	PIdentifier* argument;
	
	void compile(Compiler* compiler) override;
	
	PInput(PIdentifier* argument) : argument(argument) { }
	
};

#endif /* PInput_hpp */
