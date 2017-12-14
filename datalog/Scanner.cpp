#include "Scanner.h"



Scanner::Scanner()
{
	sub = "";
	line = 1;
}


Scanner::~Scanner()
{
}

int Scanner::read(string file, vector<Token>&tokens)
{
	int stuff=0;
	in.open(file);
	char c;
	State current = start;
	while (in.get(c))
	{
		evaluate(tokens, c, stuff, current);
	}
	return stuff;
}

int Scanner::rss(vector<Token>&tokens, char c)
{
	sub = c;
	in.get(c);
	while (c != '\'')
	{
		if (c == '\n')
		{
			return -1;
		}
		else
		{
			sub += c;
		}
		in.get(c);
	}
		sub += c;
	tokens.push_back(Token(Token::STRING, sub, line));
	return 1;
}
void Scanner:: print(vector<Token>tokens, int s, string file2)
{
	ofstream out;
	out.open(file2);
	for (int i = 0; i < tokens.size(); i++)
	{
		out << "(" << tokens[i].getToken() << ",\"" << tokens[i].getValue() << "\"," << tokens[i].getLine() << ")" << endl;
	}
	switch (s){
	case 0:
		out << "Total Tokens = " << tokens.size();
		break;
	default:
		out << "Input Error on line " << s << endl;
		break;
	}
	
	out.close();
}

void Scanner::final(string file, string file2)
{
	int ans=read(file, tokens);
	item = Datalog(tokens);

	if (ans == 0)
	{
		tokens.push_back(Token(Token::E_OF, "", line));
		item = Datalog(tokens);
		item.datalogProgram(file2);
        //make a parser class for storage
		//print(tokens, ans, file2);
	}
	else
	{
		//print(tokens, ans, file2);
	}
}

int Scanner::default_trans(char c, vector<Token>&tokens)
{
	stringstream tt;
	tt << c;
	string ch;
	tt >> ch;
	switch (c)
	{
	case ',':
		tokens.push_back(Token(Token::COMMA, ch, line));
		break;
	case '.':
		tokens.push_back(Token(Token::PERIOD, ch, line));
		break;
	case '?':
		tokens.push_back(Token(Token::Q_MARK, ch, line));
		break;
	case '(':
		tokens.push_back(Token(Token::LEFT_PAREN, ch, line));
		break;
	case ')':
		tokens.push_back(Token(Token::RIGHT_PAREN, ch, line));
		break;
	case ':':
		if (in.peek() == '-')
		{
			sub = c;
			in.get(c);
			sub += c;
			tokens.push_back(Token(Token::COLON_DASH, sub, line));
		}
		else
		{
			sub = c;
			tokens.push_back(Token(Token::COLON, ch, line));
		}
		break;
	case '\n':
		line++;
		break;
	default:
		if (isalpha(c))
		{
			identify(c, tokens);//needs to check if its a key word or add on until it ends
		}
		else if (isspace(c))
		{
			break;
		}
		else
		{
			return -1;
		}
	}
	return 1;
}

void Scanner::identify(char a, vector<Token>&tokens)
{
	sub = a;
	while (isalpha(in.peek()) || isdigit(in.peek()))
	{
		in.get(a);
		sub += a;
	}
	if (sub == "Schemes")
	{
		tokens.push_back(Token(Token::SCHEMES, sub, line));
	}
	else if (sub == "Queries")
	{
		tokens.push_back(Token(Token::QUERIES, sub, line));
	}
	else if (sub == "Facts")
	{
		tokens.push_back(Token(Token::FACTS, sub, line));
	}
	else if (sub == "Rules")
	{
		tokens.push_back(Token(Token::RULES, sub, line));
	}
	else
	{
		tokens.push_back(Token(Token::ID, sub, line)); 
	}

}

void Scanner::evaluate(vector<Token>&tokens, char c, int &stuff, State&current)
{
	int er;
	sub += c;
	stringstream ss;
	ss << c;
	string ch;
	ss >> ch;
	switch (current) {
	case start:
		switch (c)
		{
		case '#':
			current = rcs;
			break;
		case '\'':
			er = rss(tokens, c);
			switch (er){
			case -1:
				error(current, stuff);
				break;
			case 1:
				current = start;
			}
			break;
		case '\n':
			line++;
			break;
		default:
			if (isalpha(c))
			{
				identify(c, tokens);//needs to check if its a key word or add on until it ends
				break;
			}
			else if (isspace(c))
			{
				break;
			}
			else
			{
				int e = default_trans(c, tokens);
				switch (e)
				{
				case-1:
					error(current, stuff);
					break;
				case 1:
					break;
				}
			}
			break;
		}
		break;
	case rcs:
		switch (c) {
		case '\n':
			line++;
			current = start;
			break;
		default:
			break;
		}
		break;
	case end:
		return;
		break;
	default:
		break;
	}

}

void Scanner::error(State& current, int&stuff)
{
	current = end;
	stuff = line;
}