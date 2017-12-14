#include <iostream>
#include <set>
#include <sstream>
using namespace std;
class Node
{
    set<int> adjID;
    bool flag;
    int ponum;
public:
    Node()
    {
        flag=false;
        ponum=-1;
    }
    
    void add (int i)
    {
        adjID.insert(i);
    }
    
    string print()
    {
        stringstream ss;
        for(auto a: adjID)
        {
            ss<<" R"<<a;
        }
        return ss.str();
    }
    bool visit()
    {
        return flag;
    }
    
    void visited()
    {
        flag=true;
    }
    set<int> getadj()
    {
        return adjID;
    }
    
    void setPoNum(int i)
    {
        ponum=i;
    }
    
    int getPoNum()
    {
        return ponum;
    }
    
    int adjsize()
    {
        return adjID.size();
    }
};