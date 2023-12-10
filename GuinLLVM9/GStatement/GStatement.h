//
//  GStatement.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GStatement_h
#define GStatement_h

#include "llvm.h"
#include "Tokenizer.h"
#include <queue>
#include <string>

class GValue;
class IRGenerator;

class GStatement {
	
	static bool hasNewLineNext(const std::queue<Token>& tokens);
	
public:
	
	static GStatement* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
	virtual std::string description() const = 0;
	
	virtual Value* generateIR(IRGenerator* generator) const = 0;
	
	virtual ~GStatement() = default;
	
};

#endif /* GStatement_h */
