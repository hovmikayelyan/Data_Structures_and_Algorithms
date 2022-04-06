/**
 * @file bubble_detection.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>

using namespace std;

#define custom_for(index, k, count) for (int index = k; index < count; index++)
#define GRAPH vector<set<int>>
#define MATRIX vector<vector<int>>
#define PATHS map<int, map<int, vector<set<int>>>>

int KMER = 15;
int T;

// debrujin graph

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
            graph.push_back(set<int>());
            L_label = labels[L_kmer] = vertex++;
        }

        if (labels.find(R_kmer) != labels.end())
            R_label = labels[R_kmer];
        else
        {
            graph.push_back(set<int>());
            R_label = labels[R_kmer] = vertex++;
        }

        graph[L_label].insert(R_label);
    }

    // build deBruijn graph
    GRAPH de_bruijn_graph()
    {
        GRAPH graph;
        string read;
        cin >> KMER >> T;

        while (cin >> read)
            custom_for(i, 0, read.size() - KMER + 1)
                add_edge(graph, read.substr(i, KMER));

        return graph;
    }

public:
    GRAPH create()
    {
        return de_bruijn_graph();
    }
};

// bubble detection

class BubbleDetection
{
    const GRAPH graph;
    MATRIX in_out;
    int nodes;
    set<int> in, out;
    PATHS paths;

    int count_bubbles()
    {
        int bubbles = 0;
        for (const auto &w_pair : paths)
        {
            const map<int, vector<set<int>>> allPATHS = w_pair.second;

            for (const auto &pairPaths : allPATHS)
            {
                const vector<set<int>> wvPATHS = pairPaths.second;

                custom_for(i, 0, wvPATHS.size())
                        custom_for(j, i + 1, wvPATHS.size())
                            disjoint_paths(wvPATHS[i], wvPATHS[j])
                    ? bubbles++
                    : false;
            }
        }
        return bubbles;
    }

    bool disjoint_paths(const set<int> &path1, const set<int> &path2)
    {
        for (const auto &v : path1)
            if (path2.find(v) != path2.end())
                return false;
        return true;
    }

    void find_candidates()
    {
        custom_for(i, 0, nodes)
        {
            in_out[i][1] = graph[i].size(); // out degree
            for (const auto &v : graph[i])  // in degree of children nodes
                in_out[v][0]++;
        }

        custom_for(i, 0, nodes)
        {
            if (in_out[i][0] > 1)
                in.insert(i);
            if (in_out[i][1] > 1)
                out.insert(i);
        }
    }

    void dfs(int root, int curnode, set<int> &visited)
    {
        if (curnode != root && in.find(curnode) != in.end())
        {
            set<int> npath = visited;
            npath.erase(curnode);
            npath.erase(root);
            paths[root][curnode].push_back(npath);
        }

        if (visited.size() > T)
            return;

        // new path to children
        for (const auto &v : graph[curnode])
            if (visited.find(v) == visited.end())
            {
                set<int> nvisited = visited;
                nvisited.insert(v);
                dfs(root, v, nvisited);
            }
    }

public:
    BubbleDetection(const GRAPH g) : graph(g)
    {
        nodes = graph.size();
        in_out = MATRIX(nodes, vector<int>(2, 0));
    }

    int bubbles()
    {
        find_candidates();

        for (const auto &root : out)
        {
            set<int> visited = {root};
            dfs(root, root, visited);
        }

        return count_bubbles();
    }
};

int main(int argc, char **argv)
{
    // make de_bruijn graph
    DebruijnGraph dbGraph;
    GRAPH graph = dbGraph.create();

    // bubble detection
    BubbleDetection bd(graph);
    cout << bd.bubbles() << endl;

    return 0;
}