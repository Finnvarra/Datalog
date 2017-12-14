#include "Database.h"

Database::Database()
{

}

Database::~Database()
{
    
}

void Database::addmembers(map<string, Relation> n)
{
    sRelations=n;
}

void Database:: addon (int i, Relation n)
{
    
}

string Database::toString()
{
    stringstream ss;
    for(auto s: sRelations)
    {
        ss<<s.first<<endl;
        ss<<s.second.toString();
        ss<<endl;
    }
    return ss.str();
}
vector<Tuple> add (vector<Tuple> t1, vector<Tuple> t2)
{
    for (int i=0; i<t1.size(); i++)
    {
        t2.push_back(t1[i]);
    }
    return t2;
}

set<Tuple> Database::qbool (string i, vector<string> q)
{
    set<Tuple> empty;
    for(auto s: sRelations)
    {
        if (i == s.first)
        {
            return s.second.evaluateQ(q);
        }
    }
    return empty;
}

string Database::spr(string i, Scheme q, set<Tuple> y, vector<string>par)
{
    string st= "";
    for(auto s: sRelations)
    {
        if(s.first == i)
        {
                st+=s.second.select(q, y);
               st+=s.second.project(par, y, q);
                st+=s.second.rename(par, y);
            st+="\n";
        }
    }
    return st;
}

Relation Database:: findrelation(string i)
{
    Relation none = Relation();
    for(auto a: sRelations)
    {
        if (a.first == i)
        {
            return a.second;
        }
    }
    return none;
}

void Database::addRelation(Relation n, string i)
{
    sRelations[i]=n;
}