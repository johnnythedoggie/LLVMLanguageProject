//
//  CFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#include "CFunction.hpp"

int CFunction::globalIdentifier = 0;

std::string CFunction::id() {
	return "function" + std::to_string(identifier);
}
