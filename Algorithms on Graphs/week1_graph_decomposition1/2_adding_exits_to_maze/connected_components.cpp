/**
 * @file connected_components.cpp
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

void explore(vector<vector<int>> &adj, int x, vector<int> &visited)
{
    visited[x] = 1;
    for (auto elem : adj[x])
    {
        if (!visited[elem])
            explore(adj, elem, visited);
    }
}

int number_of_components(vector<vector<int>> &adj)
{
    int res = 0;

    vector<int> visited(adj.size());
    for (int i = 0; i < adj.size(); i++)
    {
        if (!visited[i])
        {
            explore(adj, i, visited);
            res++;
        }
    }
    return res;
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
    cout << number_of_components(adj);
}
