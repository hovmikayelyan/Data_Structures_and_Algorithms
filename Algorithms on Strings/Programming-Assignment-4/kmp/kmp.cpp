/**
 * Algorithms on Strings/Week 4/Problem 1
 * @file kmp.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> compute_prefix(const string &p)
{
  vector<int> s(p.size());

  for (int j = 1, brdr = 0, n = p.size(); j < n; ++j)
  {
    while (brdr && p[j] != p[brdr])
    {
      brdr = s[brdr - 1];
    }
    brdr = (p[j] == p[brdr]) ? ++brdr : 0;
    s[j] = brdr;
  }

  return s;
}

vector<int> find_pattern(const string &pattern, const string &text)
{
  string S = pattern + '$' + text;
  vector<int> s = compute_prefix(S);
  vector<int> result;

  for (int i = pattern.size() + 1; i < S.size(); ++i)
  {
    if (s[i] == pattern.size())
    {
      result.push_back(i - 2 * pattern.size());
    }
  }

  return result;
}

int main()
{
  string pattern, text;
  cin >> pattern;
  cin >> text;

  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i)
  {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}