#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

constexpr double PERIOD = 10.0;
constexpr double ALPHA = 2.0;

struct intersection_t
{
    vector<int> in, out;
    int id;
};

struct street_t
{
    int beg, end, L;
    string name;
    int count{};
};

int main()
{
    map<string, int> street_name;
    int D, I, S, V, F;
    cin >> D >> I >> S >> V >> F;

    vector<intersection_t> intersection(I);
    vector<street_t> street(S);

    for (int i = 0; i < I; ++i)
        intersection[i].id = i;

    for (int i = 0; i < S; ++i)
    {
        auto& s = street[i];
        cin >> s.beg >> s.end >> s.name >> s.L;

        street_name[s.name] = i;
        intersection[s.beg].out.push_back(i);
        intersection[s.end].in.push_back(i);
    }

    for (int i = 0; i < V; ++i)
    {
        int n;
        cin >> n;
        string name;
        for (int j = 0; j < n; ++j)
        {
            cin >> name;
            int s = street_name[name];
            street[s].count++;
        }
    }

    // solution

    for (int i = 0; i < intersection.size();)
    {
        auto& in_vec = intersection[i].in;
        for (int j = 0; j < in_vec.size();)
        {
            int s_id = in_vec[j];
            if (street[s_id].count)
                ++j;
            else
            {
                swap(in_vec[j], in_vec.back());
                in_vec.pop_back();
            }
        }

        if (in_vec.size())
            ++i;
        else
        {
            swap(intersection[i], intersection.back());
            intersection.pop_back();
        }
    }

    cout << intersection.size() << '\n';
    for (auto& i : intersection)
    {
        cout << i.id << '\n';
        auto& in_vec = i.in;
        cout << in_vec.size() << '\n';

        double tot = 0;
        for (auto j : in_vec)
            tot += pow(street[j].count, ALPHA);

        for (auto j : in_vec)
        {
            cout << street[j].name << ' '
                 << min(D, max(1, int{floor(pow(street[j].count, ALPHA) *
                                            PERIOD / tot)}))
                 << '\n';
        }
    }

    return 0;
}
