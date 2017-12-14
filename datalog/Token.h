#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Token
{
	public:
	enum token 
	{
		COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, E_OF
	};
	string arr[14];
	// = { "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "EOF" };
	token tok;
	int line;
	string value;
	/*
	start
		read_s
		read_c
		read_sp
		end
		error
		switch (for comments or string)
		and swtich within string all in scanner
		void emit(state current, state next)
		*/

	Token(token t, string v, int l);
	~Token();
	string getToken();
	string getValue();
	int getLine();
	token getTok();
	
};

