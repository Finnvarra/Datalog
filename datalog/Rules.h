#pragma once
#include "Predicate.h"
class Rules
{
protected:
	Predicate pred;
	vector<Predicate> preds;
public:
	Rules(){};
	Rules(Predicate p, vector<Predicate> p2);
	~Rules();
	string toString();
    Predicate getPred();
    vector<Predicate> getPreds();
};

