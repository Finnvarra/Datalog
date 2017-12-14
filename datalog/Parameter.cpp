#include "Parameter.h"


Parameter::Parameter(Token::token t, string val)
{
	type = t;
	value = val;
}


Parameter::~Parameter()
{
}

bool Parameter:: IS()
{
	if (type == Token::STRING)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

string Parameter::getVal()
{
	return value;
}

void Parameter::setp(string l)
{
    value=l;
}