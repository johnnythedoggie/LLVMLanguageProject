//
//  PIdentifier.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PIdentifier.hpp"


Value* PIdentifier::getValue(Compiler* compiler) {
	return compiler->valueForIdentifier[identifier];
}

void PIdentifier::compile(Compiler* compiler) {
	// do nothing
	return;
}
