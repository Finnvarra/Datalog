#include "Interpretor.h"

Interpretor::Interpretor(vector<Predicate> s, vector<Predicate> f, vector<Rules> r, vector<Predicate> q)
{
    schemes=s;
    facts=f;
    rules=r;
    queries=q;
}
Interpretor::~Interpretor()
{
}

void Interpretor::Data(string file2)
{
    out.open(file2);
    addScheme();
    addFacts();
    addRules();
    //cout<<"back on top"<<endl;
    addQueries();
    out.close();
    
}

void Interpretor::addScheme()//reads in the schemes from the datalog program
{
    for(int i=0; i<schemes.size(); i++)
    {
        par.push_back(schemes[i].getParam());//vector of parameter vectors
        for(int j=0; j<par[i].size(); j++)
        {
            S.push_back(par[i][j].getVal());//converting parameters of a single identity to string for scheme
        }
        vector<vector<string>> empty;
        Relation Rel = Relation(S, empty);
        sch[schemes[i].getId()]=Rel;
       // cout<<schemes[i].getId()<<" "<<Rel.getScheme().size()<<endl;
        S.clear();
    }
    out<<"Scheme Evaluation"<<endl<<endl;
}

void Interpretor::addFacts()
{
    vector<Parameter>combo;//vector of combinations of parameters for a single fact
    out<<"Fact Evaluation"<<endl<<endl;
    for(int i=0; i<facts.size(); i++)
    {
        ft.clear();
        combo=facts[i].getParam();
        Tuple prep;
        for(int j=0; j<combo.size(); j++)
        {
                //cout<<facts[i].getId()<<endl;
                prep.push_back(combo[j].getVal());//the string conversion of combo
        }
        sch[facts[i].getId()].tuples.insert(prep);

    }
    d.addmembers(sch);
    out<<d.toString();
}

Scheme schs(map<string, Scheme> sch, string s)
{
    Scheme none;
    for (auto a : sch)
    {
        if (a.first == s)
        {
            return a.second;
        }
    }
    return none;
}

void Interpretor:: graphs()
{
    for(int i=0; i<rules.size(); i++)
    {
        for(int j=0; j<rules.size(); j++)
        {
            for(int k=0; k<rules[i].getPreds().size(); k++)
            {
                if (rules[i].getPreds()[k].getId() == rules[j].getPred().getId())
                {
                    dep[i].add(j);
                    rev[j].add(i);
                }
            }
        }
        
    }
}
void Interpretor::addRules()
{
    out<<"Rule Evaluation"<<endl<<endl;
    //set<int>opposite;
    graphs();
    g.addmember(dep, rev);
    out<<g.printd(rules.size())<<endl;
    out<<g.printr(rules.size())<<endl;
    g.dfsForest();
    out<<g.printpo(rules.size());
    g.ssc();
    out<<g.printssc()<<endl;
    vector<set<int>> rscc=g.getscc();
    int diff=1;
    bool past=false;
    for(int i=0; i<rscc.size(); i++)
    {
        work(rscc[i]);
        past = false;
        while (past != true)
        {
            bool nonadded= true;
        for(auto a: rscc[i])
        {
           // past=true;
            out<<rules[a].toString()<<endl;
        real=d.findrelation(rules[a].getPreds()[0].getId());
        addTempscheme(rules[a].getPreds()[0].getParam(), real);
        Scheme temp =real.getTempScheme();
        real.setScheme(temp);
        prunetuple();
        prev=d.findrelation(rules[a].getPred().getId()).getTuples().size();
        for (int j=0; j<rules[a].getPreds().size()-1; j++)
        {
            ram=rules[a].getPreds()[j+1].getParam();
            real=join(d.findrelation(rules[a].getPreds()[j+1].getId()));
            checkers.clear();
            ram.clear();
        }
        rulePrint(rules[a].getPred(), rules[a].getPred().getId());
            RPonPreds(a);
        diff = d.findrelation(rules[a].getPred().getId()).getTuples().size()-prev;
        prev=d.findrelation(rules[a].getPred().getId()).getTuples().size();
        if (diff != 0)
        {
            //cout<<"here"<<endl;
            nonadded =false;
        }
            if (detect(rscc[i])==true)
        {
           past=true;
        }
        }
            if (nonadded == true)
            {
                past =true;
            }
    }
        out<<endl;
   }

    
    
    out<<"Rule Evaluation Complete"<<endl<<endl;
    out<<d.toString();
}


void Interpretor::RPonPreds(int a)
{
    for (int j=0; j<rules[a].getPreds().size(); j++)
    {
        rulePrint(rules[a].getPreds()[j], rules[a].getPreds()[j].getId());
    }
}
void Interpretor::work (set<int> rscc)
{
    out<<"SCC:";
    for(auto a: rscc)
    {
        out<<" R"<<a;
    }
    out<<endl;
}

