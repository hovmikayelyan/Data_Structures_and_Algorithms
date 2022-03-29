/**
 * @file dijkstra.cpp
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

int distance(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, int t)
{
  const int INF = numeric_limits<int>::max();
  vector<int> dist(adj.size(), INF);
  vector<bool> prev(adj.size(), 0);
  dist[s] = 0;

  for (size_t i = 0; i < adj.size(); i++)
  {
    int u = -1, MIN = INF;
    for (size_t j = 0; j < adj.size(); j++)
    {
      if (!prev[j] && dist[j] < MIN)
      {
        MIN = dist[j];
        u = j;
      }
    }
    if (u == -1)
      break;
    prev[u] = 1;

    for (size_t j = 0; j < adj[u].size(); j++)
    {
      int elem = adj[u][j];
      if (!prev[elem] && dist[u] + cost[u][j] < dist[elem])
      {
        dist[elem] = dist[u] + cost[u][j];
      }
    }
  }
  return dist[t] == INF ? -1 : dist[t];
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
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, cost, s, t);
  return 0;
}