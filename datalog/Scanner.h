#pragma once
#include "Token.h"
#include "Datalog.h"
#include <vector>
#include <fstream>
#include <sstream>
class Scanner
{
public:
	enum State{
		start,
		rcs,
		end
	};
	int line;
	string sub;
	ifstream in;
	vector<Token> tokens;
	Datalog item;
public:
	Scanner();
	~Scanner();
	int read(string file, vector<Token>&tokens);
	void final(string file, string file2);
	void print(vector<Token> tokens, int s, string file2);
	void identify(char a, vector<Token>&tokens);
	int default_trans(char c, vector<Token>&tokens);
	void evaluate(vector<Token>&tokens, char c, int & stuff, State&current);
	int rss(vector<Token>&tokens, char c);
	void error(State&current, int&stuff);
};

