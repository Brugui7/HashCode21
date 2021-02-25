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

constexpr double ALPHA = 1.0;
constexpr int SEARCH_ITERATIONS = 1000;
constexpr int SEARCH_SPACE = 20;

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
            that.count() < this->count();
    }
};

struct pizzaDB
{
    int pizza_index{0},last_pizza{-1};
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
        
        vpizza.push_back(p);
        last_pizza = vpizza.size()-1;
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
        
        
        
        for(int trial=0;trial<SEARCH_ITERATIONS;++trial)
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
        for(int i=0;i<n and last_pizza>=0;++i)
        {
            load_last_pizza();
        }
        
        return make_pair(best_score,best_sol);
    }
    void sort()
    {
        std::sort(vpizza.begin(),vpizza.end());
    }
    void compute_weights()
    {
        for(const auto& p: vpizza)
        {
            double w = std::pow(p.count(),ALPHA);
            weight.push_back(w);
        }
    }
    void load_last_pizza()
    {
        const auto &p = vpizza[last_pizza];
        const auto &w = weight[last_pizza];
        T.insert({w,p.index});
        --last_pizza;
    }
    void load_pizzas()
    {  
        for(int i=0;i<SEARCH_SPACE and last_pizza>=0;++i)    
        {
            load_last_pizza();
        }
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
    
    pdb.sort();
    pdb.compute_weights();
    pdb.load_pizzas();
    
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
