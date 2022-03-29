/**
 * @file 4)lcs2.cpp
 * @author HovMikayelyan
 * @brief 
 * @version 0.1
 * @date 2021-11-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs(vector<int> &arr1, vector<int> &arr2, int m, int n)
{
    int **memo = new int *[m + 1];
    for (size_t i = 0; i < m + 1; i++)
    {
        memo[i] = new int[n + 1];
    }

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                memo[i][j] = 0;
            }
            else if (arr1[i - 1] == arr2[j - 1])
            {
                memo[i][j] = memo[i - 1][j - 1] + 1;
            }
            else
            {
                memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
            }
        }
    }

    return memo[m][n];
}

int main()
{
    int n, m;
    int temp = 0;
    cin >> n;
    vector<int> arr1;
    for (size_t i = 0; i < n; i++)
    {
        cin >> temp;
        arr1.push_back(temp);
    }

    cin >> m;
    vector<int> arr2;
    for (size_t i = 0; i < m; i++)
    {
        cin >> temp;
        arr2.push_back(temp);
    }

    cout << lcs(arr1, arr2, n, m);
    return 0;
}