#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Pizza {
  int id;
  vector<int> ingredients;
};

struct Team {
  int members;
  vector<Pizza> pizzas;
};

string ingredient;
vector<Team> teams;
vector<Pizza> pizzas;
unordered_map<string, int> h;
int M, T[5], I, cnt = 1;

void readInput() {
  cin >> M >> T[2] >> T[3] >> T[4];
  for(int i = 0;i < M;i++) {
    Pizza pizza;
    pizza.id = i;

    cin >> I;
    for(int j = 0;j < I;j++) {
      cin >> ingredient;
      if (!h[ingredient]) h[ingredient] = cnt++;
      pizza.ingredients.push_back(h[ingredient]);
    }

    pizzas.push_back(pizza);
  }
}

void createTeams() {
  for(int i = 2;i < 5;i++) {
    for(int j = 0;j < T[i];j++) {
      Team team;
      team.members = i;
      teams.push_back(team);
    }
  }
}

int main(int argc, char const *argv[])
{
  readInput();
  createTeams();
  
  return 0;
}
