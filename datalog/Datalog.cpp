#include "Datalog.h"
#include "Rules.h"


Datalog::Datalog(vector<Token> l)
{
	list = l;
	count = 0;
	repeat = 0;
}


Datalog::~Datalog()
{
}

void Datalog::datalogProgram(string file2)
{
	try
	{
		match(Token::SCHEMES);
		match(Token::COLON);
		scheme();
		schemeList();
		pred.clear();
		match(Token::FACTS);
		match(Token::COLON);
		factList();
		pred.clear();
		match(Token::RULES);
		match(Token::COLON);
		ruleList();
		match(Token::QUERIES);
		match(Token::COLON);
		query();
		queryList();
		pred.clear();
		match(Token::E_OF);
/*
		ofstream out;
		out.open(file2);
		out << "Success!" << endl;
		out << "Schemes("<<schemes.size()<<"):" << endl;
		for (int i = 0; i < schemes.size(); i++)
		{
			out<<schemes[i].toString()<<endl;
		}
		out << "Facts(" << facts.size()<<"):" << endl;
		for (int i = 0; i < facts.size(); i++)
		{
			out << facts[i].toString() << endl;
		}
		out << "Rules(" << rules.size() << "):" << endl;
		for (int i = 0; i < rules.size(); i++)
		{
			out<<rules[i].toString()<<endl;
		}
		out << "Queries(" << queries.size()<<"):" << endl;
		for (int i = 0; i < queries.size(); i++)
		{
			out<<queries[i].toString()<<endl;
		}
		out << "Domain(" <<domain.size()<< "):" << endl;
		for (auto a: domain)
		{
			out << "  " << a << endl;
		}
		out.close();*/
        Interpretor d(schemes, facts, rules, queries);
        d.Data(file2);
	
	}
	catch (Token error)
	{
		ofstream out;
		out.open(file2);
		out << "Failure!" << endl;
		out << "  " << "(" << error.getToken() << ",\"" << error.getValue() << "\"," << error.getLine() << ")" << endl;
		out.close();
	}
}

void Datalog ::match(Token::token t)
{
	if (t == list[count].getTok())
	{
		count++;
	}
	else
	{
		throw list[count];
	}
	return;
}

void Datalog::scheme()
{
	predicate();
	schemes = pred;
}

void Datalog::schemeList()
{
	if (list[count].getTok() != Token::FACTS)//what do I put here
	{
		scheme();
		schemeList();
	}
	else
	{
		return;
	}
}

void Datalog::fact()
{
	predicate();
	facts = pred;
	match(Token::PERIOD);
}

void Datalog::factList()
{
	if (list[count].getTok() != Token::RULES)
	{
		fact();
		factList();
	}
	else
	{
		return;
	}
}

void Datalog::rule()
{
	predicate();
	match(Token::COLON_DASH);
	predicate();
	predicateList();
	match(Token::PERIOD);
	per2 = pred[0];
	pred.erase(pred.begin());
	r = Rules(per2, pred);
	rules.push_back(r);
	pred.clear();
}

void Datalog::ruleList()
{
	if (list[count].getTok() != Token::QUERIES)
	{
		rule();
		ruleList();
	}
	else
	{
		return;
	}
}

void Datalog::query()
{
	predicate();
	queries = pred;
	match(Token::Q_MARK);
}

void Datalog::queryList()
{
	if (list[count].getTok() != Token::E_OF)
	{
		query();
		queryList();
	}
	else
	{
		return;
	}
}

void Datalog::predicate()
{
	if (list[count].getTok() == Token::ID)
	{
		id = list[count].getValue();
	}
	match(Token::ID);
	match(Token::LEFT_PAREN);
	parameter();
	parameterList();
	match(Token::RIGHT_PAREN);
	per = Predicate(id, par);
	par.clear();
	pred.push_back(per);

}

void Datalog::predicateList()
{
	if (list[count].getTok() != Token::PERIOD)
	{
		match(Token::COMMA);
		predicate();
		predicateList();
	}
}

void Datalog::parameter()
{
	//cout << list[count].getValue() << endl;
	if (list[count].getTok()==Token::STRING)
	{
		p = Parameter(Token::STRING, list[count].getValue());
		domain.insert(list[count].getValue());
		par.push_back(p);
		match(Token::STRING);
	}
	else //if (list[count].getTok() == Token::ID)
	{
		match(Token::ID);
		p = Parameter(Token::ID, list[count-1].getValue());
		par.push_back(p);
		
	}
	//else if (list[count].getTok() == Token::RIGHT_PAREN)
	//{
	//	return;
	//}
	//else
	//{
	//	throw list[count];
	//}
}

void Datalog::parameterList()
{
	if (list[count].getTok() != Token::RIGHT_PAREN)
	{
		match(Token::COMMA);
		parameter();
		parameterList();
	}
}