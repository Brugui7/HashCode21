#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
#include <cassert>
#include <list>

// score: 1001
// score: 4565642
// score: 1231878
// score: 969685
// score: 661797
// score: 455737

class name_resolution
{
    std::map<std::string,int> id;
    std::vector<std::string> name;
    
    public:
    int get_id(const std::string& a)const
    {
        return id.at(a);
    }
    auto get_name(int i)const
    {
        return name.at(i);
    }
    void add(int i,std::string a)
    {
        name.push_back(a);
        id[a]=i;
    }
};

struct street_t;

struct car_t
{
    //
    const name_resolution& strdb;
    int id;
    int pos{0};
    std::vector<int> path;
    car_t(const name_resolution& str_name):
        strdb{str_name}
    {}
    void add_path(std::string name)
    {
        path.push_back(strdb.get_id(name));
    }
    int get_street()const
    {
        return path.at(pos);
    }
    void advance()
    {
        ++pos;
    }
    bool finish()const
    {
        return pos==(path.size()-1);
    }
    static int id_counter;
    
};
    std::ostream& operator << (std::ostream& os, const car_t& car)
    {
        os << "car id: " << car.id << '\n';
        os << "path items: " << car.path.size() << '\n';
        for(auto st : car.path)
        {
            os << car.strdb.get_name(st) << ' ';
        }
        return os ;
    }

struct street_t
{
    //
    int id;
    std::string name;
    int beg, end, L;
    
    std::queue< std::pair<int,int> > Q;
    
    bool operator < (const street_t& that)const
    {
        return name < that.name;
    }
    static int id_counter;
};

int street_t::id_counter =0;
int car_t::id_counter =0;

struct node_t
{
    const name_resolution& strdb;
    int id;
    node_t(int i,const name_resolution& str_name):
        id{i},
        strdb{str_name}
    {}
    std::vector<int> in,out;
    std::vector< std::pair<int,int> > schedule;
    
    int T{};
    
    void insert_schedule(int i,int t)
    {
        if(t<=0) 
            throw std::runtime_error(
            "node_t::insert_schedule(): t<=0 is not allowed");
        schedule.push_back({i,t});
        T += t;
    }
    
    bool active()const{return T>0;}
    
    int green(int time)const // returns street id
    {
        // TODO: an efficient way to get the light
        if(T==0) 
            throw std::runtime_error(
            "node_t::green(): T=0");
        if(schedule.size()==0) 
            throw std::runtime_error(
            "node_t::green(): no green lights are scheduled");
        time %= T;  
        for(auto [s,t]: schedule)
        {
            if(time<t)
                return s;
            time-=t;
        }
        if(schedule.size()==0) 
            throw std::runtime_error(
            "node_t::green(): ERROR no street scheduled");
        return -1;
    }
};

std::ostream& operator << (std::ostream& os, const node_t& node)
{
    os << "node id: " << node.id << '\n';
    os << "schedule:\n"; 
    for(auto [i,t] : node.schedule)
    {
        os <<  node.strdb.get_name(i)  <<" time=" <<t<<'\n';
    }
    return os;
}

auto get_graph(int N_nodes, 
    const std::vector<street_t>& streets,
    const name_resolution& str_name
    )
{
    std::vector<node_t> graph;
    
    for(int i=0;i<N_nodes;++i)
        graph.emplace_back(i,str_name);
    
    // construct graph
    for(const auto& st : streets)
    {
        graph[st.beg].out.push_back(st.id);
        graph[st.end].in.push_back(st.id);
    }
    
    // TODO plan the lights: homogeneus assignment
    for(auto &node : graph)
    {
        for(auto st : node.in)
            node.insert_schedule(st,1);
    }
    return graph;
}

struct simulation_t
{
    const int T_max, Bonus;
    int score{};
    int cars_arrived{};
    int first=std::numeric_limits<int>::max();
    int last = -1;
    int min_score=std::numeric_limits<int>::max();
    int max_score=-1;
    std::ostream &os;
    std::set<int> busy_nodes; 
    
    simulation_t(int t_max,int bonus, 
        const std::vector<node_t>& graph,
        std::vector<street_t>& streets,
        std::vector<car_t>& cars,
        std::ostream& o):
        
