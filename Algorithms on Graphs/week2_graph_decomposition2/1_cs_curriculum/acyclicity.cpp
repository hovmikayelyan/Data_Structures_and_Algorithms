/**
 * @file acyclicity.cpp
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

int dfs(vector<vector<int>> &adj, int x, vector<int> &visited, vector<int> &recursionStack)
{

    visited[x] = 1;
    recursionStack[x] = 1;

    for (auto elem : adj[x])
    {
        if (!visited[elem] && dfs(adj, elem, visited, recursionStack))
            return 1;
        else if (recursionStack[elem])
            return 1;
    }

    recursionStack[x] = 0;
    return 0;
}

int acyclic(vector<vector<int>> &adj)
{
    vector<int> visited(adj.size());
    vector<int> recursionStack(adj.size());

    for (int i = 0; i < adj.size(); i++)
    {
        if (!visited[i])
        {
            if (dfs(adj, i, visited, recursionStack))
                return 1;
        }
    }
    return 0;
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
    cout << acyclic(adj);
}
