//
//  CType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CType.hpp"
#include "CTypeType.hpp"

CType* CType::getConstantType() {
	return new CTypeType();
}
