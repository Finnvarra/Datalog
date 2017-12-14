#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include "Node.h"

using namespace std;

class Graph
{
    int counter;
    vector<int> ponumorder; // from high to low
    vector<set<int>>scc;
public:
    map <int, Node> depend;
    map<int, Node> reverse;
    Graph();
    ~Graph();
    void addmember(map<int, Node> d, map<int, Node> r);
    string printd(int rnum);
    string printr(int rnum);
    void dfsForest();
    void dfs(int i);
    string printpo(int rnum);
    void ssc();
    void sscdfs(int i, set<int>&cur);
    vector<set<int>> getscc();
    string printssc();
    int depsize(int a);
};