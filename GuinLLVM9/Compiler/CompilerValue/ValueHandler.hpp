//
//  ValueHandler.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef ValueHandler_hpp
#define ValueHandler_hpp

#include "CompilerValue.hpp"
#include "Compiler.hpp"
#include "PValue.hpp"
#include <string>

namespace ValueHandler {
	
	CompilerValue* newDynamicValue(Compiler* compiler, PValue* initalValue, std::string name);
	
	CompilerValue* newStaticValue(Compiler* compiler, PValue* value, std::string name);
	
	CompilerValue* newConstantValue(Compiler* compiler, PValue* value, std::string name);

	CompilerValue* newConstantValue(Compiler* compiler, CValue* value, std::string name);
	
	Value* getLLVMValue(CompilerValue* value, Compiler* compiler);
	
	Value* getLLVMLocation(CompilerValue* value, Compiler* compiler);
	
}

#endif /* ValueHandler_hpp */
