#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <bitset>

#define __fast_io__ \
    std::ios_base::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
using namespace std;

constexpr int MAX_INGREDIENTS=10'000;
typedef bitset<MAX_INGREDIENTS> ingredient_set;

struct pizza_t : ingredient_set
{
    int index;
    
    pizza_t(int i): index{i}
    {}
    
    bool operator<(const pizza_t& that)const
    {
        return that.count() == this->count() ? that.index < this->index :
            this->count() < that.count();
    }
};

struct pizzaDB
{
    int pizza_index{0};
    map<string,int> mingredients;
    vector<pizza_t> vpizza;
    
    void add(const vector<string>& pizza)
    {
        pizza_t p{pizza_index++};
        for(int i=0;i<pizza.size();++i)
        {
            int val{mingredients.size()};
            auto it = mingredients.find(pizza[i]);
            if(it!=mingredients.end())
            {
                val = it->second;
            }else
            {
                mingredients.insert({pizza[i],val});    
            }
            p[val]=1;
        }
        vpizza.push_back(p);
    }
    
    pizzaDB(int n)
    {
        vpizza.reserve(n);
    }
    
    const auto size() const
    {
        return vpizza.size();
    }
    
    auto deliver(int n)
    {
        ingredient_set ning;
        vector<int> vp(n);
        
        {
            n--;
            const auto &p = vpizza.back();
            vp[n] = p.index;
            ning = p;
            vpizza.pop_back();
        }
        
        
        while(n--)
        {
            int idx_best = vpizza.size()-1;
            ingredient_set ing_best{ning};
            const size_t max_search = 1000;
            
            for(int i=0;i< min(max_search,vpizza.size());++i)
            {
                int idx = vpizza.size()-1-i;
                ingredient_set tmp{ning};
                const auto &p = vpizza[idx];
                
                tmp |= p;
                
                if(ing_best.count()<tmp.count())
                {
                    idx_best = idx;
                    ing_best = tmp;
                }
            }
            
            ning = ing_best;
            vp[n]= vpizza[idx_best].index;
            vpizza[idx_best] = vpizza.back();
            vpizza.pop_back();
        }
        
        return make_pair(ning.count(),vp);
    }
    
    void sort()
    {
        std::sort(vpizza.begin(),vpizza.end());
        std::cerr << "first pizza: " << vpizza[0].count () << '\n';
    }
};

int main()
{
    __fast_io__;
    int npizzas;
    array<int,3> nteams;
    
    cin>>npizzas;
    for(auto &n: nteams) cin>>n;
    
    pizzaDB pdb(npizzas);
    
    for(int i=0;i<npizzas;++i)
    {
        int ningredients; 
        cin>>ningredients;
        vector<string> ving{ningredients};
        for(auto &ing : ving)
            cin>>ing;
        pdb.add(ving);
    }
    
    int64_t score =0;
    
    vector< vector<int> > vdeliver;
    
    pdb.sort();
    
    for(int i=nteams.size()-1;i>=0;--i)
    while(nteams[i]--)
    {
        const int npeople = i+2;
        if(pdb.size()<npeople) break; // no more pizza left
        auto [diff_ingred,pizzas] = pdb.deliver(npeople);
        score += diff_ingred*diff_ingred;
        
        vdeliver.push_back(pizzas);
    }
    
    cout << vdeliver.size() << '\n';
    for(auto del : vdeliver)
    {
        cout << del.size();
        for(auto i: del)
            cout << ' ' << i;
        cout << '\n';
    }
    
    cerr << "score: " << score << '\n';
    cerr << "ingredient size: " << pdb.mingredients.size() << '\n';
    cerr << "npizzas: " << npizzas << '\n';
    cerr << "npizzas x ningredients: " << npizzas*pdb.mingredients.size() <<
    '\n';
    
    return 0;
}
