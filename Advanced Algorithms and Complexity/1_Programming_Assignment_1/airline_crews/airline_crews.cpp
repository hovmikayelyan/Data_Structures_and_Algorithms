/**
 * @file airline_crews.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief 
 * @version 0.1
 * @date 2022-03-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

#define hund 100

int X, Y;
int adj_matrix[hund][hund];
int busy_x[hund], busy_y[hund];

int match_k[hund];

int path(int m, vector<vector<bool>> adj_matrix)
{

  for (int n = 0; n < Y; ++n)
  {
    if (adj_matrix[m][n] && !match_k[n])
    {
      match_k[n] = 1;

      if (busy_y[n] == -1 || path(busy_y[n], adj_matrix))
      {
        busy_x[m] = n;
        busy_y[n] = m;
        return 1;
      }
    }
  }
  return 0;
}

int FindMatching(vector<vector<bool>> adj_matrix)
{
  int res = 0;
  memset(busy_x, -1, sizeof(busy_x));
  memset(busy_y, -1, sizeof(busy_y));
  for (int i = 0; i < X; ++i)
  {
    if (busy_x[i] == -1)
    {
      memset(match_k, 0, sizeof(match_k));
      res += path(i, adj_matrix);
    }
  }
  return res;
}

vector<vector<bool>> ReadData()
{
  int num_left, num_right;
  cin >> num_left >> num_right;
  vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
  for (int i = 0; i < num_left; ++i)
    for (int j = 0; j < num_right; ++j){
      int bit;
      cin >> bit;
      adj_matrix[i][j] = (bit == 1);
    }
  return adj_matrix;
}

int main()
{
  vector<vector<bool>> adj_matrix = ReadData();
  X = adj_matrix.size();
  Y = adj_matrix[0].size();
  int num = FindMatching(adj_matrix);
  for (int num = 0; num < X; ++num)
  {
    if (busy_x[num] + 1)
    {
      cout << busy_x[num] + 1 << ' ';
    }
    else
    {
      cout << -1 << ' ';
    }
  }

  return 0;
}