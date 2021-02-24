#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

template<typename key_t, typename value_t>
class decision_tree
{
    using pair_t = std::pair<key_t,value_t>;
    
    
    struct node
    {
        pair_t key_val;
        key_t sum{};
        
        node(const pair_t& N):
            key_val{N},
            sum{key_val.first}
        {
        }
    };
    
    std::vector<node> data;
    
    
    void update(int pos)
    {
        for(;pos;pos/=2)
        {
            int l=pos*2, r = l+1;
            data[pos-1].sum = data[pos-1].key_val.first ;
            
            if(l<=data.size()) data[pos-1].sum += data[l-1].sum;
            if(r<=data.size()) data[pos-1].sum += data[r-1].sum;
        }
    }
    
    public:
    class iterator
    {
       decision_tree& tree;
       
       public:
       int pos;
       
       iterator(decision_tree& t,int p):
            tree{t}, pos{p}
       {}
       
       pair_t& operator * ()
       {
            return tree.data[pos-1].key_val;
       }
       
       pair_t* operator -> ()
       {
            return &tree.data[pos-1].key_val;
       }
    };
    decision_tree(){  }
    auto size()const {return data.size();}
    
    void insert(const pair_t& N)
    {
        data.emplace_back(N);
        update(data.size());
    }
    
    key_t sum() const
    {
        if(data.size()==0)
            return key_t{};
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
    
    iterator find(key_t k)
    {
       if(k<0)
            return begin();
       
       // 0<= k < sum all keys
       if( k >= sum())
            return end();
       
       int pos = 1;
       while( k >= data[pos-1].key_val.first )
       {
            int l = pos*2, r = l+1;
            k-= data[pos-1].key_val.first;
            if(k<data[l-1].sum)
                pos = l;
            else
            {
                k -= data[l-1].sum;
                pos = r;
            }
       }
       assert(pos>0 and pos<= data.size());
       return iterator(*this,pos);
    }
    /*
    void erase(int pos)
    {
        erase(iterator(*this,pos));
    }
    */
    
    void erase(iterator i)
    {
       if(i.pos<=0 or i.pos>data.size()) return;
       std::swap(data[i.pos-1],data.back());
       data.pop_back();
       update(data.size());
       update(i.pos);
    }
    /*
    void print()const
    {
        std::cout << "size = " << size() << " sum = " << sum() << '\n';
        for(int i=0;i<size();++i)
        {
            std:: cout << (i+1) << ' ' << data[i].key_val.first << ' ' <<
            data[i].key_val.second << ' '  << data[i].sum << '\n';
        }
    }
    */
};
