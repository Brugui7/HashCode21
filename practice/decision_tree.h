#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <map>

template<typename weight_t, typename key_t>
class decision_tree
{
    using pair_t = std::pair<weight_t,key_t>;
    
    
    struct node
    {
        pair_t wk;
        weight_t sum{};
        
        node(const pair_t& N):
            wk{N},
            sum{wk.first}
        {
        }
    };
    
    std::map<key_t,size_t> position;
    std::vector<node> data;
    
    void update(int pos)
    {
        for(;pos;pos/=2)
        {
            int l=pos*2, r = l+1;
            data[pos-1].sum = data[pos-1].wk.first ;
            
            if(l<=data.size()) data[pos-1].sum += data[l-1].sum;
            if(r<=data.size()) data[pos-1].sum += data[r-1].sum;
        }
    }
    
    void remove(size_t pos)
    {
       size_t a = pos, b = data.size();
       key_t ka = data[a-1].wk.second, kb=data[b-1].wk.second;
       position[kb] = a;
       // position[ka] = b;
       position.erase(ka);
      
      
       if(a<=0 or a>data.size()) return;
       std::swap(data[a-1],data[b-1]);
       data.pop_back();
       update(a);
       update(b/2);
    }
    public:
    class iterator
    {
       decision_tree& tree;
       
       public:
       size_t pos;
       
       iterator(decision_tree& t,size_t p):
            tree{t}, pos{p}
       {}
       
       pair_t& operator * ()
       {
            return tree.data[pos-1].wk;
       }
       
       pair_t* operator -> ()
       {
            return &tree.data[pos-1].wk;
       }
    };
    
    decision_tree(){  }
    auto size()const {return data.size();}
    
    void insert(const pair_t& N)
    {
        data.emplace_back(N);
        position[N.second] = data.size();
        update(data.size());
    }
    
    weight_t sum() const
    {
        if(data.size()==0)
            return weight_t{};
        return data[0].sum;
    }
    
    iterator end()
    {
        return iterator(*this,0);
    }
    iterator begin()
    {
        return iterator(*this,1);
    }
    
    iterator sample(weight_t w)
    {
       if(w<0)
            return begin();
       
       // 0<= w < sum all weights
       if( w >= sum())
            return end();
       
       int pos = 1;
       while( w >= data[pos-1].wk.first )
       {
            int l = pos*2, r = l+1;
            w-= data[pos-1].wk.first;
            if(w<data[l-1].sum)
                pos = l;
            else
            {
                w -= data[l-1].sum;
                pos = r;
            }
       }
       assert(pos>0 and pos<= data.size());
       return iterator(*this,pos);
    }
    void erase(iterator i)
    {
        remove(i.pos);
    }
    void erase(key_t k)
    {
        auto it = find(k);
        erase(it);
    }
    
    iterator find(key_t k)
    {
        auto it = position.find(k);
        if(it == position.end())
            return end();
        return iterator(*this,it->second);
    }
    /* 
    void print()const
    {
        std::cerr << "size = " << size() << " sum = " << sum() << '\n';
        for(int i=0;i<size();++i)
        {
            std:: cerr << (i+1) << ' ' << data[i].key_val.first << ' ' <<
            data[i].key_val.second << ' '  << data[i].sum << '\n';
        }
    }
    */
};
