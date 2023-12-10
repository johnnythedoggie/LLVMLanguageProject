//
//  GIdentifier.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GIdentifier_h
#define GIdentifier_h

#include "GValue.h"

class GIdentifier {
	
public:
	
	static GValue* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
};


#endif /* GIdentifier_h */
