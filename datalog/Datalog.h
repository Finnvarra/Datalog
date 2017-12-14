#pragma once
#include "Token.h"
#include "Rules.h"
#include "Interpretor.h"
#include <set>
#include <fstream>
class Datalog
{
protected:
	vector<Token> list;
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;
	vector<Rules> rules;
	int count;
	Parameter p;
	Predicate per;
	Predicate per2;
	Rules r;
	vector<Parameter> par;
	vector <Predicate> pred;
	string id;
	set<string> domain;
	int repeat;
public:
	Datalog() {};
	Datalog(vector<Token>list);
	~Datalog();
	void datalogProgram(string file2);
	void match(Token::token t);
	void scheme();
	void schemeList();
	void fact();
	void factList();
	void rule();
	void ruleList();
	void query();
	void queryList();
	void predicate();
	void predicateList();
	void parameter();
	void parameterList();
};

