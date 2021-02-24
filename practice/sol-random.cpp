#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <bitset>
#include <random>
#include <cmath>
#include "decision_tree.h"

constexpr double ALPHA = 2.0;
constexpr int MAX_SEARCH = 1000;

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
};

struct pizzaDB
{
    int pizza_index{0};
    map<string,int> mingredients;
    vector<pizza_t> vpizza;
    vector<double> weight;
    decision_tree<double,int> T;
    
    default_random_engine rng;
    uniform_real_distribution<double> U;
    
    
    void add(const vector<string>& pizza)
    {
        pizza_t p{pizza_index++};
        for(int i=0;i<pizza.size();++i)
        {
            size_t val{mingredients.size()};
            auto it = mingredients.find(pizza[i]);
            if(it!=mingredients.end())
                val = it->second;
            else
                mingredients.insert({pizza[i],val});    
            p[val]=1;
        }
        
        const double w = std::pow(p.count(),ALPHA);
        vpizza.push_back(p);
        weight.push_back(w);
        T.insert({w,p.index});
    }
    
    pizzaDB(int n):
        rng(13), U(0.0,1.0)
    {
        vpizza.reserve(n);
        weight.reserve(n);
    }
    
    const auto size() const
    {
        return T.size();
    }
    
    auto deliver(int n)
    {
        vector<int> best_sol(n);
        int best_score=-1;
        
        
        
        for(int trial=0;trial<MAX_SEARCH;++trial)
        {
            vector<int> sol(n);
            
            ingredient_set ing;
            for(int i=0;i<n;++i)
            {
                double r = U(rng) * T.sum();
                
                // cerr << "r=" << r << " T.sum()=" << T.sum() << '\n';
                
                //T.print();
                auto it = T.sample(r);
                
                int index = it->second;
                
                ing |= vpizza[index];
                sol[i] = index;
                
                T.erase(it);
            }
            
            int score = ing.count();
            if(score>best_score)
            {
                best_sol = sol;
                best_score = score;
            }
            
            for(auto i : sol)
            {
                T.insert({weight[i],i});
            }
        }
        
        for(auto i: best_sol)
            T.erase(i);
        
        return make_pair(best_score,best_sol);
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
        vector<string> ving(ningredients);
        for(auto &ing : ving)
            cin>>ing;
        pdb.add(ving);
    }
    
    int64_t score =0;
    
    vector< vector<int> > vdeliver;
    
    for(int i=nteams.size()-1;i>=0;--i)
    while(nteams[i]--)
    {
        const int npeople = i+2;
        if(pdb.size()<npeople) break; // no more pizza left
        auto [n_ing,pizzas] = pdb.deliver(npeople);
        score += n_ing*n_ing;
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
    return 0;
}
