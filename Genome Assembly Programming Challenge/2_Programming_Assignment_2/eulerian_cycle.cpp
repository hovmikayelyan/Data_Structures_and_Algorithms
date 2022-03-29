/**
 * @file eulerian_cycle.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief
 * @version 0.1
 * @date 2022-03-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;
#define VECT vector<int>

bool check_degrees(const VECT &_inside, const VECT &_outside)
{
  assert(_inside.size() == _outside.size());
  for (size_t i = 0; i < _inside.size(); i++)
    if (_inside[i] != _outside[i])
      return false;
  return true;
}

VECT make_euler_cycle(vector<VECT> graph)
{
  VECT desk;
  stack<int> verteces;

  verteces.push(0);
  int current = 0;

  while (!verteces.empty())
  {
    current = verteces.top();
    if (!graph[current].empty())
    {
      verteces.push(graph[current].back());
      graph[current].pop_back();
      continue;
    }
    desk.emplace_back(current);
    verteces.pop();
  }

  reverse(desk.begin(), desk.end());
  desk.pop_back();

  return desk;
}

int main()
{
  // main start
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  // input numbers
  int num_verteces, num_edges;
  cin >> num_verteces >> num_edges;

  vector<VECT> graph(num_verteces);

  // both are vector ints
  VECT _inside(num_verteces);
  VECT _outside(num_verteces);

  for (int i = 0; i < num_edges; ++i)
  {
    int from, to;
    cin >> from >> to;
    graph[--from].emplace_back(--to);
    ++_inside[to];
    ++_outside[from];
  }

  // return 0 if isnt chekced
  if (!check_degrees(_inside, _outside))
  {
    cout << 0 << endl;
    return 0;
  }

  // move ang get graph back
  auto cycle = make_euler_cycle(move(graph));

  cout << 1 << '\n';
  for (auto v : cycle)
    cout << v + 1 << ' ';
  cout << endl;

  return 0;
}