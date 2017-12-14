#pragma once
#include "Predicate.h"
#include "Rules.h"
#include "Database.h"
#include <fstream>
#include "Graph.h"
class Interpretor
{
protected:
    vector<Rules> rules;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<string> Id;
    vector<vector<Parameter>> par;
    vector<Parameter> ram;
    vector<string>ft;
    Scheme S;
    Graph g;
    Relation real;
    vector<int> checkers;
    vector<string> quer;
    ofstream out;
    int prev;
    map<int, Node> dep;
    map<int, Node> rev;
    map<string, Relation> sch;
    Database d;
public:
    Interpretor(vector<Predicate> s, vector<Predicate> f, vector<Rules> r, vector<Predicate> q);
    ~Interpretor();
    void Data(string file2);
    void work (set<int> rscc);
    void graphs();
    void RPonPreds(int a);
    bool detect (set<int> scc);
    void prunetuple();
    void addScheme();
    void addFacts();
    void addRules();
    void addTempscheme(vector<Parameter> p, Relation& r);
    void endprint(Relation r);
    Scheme comboS(Scheme s1, Scheme s2);
    Relation join(Relation r2);
    bool joinable(Tuple t1, Tuple t2);
    void rulePrint(Predicate p, string i);
    void tupleruleprint(vector<string> param, set<Tuple> t, vector<int> places, string i);
    void createRelation();
    void addQueries();
    void convertpar(vector<Parameter>p);
};