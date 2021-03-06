#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <vector>

// predicted scores
// A: 4'004
// B: 9'137'020
// C: 2'611'946
// D: 4'974'364
// E: 1'396'614
// F: 1'648'704

// actual scores
// A: 2'002
// B: 4'568'510
// C: 1'305'973
// D: 2'487'182
// E: 698'307
// F: 824'352

class name_resolution
{
    std::map<std::string, int> id;
    std::vector<std::string> name;

   public:
    int get_id(const std::string& a) const { return id.at(a); }
    auto get_name(int i) const { return name.at(i); }
    void add(int i, std::string a)
    {
        name.push_back(a);
        id[a] = i;
    }
};

struct car_t
{
    // a car as given in the input
    const name_resolution& strdb;
    int id;
    std::vector<int> path;
    car_t(int car_id, const name_resolution& str_name)
        : id{car_id}, strdb{str_name}
    {
    }

    // additional information
    int time_to_finish{0};
    void add_path(int st, int L)
    {
        path.push_back(st);
        if (path.size() > 1)
            time_to_finish += L;
    }
    int start() const { return path[0]; }
};

struct sim_car_t : car_t
{
    // simulation state
    size_t pos{0};

    sim_car_t(const car_t& c) : car_t{c} { reset(); }

    void reset() { pos = 0; }
    int get_street() const { return path.at(pos); }
    void advance() { pos = std::min(pos + 1, path.size() - 1); }
    bool finish() const { return pos == (path.size() - 1); }
};

std::ostream& operator<<(std::ostream& os, const car_t& car)
{
    os << "car id: " << car.id << '\n';
    os << "path items: " << car.path.size() << '\n';
    for (auto st : car.path)
    {
        os << car.strdb.get_name(st) << ' ';
    }
    return os;
}

struct street_t
{
    int id;
    std::string name;
    int beg, end, L;
    street_t(int st_id) : id{st_id} {}

    // additional information
    int ncars{};  // cars that will use this street
    void count_car() { ncars++; }
    int get_cars() const { return ncars; }

    std::vector<int> qcars;  // cars starting here
    void queue_car(int i) { qcars.push_back(i); }
};

struct sim_street_t : street_t
{
    sim_street_t(const street_t& st) : street_t{st} { reset(); }
    std::queue<std::pair<int, int>> Q;
    void reset()
    {
        Q = std::queue<std::pair<int, int>>{};
        for (auto c : qcars)
            Q.push({0, c});
    }
    bool waiting(int time) const
    {
        if (Q.empty())
            return false;
        auto [t, car_id] = Q.front();
        return t > time ? false : true;
    }
};

struct node_t
{
    // fixed by input
    const name_resolution& strdb;
    int id;
    node_t(int i, const name_resolution& str_name) : id{i}, strdb{str_name} {}
    std::vector<int> in, out;  // in/out streets

    virtual bool active() const = 0;
    virtual int schedule_size() const = 0;
    virtual std::pair<int, int> get_schedule(int i) const = 0;
    virtual int green(int time) const = 0;
    virtual ~node_t() {}
};

std::ostream& operator<<(std::ostream& os, const node_t& no)
{
    os << "node id: " << no.id << '\n';
    os << "schedule:\n";
    int N_st = no.schedule_size();
    for (int i = 0; i < N_st; ++i)
    {
        auto [s, t] = no.get_schedule(i);
        os << no.strdb.get_name(s) << ' ' << t << '\n';
    }
    return os;
}

auto get_street(std::istream& is)
{
    static int str_id = 0;
    street_t str{str_id++};
    is >> str.beg >> str.end >> str.name >> str.L;
    return str;
}
auto get_car(std::istream& is,
             const name_resolution& strdb,
             std::vector<street_t>& streets)
{
    static int car_id = 0;
    car_t c{car_id++, strdb};
    int n;
    is >> n;
    for (int i = 0; i < n; ++i)
    {
        std::string name;
        is >> name;
        int st = strdb.get_id(name);
        c.add_path(st, streets[st].L);

        // count only cars that need to exit that street
        if (i < (n - 1))
            streets.at(st).count_car();
    }
    streets.at(c.start()).queue_car(c.id);
    return c;
}

