#pragma once
#include "Relations.h"
#include "Predicate.h"
#include <map>
class Database
{
protected:
    map<string, Relation> sRelations;
public:
    Database();
    ~Database();
    void addmembers(map<string, Relation> n);
    string toString();
    set<Tuple> qbool(string i, vector<string> q);
    string spr(string i, Scheme q, set<Tuple> y, vector<string>par);
    Relation findrelation(string i);
    void addRelation(Relation n, string i);
    void addon (int i, Relation n);
};