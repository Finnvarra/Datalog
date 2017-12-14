#pragma once
#include "Token.h"
#include <sstream>

class Parameter
{
protected:
	Token::token type;
	string value;
public:
	Parameter(){};
	Parameter(Token::token t, string val);
	~Parameter();
	bool IS();
	string getVal();
    void setp(string l);
};