template <typename T>
void output_plan(std::ostream& os, const std::vector<T>& graph)
{
    int count = std::count_if(graph.begin(), graph.end(),
                              [](const node_t& no) { return no.active(); });
    os << count << '\n';
    for (const node_t& no : graph)
        if (no.active())
        {
            int N_st = no.schedule_size();
            os << no.id << '\n';
            os << N_st << '\n';
            for (int i = 0; i < N_st; ++i)
            {
                auto [s, t] = no.get_schedule(i);
                os << no.strdb.get_name(s) << ' ' << t << '\n';
            }
        }
}

struct sim_node_t : node_t
{
    std::vector<std::pair<int, int>> schedule;  // for the output
    int T{};

    sim_node_t(int i, const name_resolution& strnames) : node_t{i, strnames} {}
    ~sim_node_t() override {}
    bool active() const override { return schedule_size() > 0; }
    int schedule_size() const override { return schedule.size(); }
    std::pair<int, int> get_schedule(int i) const override
    {
        return schedule[i];
    }
    int green(int time) const override
    {
        if (T == 0)
            throw std::runtime_error("node_t::green(): T=0");
        return schedule.at(time % T).first;
    }

    void set_simple_plan()
    {
        T = 0;
        schedule.resize(0);
        for (auto i : in)
        {
            schedule.push_back({i, 1});
            T += 1;
        }
    }

    void reset()
    {
        T = in.size();
        used.resize(T);
        schedule.resize(T);
        inv_in.clear();
        std::fill(used.begin(), used.end(), false);
        std::fill(schedule.begin(), schedule.end(), std::make_pair(-1, 1));

        for (size_t i = 0; i < in.size(); ++i)
            inv_in[in[i]] = i;
    }

    std::vector<bool> used;
    std::map<int, int> inv_in;
    void set_preference(int time, const std::vector<int>& vstr_id)
    {
        if (T == 0)
            throw std::runtime_error("node_t::green(): T=0");
        time %= T;
        if (schedule.at(time).first >= 0)
            return;

        for (auto str_id : vstr_id)
        {
            int pos = inv_in.at(str_id);
            if (used.at(pos))
                continue;

            used.at(pos) = true;
            schedule.at(time).first = str_id;
            break;
        }
    }
    void fill_schedule()
    {
        std::set<int> strs;
        for (size_t i = 0; i < in.size(); ++i)
            if (not used.at(i))
                strs.insert(in.at(i));

        for (auto& p : schedule)
            if (p.first < 0)
            {
                if (strs.empty())
                    throw std::runtime_error("no more streets available");
                p.first = *strs.begin();
                strs.erase(p.first);
            }
    }
};

template <typename T>
struct simulation_t
{
    const int T_max, Bonus;
    std::ostream& os;

    // statistics
    int score{};
    int cars_arrived{};
    int first = std::numeric_limits<int>::max();
    int last = -1;
    int min_score = std::numeric_limits<int>::max();
    int max_score = -1;

    std::vector<sim_car_t> cars;
    std::vector<sim_street_t> streets;
    std::vector<T> intersections;

    simulation_t(int t_max,
                 int bonus,
                 const std::vector<T>& in_tersections,
                 const std::vector<street_t>& in_streets,
                 const std::vector<car_t>& in_cars,
                 std::ostream& o)
        :

          T_max{t_max},
          Bonus{bonus},
          os(o),
          cars(in_cars.begin(), in_cars.end()),
          streets(in_streets.begin(), in_streets.end()),
          intersections(in_tersections.begin(), in_tersections.end())
    {
    }

