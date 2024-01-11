//
//  PDeclaration.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PDeclaration.hpp"
#include "ValueHandler.hpp"

void PDeclaration::compile(Compiler* compiler) {
	switch (variance) {
		case PVariance::CONST: {
			compiler->valueForIdentifier[identifier] = ValueHandler::newConstantValue(
			    compiler,
			    value,
			    identifier
			);
			break;
		}
		case PVariance::LET: {
			compiler->valueForIdentifier[identifier] = ValueHandler::newStaticValue(
				 compiler,
				 value,
				 identifier
			);
			break;
		}
		case PVariance::VAR: {
			compiler->valueForIdentifier[identifier] = ValueHandler::newDynamicValue(
				compiler,
				value,
				identifier
			);
			break;
		}
	}
}
