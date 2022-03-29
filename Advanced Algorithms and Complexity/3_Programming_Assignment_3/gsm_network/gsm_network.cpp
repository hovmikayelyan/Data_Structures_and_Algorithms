/**
 * @file gsm_network.cpp
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
#include <cstdio>

using std::cin;
using std::ios;
using std::vector;

struct ConvertGSMNetworkProblemToSat
{
    static constexpr auto K = 3;

    struct edge
    {
        int from;
        int to;
    };

    ConvertGSMNetworkProblemToSat(int n, int m)
        : edges(m)
    {
        this->numVertices = n;
    }

    void printEquisatisfiableSatFormula() const noexcept
    {
        const int C = K * edges.size() + numVertices;
        const int V = numVertices * K;

        printf("%d %d\n", C, V);

        for (int j = 0, cnt = 1; j < numVertices; ++j, cnt += K)
        {
            printf("%d %d %d 0\n", cnt, cnt + 1, cnt + 2);
        }

        for (const edge &e : edges)
        {
            printf("%d %d 0\n", -((e.from - 1) * K + 1), -((e.to - 1) * K + 1));
            printf("%d %d 0\n", -((e.from - 1) * K + 2), -((e.to - 1) * K + 2));
            printf("%d %d 0\n", -((e.from - 1) * K + 3), -((e.to - 1) * K + 3));
        }
    }

    int numVertices;
    vector<edge> edges;
};

int main()
{
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    ConvertGSMNetworkProblemToSat converter(n, m);

    for (int i = 0; i < m; ++i)
    {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}