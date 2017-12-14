#include "Relations.h"

Relation::Relation(Scheme p, vector<vector<string>> t)
{
    quernum=0;
    tuplist=t;
    parlist=p;
}

Relation::~Relation()
{
    
}

Scheme Relation:: getScheme()
{
    return parlist;
}

set<Tuple> Relation:: getTuples()
{
    return tuples;
}

void Relation::setScheme (Scheme s)
{
    parlist=s;
}

void Relation::remove(string a, int index)
{
    vector<Tuple> eraser;
    for(auto b: tuples)
    {
        if (b[index] != a)
        {
            eraser.push_back(b);
        }
    }
    for(int i=0; i<eraser.size(); i++)
    {
        tuples.erase(eraser[i]);
    }
}

void Relation::addTuple(set<Tuple> t)
{
    for (auto a: t)
    {
        tuples.insert(a);
        /*cout<<"added ";
        for(int i=0; i<a.size(); i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;*/
    }
}

void Relation:: newTuple(Tuple t1, Tuple t2, vector<int> s)
{
    Tuple n= t1;
    int q=0;
    for(int j=0; j<t2.size(); j++)
    {
        for (int i=0; i<s.size(); i+=2)
        {
            if (j==s[i+1])
            {
                q=1;
            }
            
        }
        if (q==0)
        {
            n.push_back(t2[j]);
        }
        q=0;
    }
    tuples.insert(n);
   // cout<<"new tuple made"<<endl;
    /*for (int i=0; i<n.size(); i++)
    {
        cout<<n[i]<<" ";
    }
    cout<<endl;*/
    
}

void Relation::createtuple()
{
    for(int i=0; i<tuplist.size(); i++)
    {
    for(int j=0; j<tuplist[i].size(); j++)
    {
        tup.push_back(tuplist[i][j]);
    }
     tuples.insert(tup);
    tup.clear();
    }
   /*for(auto s : tuples)
    {int i=0;
        while (i <s.size())
        {
        cout<<s[i]<<" ";
            i++;
    }
        cout<<endl;
    }*/
}

string Relation:: toString()
{
    stringstream ss;
    for(auto s: tuples)
    {
        ss<<"  ";
        for (int i=0; i<parlist.size(); i++)
        {
            ss<<parlist[i]<<"="<<s[i]<<" ";
        }
        ss<<endl;
    }
    return ss.str();
}

set<Tuple> Relation:: evaluateQ(vector<string> p)
{
    selected.clear();
    int t=1;
    vector<int>places;
    for(auto s: tuples)
    {
        map<string, vector<int>>matches;
        for(int i=0; i<p.size(); i++)
        {
            if (p[i].substr(0,1) == "\'" && s[i] != p[i])
            {
                t=0;
            }
            else if (p[i].substr(0, 1) != "\'")
            {
                
                places =match(matches, p[i]);
                if (places.size() != 0)
                {
                        t=(repeat(s, places, i));
                }
                places.push_back(i);
                matches.insert(pair<string, vector<int>>(p[i], places));
            }
        }
        if (t==1)
        {
           selected.insert(s);
        }
        t=1;
    }
    //cout<<"selected size"<<selected.size()<<endl;
    return selected;
}

vector<int> Relation::match(map<string, vector<int>>m, string l)
{
    vector<int> empty;
    for(auto s: m)
    {
        if(l == s.first)
        {
            return s.second;
        }
    }
    return empty;
}


int Relation::repeat(Tuple s, vector<int> place, int cur)
{
        for (int i=0; i<place.size(); i++)
        {
            if (s[place[i]] != s[cur])
        {
            return 0;
        }
        }
    return 1;
}

string Relation::select(vector<string> p, set<Tuple> y)
{
    stringstream ss;
    ss<<"select"<<endl;
    for(auto j : y)
    {
        //cout<<"in the for loop "<<p.size()<<endl;
    ss<<"  ";
    for (int i=0; i<p.size(); i++)
    {
       // cout<<"in 2nd for loop"<<endl;
        ss<<p[i]<<"="<<j[i]<<" ";
    }
        ss<<endl;
    }
   return ss.str();
}

string Relation::project(vector<string> p, set<Tuple> y, vector<string>q)
{
    stringstream ss;
    int t=0;
   
    ss<<"project"<<endl;
    for(auto j: y)
    {
        map<string, vector<int>> re;
        vector<int> l;
    for(int i=0; i<p.size(); i++)
    {
        if (p[i].substr(0, 1) != "\'" && match(re, p[i]).size()==0)
        {
            if(i== 0 || ss.str() == "project\n")
            {
                ss<<"  ";
            }
            ss<<q[i]<<"="<<j[i]<<" ";
            t=1;
        }
        l.push_back(i);
        re.insert(pair<string, vector<int>>(p[i], l));
    }
        if (t == 1)
        {
        ss<<endl;
        }
    }
    return ss.str();
}

string Relation::rename(vector<string> q, set<Tuple> y)
{
    stringstream ss;
    int t=0;
    ss<<"rename"<<endl;
    for(auto j: y)
    {
        map<string, vector<int>> re;
        vector<int> l;
        for(int i=0; i<q.size(); i++)
        {
            if (q[i].substr(0, 1) != "\'" && match(re, q[i]).size()==0)
            {
                if(i== 0 || ss.str() == "rename\n")
                {
                    ss<<"  ";
                }
                ss<<q[i]<<"="<<j[i]<<" ";
                t=1;
            }
            l.push_back(i);
            re.insert(pair<string, vector<int>>(q[i], l));
        }
        if (t == 1)
        {
            ss<<endl;
        }
    }
    return ss.str();
}

string Relation::sprPrint()
{
    stringstream ss;
     cout<<"select"<<endl;
    return ss.str();
}

void Relation:: addTemp(Scheme p)
{
    temp=p;
}
Scheme Relation:: getTempScheme()
{
    return temp;
}
