/**
 * @file tip.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * Grading: 'Good job! (Max time used: 0.15/20.00, max memory used: 23339008/2147483648.)'
 * Respect Coursera Honor Code
 * @brief
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

#define custom_for(index, k, count) for (int index = k; index < count; index++)
#define GRAPH vector<vector<set<int>>>
#define MATRIX vector<vector<int>>

int KMER = 15;
int READSIZE = 100;
int DATASET = 1618;

class DebruijnGraph
{
    void add_edge(GRAPH &graph, const string &kmer)
    {
        static int k_1 = KMER - 1;
        static int vertex = 0;
        static map<string, int> labels;

        string L_kmer = kmer.substr(0, k_1);
        string R_kmer = kmer.substr(1, k_1);
        int L_label, R_label;

        if (labels.find(L_kmer) != labels.end())
            L_label = labels[L_kmer];
        else
        {
            graph.push_back(vector<set<int>>(2, set<int>()));
            L_label = labels[L_kmer] = vertex++;
        }

        if (labels.find(R_kmer) != labels.end())
            R_label = labels[R_kmer];
        else
        {
            graph.push_back(vector<set<int>>(2, set<int>()));
            R_label = labels[R_kmer] = vertex++;
        }

        // add child labels
        graph[L_label][0].insert(R_label);
        graph[R_label][1].insert(L_label);
    }

    GRAPH de_bruijn_graph()
    {
        GRAPH graph;
        string read;

        while (cin >> read)
            custom_for(j, 0, READSIZE - KMER + 1)
                add_edge(graph, read.substr(j, KMER));

        return graph;
    }

public:
    GRAPH create()
    {
        return de_bruijn_graph();
    }
};

class TipsRemoval
{
    GRAPH graph;
    MATRIX in_out;
    set<int> out_tips;
    set<int> in_tips;
    int nodes;
    int tips;

public:
    TipsRemoval(GRAPH g) : graph(g)
    {
        nodes = graph.size();
        tips = 0;
        in_out = MATRIX(nodes, vector<int>(2, 0));
    }

    int tips_number()
    {
        find_candidates();
        bfs_in_tips();
        bfs_out_tips();

        return tips;
    }

    /// vertexes that may have bubbles
    void find_candidates()
    {
        custom_for(i, 0, nodes)
        {
            in_out[i][0] = graph[i][0].size();
            in_out[i][1] = graph[i][1].size();
        }

        custom_for(i, 0, nodes)
        {
            if (in_out[i][0] == 0)
                out_tips.insert(i);
            if (in_out[i][1] == 0)
                in_tips.insert(i);
        }
    }

    void bfs_in_tips()
    {
        while (!in_tips.empty())
        {
            int curtip = *(in_tips.begin());
            in_tips.erase(curtip);

            // decrement in_degree of all children of current in_tip vertex
            for (const auto &child : graph[curtip][0])
            {
                graph[curtip][0].erase(child);
                graph[child][1].erase(curtip);
                tips++;

                if (graph[child][1].size() == 0 && out_tips.find(child) == out_tips.end())
                    in_tips.insert(child);
            }
        }
    }

    void bfs_out_tips()
    {
        while (!out_tips.empty())
        {
            int curtip = *(out_tips.begin());
            out_tips.erase(curtip);

            // decrement in_degree of all children of current in_tip vertex
            for (const auto &parent : graph[curtip][1])
            {
                graph[curtip][1].erase(parent);
                graph[parent][0].erase(curtip);
                tips++;

                if (graph[parent][0].size() == 0)
                    out_tips.insert(parent);
            }
        }
    }
};

int main(int argc, char **argv)
{
    // debrujin
    DebruijnGraph debrujinGRAPH;
    GRAPH graph = debrujinGRAPH.create();

    // remove tips
    TipsRemoval tipREMOVE(graph);
    cout << tipREMOVE.tips_number() << endl;

    return 0;
}