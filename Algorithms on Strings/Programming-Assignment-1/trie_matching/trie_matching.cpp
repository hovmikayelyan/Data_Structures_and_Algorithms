/**
 * @file trie_matching.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

typedef map<char, int> Edges;
typedef vector<Edges> Trie;

Trie TrieConstruction(vector<string> &patterns)
{
    if (patterns.empty())
    {
        return Trie{};
    }

    Trie trie{Edges{}};

    int root = 0, cnt = 0;

    for (auto &pattern : patterns)
    {
        int currentNode = root;

        for (auto ch : pattern)
        {
            if (trie[currentNode].find(ch) != trie[currentNode].end())
            {
                currentNode = trie[currentNode][ch];
            }
            else
            {
                trie.push_back(Edges{});
                trie[currentNode][ch] = ++cnt;
                currentNode = cnt;
            }
        }
    }

    return trie;
}

void PrefixTrieMatching(string text, Trie &patterns_trie, vector<int> &positions, int index)
{
    int current_vertex = 0;
    int current_symbol_index = index;
    char symbol = text[current_symbol_index];
    while (true)
    {
        if (patterns_trie[current_vertex].empty())
        {
            positions.push_back(index);
            break;
        }
        else if (patterns_trie[current_vertex].find(symbol) != patterns_trie[current_vertex].end())
        {
            current_vertex = patterns_trie[current_vertex][symbol];
            symbol = text[++current_symbol_index];
        }
        else
        {
            break;
        }
    }
}

vector<int> TrieMatching(string text, Trie theTrie)
{
    vector<int> positions;

    for (int i = 0; i < text.size(); ++i)
    {
        PrefixTrieMatching(text, theTrie, positions, i);
    }

    return positions;
}

int main()
{
    string text;
    cin >> text;

    size_t n;
    cin >> n;

    vector<string> patterns;

    for (size_t i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        patterns.push_back(s);
    }

    Trie theTrie = TrieConstruction(patterns);
    auto ans = TrieMatching(text, theTrie);

    for (int i = 0; i < (int)ans.size(); i++)
    {
        cout << ans[i];
        if (i + 1 < (int)ans.size())
        {
            cout << " ";
        }
        else
        {
            cout << endl;
        }
    }

    return 0;
}