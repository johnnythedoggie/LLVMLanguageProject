//
//  GValue.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GValue_h
#define GValue_h

#include "GStatement.h"
#include "Variance.h"

class GType;

class GValue: public GStatement {
	
public:
	
	Variance variance;
	
	GValue(Variance variance) : variance(variance) { }
	
	static GValue* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
	virtual GType* typeOf() const = 0;
	
};


#endif /* GValue_h */
