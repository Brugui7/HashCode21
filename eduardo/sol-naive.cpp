#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct intersection_t
{
    vector<int> in,out;
};

struct street_t
{
    int beg,end,L;
    string name;
};

int main()
{
    int D,I,S,V,F;
    cin>>D>>I>>S>>V>>F;
    
    vector<intersection_t> intersection(I);
    vector<street_t> street(S);
    
    for(int i=0;i<S;++i)
    {
        auto &s = street[i];
        cin>>s.beg>>s.end>>s.name>>s.L;
        
        intersection[s.beg].out.push_back(i);
        intersection[s.end].in.push_back(i);
    }
    
    for(int i=0;i<V;++i)
    {
        int n;cin>>n;
        string name;
        for(int j=0;j<n;++j)
            cin>>name;
    }
    
    // solution
    cout << I << '\n';
    for(int i=0;i<I;++i)
    {
        cout << i << '\n';
        cout << intersection[i].in.size() << '\n';
        
        for(auto j : intersection[i].in)
        {
            cout << street[j].name << ' ' << 1 << '\n';
        }
    }
    
    return 0;
}
