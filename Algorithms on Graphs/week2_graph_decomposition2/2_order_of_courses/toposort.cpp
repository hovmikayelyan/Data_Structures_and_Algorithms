/**
 * @file toposort.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-15
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

void dfs(vector<vector<int>> &adj, int x, vector<int> &visited, vector<int> &order)
{

  visited[x] = 1;

  for (auto elem : adj[x])
  {
    if (!visited[elem])
    {
      dfs(adj, elem, visited, order);
    }
  }

  order.insert(order.begin(), x);
}

vector<int> toposort(vector<vector<int>> adj)
{
  vector<int> visited(adj.size(), 0);
  vector<int> order;

  for (int i = 0; i < adj.size(); i++)
  {
    if (!visited[i])
    {
      dfs(adj, i, visited, order);
    }
  }
  return order;
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
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++)
  {
    cout << order[i] + 1 << " ";
  }

  return 0;
}
