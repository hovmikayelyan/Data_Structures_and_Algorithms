/**
 * @file optimal_kmer_size.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief
 * @version 0.1
 * @date 2022-04-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

#define CUSTOM_MAP map<string, set<string>>

enum struct result
{
  no_cycle,
  one_cycle,
  multiple_cycles
};

result checkEulerCycyle(const CUSTOM_MAP graph)
{
  //check is euler
  for (auto &kv : graph)
  {
    if (kv.second.empty())
      return result::no_cycle;
    if (kv.second.size() > 1)
      return result::multiple_cycles;
  }

  return result::one_cycle;
}

CUSTOM_MAP developDebrujinG(const vector<string> &reads, const int k)
{
  CUSTOM_MAP graph;

  //cycle through our graph
  for (const auto &read : reads)
  {
    for (size_t i = 0; i + k < read.size(); ++i)
    {
      graph[read.substr(i, k - 1)].emplace(read.substr(i + 2, k - 1));
      if (i + k + 1 < read.size())
        graph[read.substr(i + 2, k - 1)];
    }
  }

  return graph;
}

vector<string> inputREAD()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  vector<string> reads;
  string s;

  while (cin >> s)
    reads.emplace_back(move(s));

  return reads;
}

int BinarySearchK(const vector<string> reads, int l, int r)
{
  while (r >= l)
  {
    int mid = l + (r - l) / 2;

    result res = checkEulerCycyle(developDebrujinG(reads, mid));

    //select right result
    switch (res)
    {
    case result::one_cycle:
      return mid;
    case result::no_cycle:
      r = mid - 1;
      continue;
    case result::multiple_cycles:
      l = mid + 1;
      continue;
    }
  }

  throw logic_error{"optimal k not found"};
}

int main()
{
  // mer size
  const int merS = 100;
  //output the result
  cout << BinarySearchK(inputREAD(), 0, merS) << endl;

  return 0;
}