/**
 * @file strongly_connected.cpp
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
 * To track time limit
 */
auto start = chrono::steady_clock::now();
bool returnStatement(bool var)
{
  cout << "\n";
  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << "Used Time - 0," << chrono::duration<double, milli>(diff).count() << " s" << endl;

  return var;
}

/**
 * @brief
 * Main Program
 */

vector<vector<int>> reverseEdges(vector<vector<int>> &adj)
{
  vector<vector<int>> rAdj(adj.size(), vector<int>());
  for (int i = 0; i < adj.size(); i++)
  {
    for (int j = 0; j < adj[i].size(); j++)
    {
      rAdj[adj[i][j]].push_back(i);
    }
  }
  return rAdj;
}

void dfs(vector<vector<int>> &adj, int x, vector<int> &visited, stack<int> &Stack)
{
  visited[x] = 1;

  for (auto elem : adj[x])
  {
    if (!visited[elem])
    {
      visited[elem] = 1;
      dfs(adj, elem, visited, Stack);
    }
  }
  Stack.push(x);
}

int number_of_strongly_connected_components(vector<vector<int>> adj)
{
  int result = 0;
  stack<int> Stack;

  // Mark all the vertices as not visited (For 1st DFS)
  vector<int> visited(adj.size(), 0);

  for (int i = 0; i < adj.size(); i++)
  {
    if (!visited[i])
    {
      dfs(adj, i, visited, Stack);
    }
  }

  //reversed adj list
  vector<vector<int>> rAdj = reverseEdges(adj);

  // Mark all the vertices as not visited (For 2nd DFS)
  for (int i = 0; i < adj.size(); i++)
  {
    visited[i] = 0;
  }

  //process all vertices in order defined by Stack
  while (!Stack.empty())
  {
    int x = Stack.top();
    Stack.pop();

    // get one SCC of the popped vertex
    if (!visited[x])
    {
      stack<int> componentStack;
      dfs(rAdj, x, visited, componentStack);
      result++;
    }
  }
  return result;
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
  cout << number_of_strongly_connected_components(adj);
}