        T_max{t_max},Bonus{bonus},
        os(o)
    {
        for(int time=0;time<T_max;++time)
        {   
           // move cars at time steps, ignore empty intersections
           busy_nodes.clear();
           
           for(const auto & car : cars)
           if(not car.finish())
           {
                const auto &st = streets[car.get_street()];
                busy_nodes.insert(st.end);
           }
           
           
           os << "Time: " << time << '\n';
           for(auto no_id : busy_nodes)
           {
                auto & node = graph[no_id];
                auto &st = streets [node.green(time) ]; 
                if(st.Q.empty())
                    continue;
                auto [t,car_id] = st.Q.front();       
                auto &car = cars[car_id];
                
                os << "node id: " << node.id << '\n';
                os << "green light on street: " << node.green(time) << '\n';
                os << "size of queue " << st.Q.size() <<'\n';
                os << "last element: time=" << t << " car=" << car.id <<'\n';
                
                if(t>time)
                {
                    continue;
                }    
                
                st.Q.pop();
                car.advance();
                auto &new_st = streets [car.get_street() ];
                
                if(car.finish())
                {
                    os << "car " << car.id << " finished moving to end_list on street " 
                        << new_st.id << " " << new_st.name <<'\n';
                    anotate_score(time + new_st.L);
                }
                else
                {
                    os << "car " << car.id <<" moving to queue on street " 
                        << new_st.id <<'\n';
                    new_st.Q.push({time+new_st.L,car.id});
                }
                
           }
        }
    }
    void anotate_score(int time)
    {
        if(time>T_max)return;
        int pts = Bonus + T_max - time;
        score += pts;
        cars_arrived++;
        first = std::min(first,time);
        last = std::max(last,time);
        min_score = std::min(min_score,pts);
        max_score = std::max(max_score,pts);
        os << "Anotate score=" << pts << " at time="<<time<<'\n';
    }
};

auto get_street(std::istream& is)
{
    street_t str;
    is >> str.beg >> str.end >> str.name >> str.L;
    str.id = str.id_counter++;
    return str;
}
auto get_car(std::istream& is,
    const name_resolution& strdb)
{
    car_t c{strdb};
    int n; is>>n;
    c.id = c.id_counter++;
    c.path.reserve(n);
    while(n--)
    {
        std::string name;is>>name;
        c.add_path(name);
    }
    return c;
}

void output_plan(std::ostream& os,
    const std::vector<node_t>& graph,
    const std::vector<street_t> &streets)
{
    int count=std::count_if(graph.begin(),graph.end(),
        [](const node_t& no){ return no.active() ; } );
    os << count << '\n';
    for(const auto &no : graph)
    if(no.active())
    {
        os << no.id << '\n';
        os << no.schedule.size() << '\n';
        for(auto [s,t] : no.schedule )
        {
            os << streets[s].name << ' ' << t << '\n';
        }
    }
}

using namespace std;
int main()
{
    // read input data
    int T_max, N_nodes, N_streets, N_cars, Bonus;
    cin >> T_max >> N_nodes >> N_streets >> N_cars >> Bonus;
    
    vector<street_t> streets;
    vector<car_t> cars;
    name_resolution strdb;
    for(int i=0;i<N_streets;++i)
    {
        streets.push_back(get_street(cin));
        strdb.add(streets.back().id,streets.back().name);
    }
    for(int i=0;i<N_cars;++i)
    {
        car_t c = get_car(cin,strdb);
        cars.push_back(c);
        auto &st = streets[c.get_street()];
        st.Q.push({0,i}); 
    }
    // construct traffic light rules 
    vector<node_t> city = get_graph(N_nodes,streets,strdb);
    
    output_plan(cout,city,streets);
    
    // run simulation
    
    ofstream log("/dev/null");
    //ofstream log("log");
    
    simulation_t sim(T_max,Bonus,city,streets,cars,log);
    
    // output scores
    cerr << "score: " << sim.score << '\n';
    cerr << "num cars arrivals: " << sim.cars_arrived << '\n';
    cerr << "earliest arrival: " << sim.first << '\n';
    cerr << "max score: " << sim.max_score << '\n';
    cerr << "last arrival: " << sim.last << '\n';
    cerr << "min score: " << sim.min_score << '\n';
    
    return 0;
}
