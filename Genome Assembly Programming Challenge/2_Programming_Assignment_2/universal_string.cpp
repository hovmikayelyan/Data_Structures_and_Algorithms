/**
 * @file universal_string.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief
 * @version 0.1
 * @date 2022-04-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;
#define VECT vector<string>

VECT createEulerCycle(map<string, set<string>> graph)
{
  stack<string> vertices;
  VECT path;
  vertices.push(graph.begin()->first);
  string selected = vertices.top();

  while (!vertices.empty())
  {
    selected = vertices.top();
    if (!graph[selected].empty())
    {
      vertices.push(*graph[selected].begin());
      graph[selected].erase(graph[selected].begin());
      continue;
    }
    path.push_back(selected);
    vertices.pop();
  }

  reverse(path.begin(), path.end());
  return path;
}

map<string, set<string>>
developDeBruijnGraph(const int k, const int n)
{
  auto calculate_overlap = [](const auto &a, const auto &b, int mer)
  {
    for (size_t i = 1; i < a.size(); ++i)
      if (a[i] != b[i - 1])
        return false;
    return true;
  };

  VECT univ;
  map<string, set<string>> graph;

  for (size_t i = 0; i < n; ++i)
    univ.emplace_back(bitset<16>{i}.to_string().substr(16 - k));

  for (auto &m1 : univ)
    for (auto &m2 : univ)
      if (calculate_overlap(m1, m2, k - 1))
        graph[m1.substr(0, k - 1)].emplace(m2.substr(0, k - 1));

  return graph;
}

void output_kUniversalCircularString(const VECT &cycle, const int k)
{
  for (size_t i = 0; i < cycle.size() - 1; ++i)
  {
    const auto &s = cycle[i];
    cout << s.substr(0, s.size() - (k - 2));
  }
  cout << endl;
}

int main()
{
  int k;
  cin >> k;
  int n = pow(2, k);

  const auto cycle = createEulerCycle(developDeBruijnGraph(k, n));
  output_kUniversalCircularString(cycle, k);

  return 0;
}