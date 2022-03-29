/**
 * @file bipartite.cpp
 * @author  Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief
 * Main Program
 *
 * A graph is bipartite  = it has no odd cycle.
 *
 * Algorithm:
 * 1. Using BFS to color each node using alternate colors (1 and -1 for two colors)
 * 2. When it finds two connected nodes are going to be colored in the same color, return 0.
 */

bool isBipartite(vector<vector<int>> &adj)
{
    vector<int> col(adj.size(), -1);
    
    queue<pair<int, int>> queue;

    for (int i = 0; i < adj.size(); i++)
    {
        if (col[i] == -1)
        {
            queue.push({i, 0});
            col[i] = 0;

            while (!queue.empty())
            {
                pair<int, int> p = queue.front();
                queue.pop();

                int v = p.first;
                int c = p.second;

                for (auto elem : adj[v])
                {
                    if (col[elem] == c)
                        return 0;

                    if (col[elem] == -1)
                    {

                        col[elem] = (c) ? 0 : 1;
                        queue.push({elem, col[elem]});
                    }
                }
            }
        }
    }

    return 1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    cout << isBipartite(adj);

    return 0;
}