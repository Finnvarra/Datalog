#include "Token.h"


Token::Token(token t, string v, int l)
{
	tok = t;
	value = v;
	line = l;
	arr[0] = "COMMA";
	arr[1] = "PERIOD";
	arr[2] = "Q_MARK";
	arr[3] = "LEFT_PAREN";
	arr[4] = "RIGHT_PAREN";
	arr[5] = "COLON"; 
	arr[6] = "COLON_DASH"; 
	arr[7] = "SCHEMES";
	arr[8] = "FACTS";
	arr[9] = "RULES";
	arr[10] = "QUERIES";
	arr[11] = "ID";
	arr[12] = "STRING";
	arr[13] = "EOF";
}


Token::~Token()
{
}

string Token::getToken()
{
	int t = static_cast<int>(tok);
	return arr[t];
}

string Token::getValue()
{
	return value;
}

int Token::getLine()
{
	return line;
}

Token::token Token::getTok()
{
	return tok;
}