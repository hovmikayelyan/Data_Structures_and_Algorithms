/**
 * @file reachability.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief
 * Main Program
 */

void explore(vector<vector<int>> &adj, vector<bool> &visited, int u, int v)
{
  visited[u] = 1;
  for (auto elem : adj[u])
  {
    if (!visited[elem])
    {
      explore(adj, visited, elem, v);
    }
  }
}

int main()
{
  size_t n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n, vector<int>());

  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  int u, v;
  cin >> u >> v;
  vector<bool> visited(n, 0);

  explore(adj, visited, u - 1, v - 1);

  if (visited[v - 1])
  {
    cout << 1;
  }
  else
  {
    cout << 0;
  }

  return 0;
}
