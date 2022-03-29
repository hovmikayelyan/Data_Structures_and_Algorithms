/**
 * @file negative_cycle.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

const int inf = numeric_limits<int>::max();

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost)
{
  vector<long> dist(adj.size(), inf);
  dist[0] = 0;
  for (size_t k = 1; k < adj.size(); k++)
  {
    for (size_t i = 0; i < adj.size(); i++)
    {
      for (size_t j = 0; j < adj[i].size(); j++)
      {
        int next = adj[i][j];
        if (dist[i] + cost[i][j] < dist[next])
          dist[next] = dist[i] + cost[i][j];
      }
    }
  }

  for (size_t i = 0; i < adj.size(); i++)
  {
    for (size_t j = 0; j < adj[i].size(); j++)
    {
      int next = adj[i][j];
      if (dist[i] + cost[i][j] < dist[next])
        return 1;
    }
  }
  return 0;
}

int main()
{
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  vector<vector<int>> cost(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  cout << negative_cycle(adj, cost);
}