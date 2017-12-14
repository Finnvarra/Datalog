#pragma once
#include "Scheme.h"
#include "Tuple.h"
#include <map>
#include <sstream>
#include <set>
class Relation{
public:
    vector<string> scheme;
    Scheme temp;
    set<Tuple> selected;
    int quernum;
    Tuple RParam;
    Scheme parlist;
    vector<vector<string>> tuplist;
    set<Tuple> tuples;
    Tuple tup;
    string schemeName;
    
    Relation(Scheme p, vector<vector<string>>t);
    Relation(){};
    ~Relation();
    void remove(string a, int index);
    Scheme getScheme();
    void addTemp(Scheme p);
    Scheme getTempScheme();
    void setScheme (Scheme s);
    set<Tuple> getTuples();
    void addTuple(set<Tuple> t);
    void newTuple (Tuple t1, Tuple t2, vector<int> s);
    string select(vector<string>p, set<Tuple>y);
    string project(vector<string>p, set<Tuple>y, vector<string>q);
    string rename(vector<string>q, set<Tuple>y);
    void createtuple();
    string toString();
    set<Tuple> evaluateQ(vector<string>p);
    vector<int> match (map<string, vector<int>>m, string l);
    int repeat(Tuple s, vector<int>pl, int cur);
    string sprPrint();
    Tuple join (Tuple t1, Tuple t2);
    //void createParam();
    
};