bool Interpretor::detect (set<int> scc)
{
    if (scc.size()==1)
    {
        for(auto a : scc)
        {
            for (int i=0; i<rules[a].getPreds().size(); i++)
            {
                if (rules[a].getPred().getId()== rules[a].getPreds()[i].getId())
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

void Interpretor::prunetuple ()
{
    for (int i=0; i<real.getScheme().size(); i++)
    {
        if (real.getScheme()[i].substr(0, 1)== "\'")
        {
            real.remove(real.getScheme()[i], i);
        }
    }
    
}
void Interpretor::addTempscheme(vector<Parameter> p, Relation& r)
{
    Scheme s;
    for (int i =0; i<p.size(); i++)
    {
        s.push_back(p[i].getVal());
    }
    r.addTemp(s);
    
}

void Interpretor::endprint (Relation r)
{
    Scheme s= r.getScheme();
    set<Tuple>t=r.getTuples();
    for(auto a: t)
    {
        out<<"  ";
        for(int i=0; i<s.size(); i++)
        {
           out<<s[i]<<"="<<a[i]<<" ";
        }
        out<<endl;
    }
}

int findtup(Relation r, Tuple t)
{
    for (auto a: r.getTuples())
    {
        if (t== a)
        {
            return 1;
        }
    }
    return -1;
}
void Interpretor::tupleruleprint(vector<string> param, set<Tuple> t, vector<int> places, string id)
{
   Relation r= d.findrelation(id);
    vector<vector<string>>null;
    Relation r1=Relation(r.getScheme(), null);
    set<Tuple> s;
    for (auto a: t)
    {
        Tuple n;
        for(int i=0; i<param.size(); i++)
        {
            n.push_back(a[places[i]]);
        }
        if (findtup(r, n)==-1)
        {
        s.insert(n);
        }
    }
    r1.addTuple(s);
    r.addTuple(s);
    endprint(r1);
    sch[id]=r;
    d.addmembers(sch);
}

void Interpretor::rulePrint(Predicate p, string i)
{
    vector<int> places;
    vector<string>pars;
    for(int i=0; i<p.getParam().size(); i++)
    {
        for (int j=0; j<real.getScheme().size(); j++)
        {
            if(p.getParam()[i].getVal()==real.getScheme()[j])
            {
                places.push_back(j);
                pars.push_back(real.getScheme()[j]);
            }
        }
    }
    set<Tuple>t=real.getTuples();
   tupleruleprint(pars, t, places, i);
}

Scheme Interpretor::comboS(Scheme s1, Scheme s2)
{
    Scheme s=s1;
    int l=0;
    for (int j=0; j<s2.size(); j++)
    {
    for (int i=0; i<s1.size(); i++)
    {
        if (s1[i]==s2[j])
        {
            checkers.push_back(i);
            checkers.push_back(j);
            l=1;
        }
    }
        if (l==0)
        {
            s.push_back(s2[j]);
        }
        l=0;
    }
    return s;
}

Relation Interpretor:: join(Relation r2)
{
    Relation r =Relation();
    vector<vector<string>>filler;
    addTempscheme(ram, r2);
    Scheme s=comboS(real.getScheme(), r2.getTempScheme());
    r=Relation(s, filler);
   for(auto i: real.getTuples())
    {
        for(auto j: r2.getTuples())
        {
            if (joinable(i, j)==true)
            {
                r.newTuple(i, j, checkers);
            }
        }
    }
    
    return r;
}

bool Interpretor:: joinable (Tuple t1, Tuple t2)
{
    for(int i=0; i<checkers.size(); i+=2)
    {
        if (t1[checkers[i]]!=t2[checkers[i+1]])
        {
            return false;
        }
    }
    return true;
}

void Interpretor::addQueries()
{
    out<<"Query Evaluation"<<endl<<endl;
    for(int i=0; i<queries.size(); i++)
    {
        out<<queries[i].toString()<<"? ";
        convertpar(queries[i].getParam());
        set<Tuple> yn=d.qbool(queries[i].getId(), quer);
        if (yn.size()== 0)
        {
            out<<"No"<<endl<<endl;
        }
        else
        {
            out<<"Yes("<<yn.size()<<")"<<endl;
            string stuff =d.spr(queries[i].getId(), sch[queries[i].getId()].parlist, yn, quer);
            out<<stuff;
        }
    }
}

void Interpretor::convertpar(vector<Parameter>p)
{
    quer.clear();
    for (int i=0; i<p.size(); i++)
    {
        quer.push_back(p[i].getVal());
    }
}
