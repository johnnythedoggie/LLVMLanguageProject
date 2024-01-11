//
//  PDeclaration.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PDeclaration.hpp"

void PDeclaration::compile(Compiler* compiler) {
	compiler->valueForIdentifier[identifier] = value->getValue(compiler);
}
