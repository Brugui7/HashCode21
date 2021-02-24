#include <iostream>
#include <set>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
    set<string> I;
    int N;
    array<int,3> M;
    cin>>N;
    int max_ing=-1;
    for(auto &m : M)cin>>m;
    for(int i=0;i<N;++i)
    {
        int n; cin>>n;
        max_ing = max(max_ing,n);
        for(int j=0;j<n;++j)
        {
            string s;cin>>s;
            I.insert(s);
        }
    }
    cout << "#pizzas = " << N << '\n';
    cout << "#ingredients = " << I.size() << '\n';
    cout << "max ingredients = " << max_ing << '\n';
    
    return 0;
}
