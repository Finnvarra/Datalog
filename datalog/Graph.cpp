#include "Graph.h"

Graph:: Graph()
{
    
}

Graph::~Graph()
{
    
}

void Graph::addmember(map<int, Node> d, map<int, Node> r)
{
    depend= d;
    reverse=r;
}

string Graph::printd(int rnum)
{
    stringstream ss;
    ss<<"Dependency Graph"<<endl;
    for (int i=0; i<rnum; i++)
    {
        ss<<"  R"<<i<<":";
        ss<<depend[i].print()<<endl;
    }
    return ss.str();
}

string Graph::printr(int rnum)
{
    stringstream ss;
    ss<<"Reverse Graph"<<endl;
    for (int i=0; i<rnum; i++)
    {
        ss<<"  R"<<i<<":";
        ss<<reverse[i].print()<<endl;
    }

    return ss.str();
}

void Graph::dfsForest()
{
    counter=0;
    for (auto a: reverse)
    {
        //cout<<"Node R"<<a.first<<endl;
        dfs(a.first);
    }
}

void Graph::dfs(int i)
{
    
    if (reverse[i].visit()==false)
    {
        //cout<<"R"<<i<<" not visited"<<endl;
        reverse[i].visited();
        for (auto a: reverse[i].getadj())
        {
            dfs(a);
           
        }
        counter++;
        //cout<<counter<<" R"<<i<<endl;
        reverse[i].setPoNum(counter);
        ponumorder.push_back(i);
    }
}

string Graph::printpo(int rnum)
{
    stringstream ss;
    ss<<"Postorder Numbers"<<endl;
    for (int i=0; i<rnum; i++)
    {
        ss<<"  R"<<i<<": "<<reverse[i].getPoNum()<<endl;
    }
    ss<<endl;
    return ss.str();
}

void Graph:: ssc()
{
    set<int>cur;
    for (int i=ponumorder.size()-1; i>=0; i--)
    {
        sscdfs(ponumorder[i], cur);
        if (cur.size() !=0)
        {
        scc.push_back(cur);
        }
        cur.clear();
    }
}

void Graph:: sscdfs(int i, set<int>&cur)
{
        if (depend[i].visit()==false)
        {
            depend[i].visited();
        for (auto a: depend[i].getadj())
        {
            sscdfs(a, cur);
        }
            cur.insert(i);
        }
    

}

string Graph:: printssc()
{
    stringstream ss;
    ss<<"SCC Search Order"<<endl;
    for (int i=ponumorder.size()-1; i>=0; i--)
    {
        ss<<"  R"<<ponumorder[i]<<endl;
    }
    return ss.str();
}

vector<set<int>> Graph::getscc()
{
    return scc;
}

int Graph::depsize(int a)
{
    return depend[a].adjsize();
}