    void run()
    {
        for (auto& c : cars)
            c.reset();
        for (auto& s : streets)
            s.reset();
        for (int time = 0; time < T_max; ++time)
        {
            std::set<int> busy_nodes;

            for (const auto& car : cars)
                if (not car.finish())
                {
                    const auto& st = streets.at(car.get_street());
                    busy_nodes.insert(st.end);
                }

            os << "Time: " << time << '\n';
            for (auto no_id : busy_nodes)
            {
                time_step(time, no_id);
            }
        }
    }
    void time_step(int time, int no_id)
    {
        auto& node = intersections.at(no_id);

        if (node.green(time) < 0)
            return;

        auto& st = streets.at(node.green(time));
        if (not st.waiting(time))
            return;

        auto [t, car_id] = st.Q.front();
        st.Q.pop();
        auto& car = cars.at(car_id);

        os << "node id: " << node.id << '\n';
        os << "green light on street: " << node.green(time) << '\n';
        os << "size of queue " << st.Q.size() << '\n';
        os << "last element: time=" << t << " car=" << car.id << '\n';

        car.advance();
        auto& new_st = streets[car.get_street()];

        // assuming that new_st lies in the out list of node
        // guaranteed by the dataset

        if (car.finish())
        {
            os << "car " << car.id << " finished moving to end_list on street "
               << new_st.id << " " << new_st.name << '\n';
            anotate_score(time + new_st.L);
        }
        else
        {
            os << "car " << car.id << " moving to queue on street " << new_st.id
               << '\n';
            new_st.Q.push({time + new_st.L, car.id});
        }
    }
    void anotate_score(int time)
    {
        if (time > T_max)
            return;
        int pts = Bonus + T_max - time;
        score += pts;
        cars_arrived++;
        first = std::min(first, time);
        last = std::max(last, time);
        min_score = std::min(min_score, pts);
        max_score = std::max(max_score, pts);
        os << "Anotate score=" << pts << " at time=" << time << '\n';
    }
    void set_plan_0()
    {
        for (auto& i : intersections)
            i.set_simple_plan();
    }
    void set_plan_1()
    {
        for (auto& no : intersections)
            no.reset();
        for (auto& c : cars)
            c.reset();
        for (auto& s : streets)
            s.reset();
        for (int time = 0; time < T_max; ++time)
        {
            std::set<int> busy_nodes;

            for (const auto& car : cars)
                if (not car.finish())
                {
                    const auto& st = streets.at(car.get_street());
                    busy_nodes.insert(st.end);
                }

            for (auto no_id : busy_nodes)
            {
                // set a prefered light if possible
                auto& no = intersections.at(no_id);
                std::vector<int> waiting_str;
                for (auto str_id : no.in)
                {
                    auto& str = streets.at(str_id);
                    if (str.waiting(time))
                        waiting_str.push_back(str_id);
                }
                if (waiting_str.empty())
                    continue;
                if (no.green(time) < 0)
                    no.set_preference(time, waiting_str);
                time_step(time, no_id);
            }
        }

        for (auto& no : intersections)
        {
            no.fill_schedule();
        }
    }
};

using namespace std;
int main()
{
    // read input data
    int T_max, N_nodes, N_streets, N_cars, Bonus;
    cin >> T_max >> N_nodes >> N_streets >> N_cars >> Bonus;

    vector<street_t> streets;
    vector<car_t> cars;
    name_resolution strdb;
    for (int i = 0; i < N_streets; ++i)
    {
        streets.push_back(get_street(cin));
        strdb.add(streets.back().id, streets.back().name);
    }
    for (int i = 0; i < N_cars; ++i)
    {
        cars.push_back(get_car(cin, strdb, streets));
    }

    // construct the graph
    vector<sim_node_t> intersections;
    for (int i = 0; i < N_nodes; ++i)
    {
        intersections.emplace_back(i, strdb);
    }
    for (auto& st : streets)
        if (st.get_cars())
        {  // count only streets that have cars
            intersections[st.beg].out.push_back(st.id);
            intersections[st.end].in.push_back(st.id);
        }

    ofstream log("log");
    simulation_t sim(T_max, Bonus, intersections, streets, cars, log);

    // create some plan
    // sim.set_plan_0();
    sim.set_plan_1();

    // output plan
    output_plan(cout, sim.intersections);

    // run simulation
    sim.run();

    // output scores
    cerr << "score: " << sim.score << '\n';
    cerr << "num cars arrivals: " << sim.cars_arrived << '\n';
    cerr << "earliest arrival: " << sim.first << '\n';
    cerr << "max score: " << sim.max_score << '\n';
    cerr << "last arrival: " << sim.last << '\n';
    cerr << "min score: " << sim.min_score << '\n';

    return 0;
}
