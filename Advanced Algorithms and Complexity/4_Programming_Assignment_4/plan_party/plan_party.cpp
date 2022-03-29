/**
 * @file plan_party.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief
 * @version 0.1
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>

using namespace std;

struct vertex
{
    int weight;
    vector<int> children;
};

vector<vertex> TreeReader() noexcept
{
    ios::sync_with_stdio(false);

    int vertices_count;
    cin >> vertices_count;

    vector<vertex> tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
    {
        cin >> tree[i].weight;
    }

    for (int i = 1, from, to; i < vertices_count; ++i)
    {
        cin >> from >> to;
        tree[from - 1].children.emplace_back(to - 1);
        tree[to - 1].children.emplace_back(from - 1);
    }

    return tree;
}

int RecursiveCompute(const vector<vertex> &tree, const int vertex, vector<int> &s, const int parent) noexcept
{
    if (s[vertex] == -1)
    {
        if (tree[vertex].children.empty())
        {
            s[vertex] = tree[vertex].weight;
        }
        else
        {
            auto firstM = tree[vertex].weight;
            for (auto u : tree[vertex].children)
            {
                if (u == parent)
                    continue;
                for (auto w : tree[u].children)
                {
                    if (w != vertex)
                    {
                        firstM += RecursiveCompute(tree, w, s, u);
                    }
                }
            }
            auto secondM = 0;
            for (auto u : tree[vertex].children)
            {
                if (u != parent)
                {
                    secondM += RecursiveCompute(tree, u, s, vertex);
                }
            }

            s[vertex] = max(firstM, secondM);
        }
    }

    return s[vertex];
}

int ComputeMaxIndemendentSet(const vector<vertex> &tree) noexcept
{
    size_t size = tree.size();
    if (size == 0)
        return 0;

    auto s = vector<int>(size, -1);

    return RecursiveCompute(tree, 0, s, -1);
}

int main()
{
    const vector<vertex> tree = TreeReader();
    cout << ComputeMaxIndemendentSet(tree) << endl;
    return 0;
}