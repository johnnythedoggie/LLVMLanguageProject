//
//  ConstCompiler.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef ConstCompiler_hpp
#define ConstCompiler_hpp

#include <string>
#include <map>
#include "PValue.hpp"

class ConstCompiler {
	
public:
	
	std::map<std::string, PValue*> valueForIdentifier = {};
	void close();
	ConstCompiler();
	
};

#endif /* ConstCompiler_hpp */
