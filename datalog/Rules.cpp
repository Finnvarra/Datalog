#include "Rules.h"


Rules::Rules(Predicate p, vector<Predicate>p2)
{
	pred = p;
	preds = p2;
}


Rules::~Rules()
{
}

string Rules::toString()
{
	stringstream ss;
	ss << pred.toString() << " :- ";
	if (preds.size()>0)
	{
		ss << preds[0].toString2();
	}
	if (preds.size() > 1)
	{
		for (int i = 1; i < preds.size(); i++)
		{
			ss << "," << preds[i].toString2();
		}
	}
	return ss.str();
}

Predicate Rules:: getPred()
{
    return pred;
}

vector<Predicate> Rules:: getPreds()
{
    return preds;
}