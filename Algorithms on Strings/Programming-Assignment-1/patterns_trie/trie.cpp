/**
 * @file trie.cpp
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

Trie build_trie(vector<string> &patterns)
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

int main()
{
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++)
  {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  Trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i)
  {
    for (const auto &j : t[i])
    {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}