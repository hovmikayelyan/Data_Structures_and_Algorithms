/**
 * Algorithms on Strings/Week 4/Problem 2
 * @file suffix_array_long.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

const int SIZE_OF_ALPHABET = 5;

int getIndex(char c)
{
  switch (c)
  {
  case 'A':
    return 1;
  case 'C':
    return 2;
  case 'G':
    return 3;
  case 'T':
    return 4;
  default:
    return 0;
  }
}

vector<int> sortDoubled(const string &s, int L, const vector<int> &order, const vector<int> &_class)
{
  vector<int> count(s.size());
  vector<int> new_order(s.size());

  for (int i = 0; i < s.size(); ++i)
  {
    ++count[_class[i]];
  }

  for (int j = 1; j < s.size(); ++j)
  {
    count[j] += count[j - 1];
  }

  for (int i = s.size() - 1; i >= 0; --i)
  {
    int start = (order[i] - L + s.size()) % s.size();
    int cl = _class[start];
    new_order[--count[cl]] = start;
  }

  return new_order;
}

vector<int> ComputeCharClasses(const string &s, const vector<int> &order)
{
  vector<int> _class(s.size());

  for (int i = 1; i < s.size(); ++i)
  {
    if (s[order[i]] != s[order[i - 1]])
    {
      _class[order[i]] = _class[order[i - 1]] + 1;
    }
    else
    {
      _class[order[i]] = _class[order[i - 1]];
    }
  }

  return _class;
}

vector<int> SortCharacters(const string &s)
{
  vector<int> order(s.size());
  vector<int> count(SIZE_OF_ALPHABET);

  for (auto &ch : s)
  {
    ++count[getIndex(ch)];
  }

  for (int j = 1; j < SIZE_OF_ALPHABET; ++j)
  {
    count[j] += count[j - 1];
  }

  for (int i = s.size() - 1; i >= 0; --i)
  {
    char c = s[i];
    count[getIndex(c)] -= 1;
    order[count[getIndex(c)]] = i;
  }
  return order;
}

vector<int> updateClasses(const vector<int> &new_order, const vector<int> &_class, int L)
{
  const int n = new_order.size();
  vector<int> new_class(n);

  for (int i = 1; i < n; ++i)
  {
    int cur = new_order[i], prev = new_order[i - 1];
    int mid = cur + L, mid_prev = (prev + L) % n;

    if (_class[cur] != _class[prev] || _class[mid] != _class[mid_prev])
    {
      new_class[cur] = new_class[prev] + 1;
    }
    else
    {
      new_class[cur] = new_class[prev];
    }
  }

  return move(new_class);
}

vector<int> buildSuffixArray(const string &S)
{
  vector<int> _order = SortCharacters(S);
  vector<int> _class = ComputeCharClasses(S, _order);
  int L = 1;

  while (L < S.size())
  {
    _order = sortDoubled(S, L, _order, _class);
    _class = updateClasses(_order, _class, L);
    L *= 2;
  }

  return move(_order);
}

int main()
{
  string s;
  cin >> s;
  vector<int> order = buildSuffixArray(s);

  for (auto elem : order)
  {
    cout << elem << ' ';
  }

  return 0;
}