#include <iostream>
#include <set>
#include <string>
#include <array>
using namespace std;

int main()
{
    set<string> I;
    int N;
    array<int,3> M;
    cin>>N;
    for(auto &m : M)cin>>m;
    for(int i=0;i<N;++i)
    {
        int n; cin>>n;
        for(int j=0;j<n;++j)
        {
            string s;cin>>s;
            I.insert(s);
        }
    }
    cout << "#pizzas = " << N << '\n';
    cout << "#ingredients = " << I.size() << '\n';
    
    return 0;
}
