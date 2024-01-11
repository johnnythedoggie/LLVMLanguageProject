//
//  ConstantType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantType.hpp"
#include "ConstantTypeType.hpp"

ConstantType* ConstantType::getConstantType() {
	return new ConstantTypeType();
}
