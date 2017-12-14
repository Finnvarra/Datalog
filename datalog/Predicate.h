#pragma once
#include "Parameter.h"
class Predicate
{
protected:
	string id;
	vector<Parameter> param;
public:
	Predicate(){};
	Predicate(string i, vector<Parameter>p);
	~Predicate();
	string toString();
	string toString2();
	string convertparam();
    string getId();
    vector<Parameter> getParam();
    void setParam(string l, int i);
};

