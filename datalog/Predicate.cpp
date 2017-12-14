#include "Predicate.h"

Predicate::Predicate(string i, vector<Parameter> p)
{
	id = i;
	param = p;
}


Predicate::~Predicate()
{
}

string Predicate::toString()
{
	stringstream ss;
	ss << id << "(";
	if (param.size()>0)
	{
		ss << param[0].getVal();
	}
	if (param.size() > 1)
	{
		for (int i = 1; i < param.size(); i++)
		{
			ss << "," << param[i].getVal();
		}
	}
	ss << ")";
	return ss.str();
}

string Predicate::toString2()
{
	stringstream ss;
	ss << id << "(";
	if (param.size() > 0)
	{
		ss << param[0].getVal();
	}
	if (param.size() > 1)
	{
		for (int i = 1; i < param.size(); i++)
		{
			ss << "," << param[i].getVal();
		}
	}
	ss << ")";
	return ss.str();
}

string Predicate:: getId()
{
    return id;
}

vector<Parameter> Predicate:: getParam()
{
    return param;
}

void Predicate:: setParam(string l, int i)
{
    param[i].setp(l);
}