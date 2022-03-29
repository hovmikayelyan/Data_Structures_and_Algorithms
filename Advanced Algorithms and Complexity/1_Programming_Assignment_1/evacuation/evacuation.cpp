/**
 * Coursera/Advanced Algorithms and Complexity/Week 1/Problem 1:
 * @file evacuation.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief
 * @version 0.1
 * @date 2022-03-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class FlowGraph
{
public:
    struct Edge
    {
        int from, to, capacity, flow;
    };

private:
    vector<Edge> edges;
    vector<vector<int>> graph;

public:
    explicit FlowGraph(int n, int m)
        : graph(n)
    {
        edges.reserve(m * 2);
    }

    void add_edge(int from, int to, int capacity)
    {

        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    int size() const
    {
        return graph.size();
    }

    const vector<int> &get_ids(int from) const
    {
        return graph[from];
    }

    const Edge &get_edge(int id) const
    {
        return edges[id];
    }

    void add_flow(int id, int flow)
    {

        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data()
{
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;

    FlowGraph graph(vertex_count, edge_count);

    for (int i = 0; i < edge_count; ++i)
    {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }

    return graph;
}

void BFS(const FlowGraph &graph, int s, int t, vector<int> &pred)
{
    queue<int> q;
    q.push(s);

    fill(pred.begin(), pred.end(), -1);

    while (!q.empty())
    {

        int cur = q.front();
        q.pop();

        for (auto id : graph.get_ids(cur))
        {

            const FlowGraph::Edge &e = graph.get_edge(id);

            if (pred[e.to] == -1 && e.capacity > e.flow && e.to != s)
            {
                pred[e.to] = id;
                q.push(e.to);
            }
        }
    }
}

int max_flow(FlowGraph &graph, int s, int t)
{
    int flow = 0;

    vector<int> pred(graph.size());

    do
    {

        BFS(graph, s, t, pred);

        if (pred[t] != -1)
        {
            int min_flow = numeric_limits<int>::max();

            for (int u = pred[t]; u != -1; u = pred[graph.get_edge(u).from])
            {
                min_flow = min(min_flow, graph.get_edge(u).capacity - graph.get_edge(u).flow);
            }

            for (int u = pred[t]; u != -1; u = pred[graph.get_edge(u).from])
            {
                graph.add_flow(u, min_flow);
            }

            flow += min_flow;
        }

    } while (pred[t] != -1);

    return flow;
}

int main()
{
    ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}