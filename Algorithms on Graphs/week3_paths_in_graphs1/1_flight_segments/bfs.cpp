/**
 * @file bfs.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

int distance(vector<vector<int>> &adj, int s, int t)
{
    if (s == t)
    {
        return 0;
    }

    vector<int> dist(adj.size());
    for (int u = 0; u < dist.size(); u++)
    {
        dist[u] = numeric_limits<int>::max();
    }

    dist[s] = 0;

    queue<int> queue;

    queue.push(s);

    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop();

        for (auto elem : adj[u])
        {
            int v = elem;
            if (dist[v] == numeric_limits<int>::max())
            {
                queue.push(v);
                dist[v] = dist[u] + 1;
            }
        }
    }

    if (dist[t] != numeric_limits<int>::max())
    {
        return dist[t];
    }

    return -1;
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
    int s, t;
    cin >> s >> t;
    s--, t--;
    cout << distance(adj, s, t);
}
