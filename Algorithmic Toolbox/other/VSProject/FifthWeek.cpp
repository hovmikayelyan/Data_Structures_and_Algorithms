#include "FifthWeek.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <climits>
#include <bits/stdc++.h>

using namespace std;

/*******************************
/**
 * @brief
 * Money Change Again
 */
void FifthWeek::solveMoneyChangeDynamic()
{
    set<int> Coins;

    map<int, int> MinNumCoins;
    MinNumCoins.insert({0, 0});

    // int n;
    // cin >> n;
    // //cin coins
    // copy_n(istream_iterator<int>(cin), n, inserter(Coins, Coins.begin()));

    Coins.insert(1);
    Coins.insert(3);
    Coins.insert(4);

    int cash;
    cin >> cash;

    int NumCoins = 0;

    for (size_t m = 1; m <= cash; m++)
    {
        MinNumCoins[m] = 1000000;
        for (int coin : Coins)
        {
            if (m >= coin)
            {
                NumCoins = MinNumCoins[m - coin] + 1;
                if (NumCoins < MinNumCoins[m])
                {
                    MinNumCoins[m] = NumCoins;
                }
            }
        }
    }

    cout << MinNumCoins[cash] << endl;
}

/*************************

/**
 * @brief
 *
 * @param n
 * @param sequence
 * 
 * primitve Calculator
 */
void FifthWeek::primitveCalculator()
{
    int n;
    cin >> n;
    vector<int> sequence;

    vector<int> a(n + 1);
    vector<int> predecessor(n + 1);

    for (int i = 2; i <= n; i++)
    {
        a[i] = a[i - 1] + 1;
        predecessor[i] = i - 1;
        if (i % 3 == 0)
        {
            if (a[i / 3] < a[i])
            {
                a[i] = a[i / 3] + 1;
                predecessor[i] = i / 3;
            }
        }
        if (i % 2 == 0)
        {
            if (a[i / 2] < a[i])
            {
                a[i] = a[i / 2] + 1;
                predecessor[i] = i / 2;
            }
        }
    }

    for (int i = n; i != 0; i = predecessor[i])
    {
        sequence.push_back(i);
    }
    reverse(sequence.begin(), sequence.end());

    cout << sequence.size() - 1 << endl;
    for (size_t i = 0; i < sequence.size(); ++i)
    {
        cout << sequence[i] << " ";
    }
}

//*********************************
/**
 * @brief
 * edit Distance Problem
 */

int minDis(string str1, string str2, int n, int m, vector<vector<int>> &memo)
{

    if (n == 0)
        return m;

    if (m == 0)
        return n;

    if (memo[n][m] != -1)
        return memo[n][m];

    if (str1[n - 1] == str2[m - 1])
    {
        if (memo[n - 1][m - 1] == -1)
        {
            return memo[n][m] = minDis(str1, str2, n - 1, m - 1, memo);
        }
        else
            return memo[n][m] = memo[n - 1][m - 1];
    }

    else
    {
        int temp1, temp2, temp3;

        if (memo[n - 1][m] != -1)
        {
            temp1 = memo[n - 1][m];
        }
        else
        {
            temp1 = minDis(str1, str2, n - 1, m, memo);
        }

        if (memo[n][m - 1] != -1)
        {
            temp2 = memo[n][m - 1];
        }
        else
        {
            temp2 = minDis(str1, str2, n, m - 1, memo);
        }

        if (memo[n - 1][m - 1] != -1)
        {
            temp3 = memo[n - 1][m - 1];
        }
        else
        {
            temp3 = minDis(str1, str2, n - 1, m - 1, memo);
        }
        return memo[n][m] = 1 + min(temp1, min(temp2, temp3));
    }
}

void FifthWeek::editDistanceProblem()
{
    string str1;
    string str2;
    cin >> str1 >> str2;

    int n = str1.length(), m = str2.length();
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));

    cout << minDis(str1, str2, n, m, memo);
}

//**************
/**
 * @brief
 * Longest Common Subsequence Of Two Sequences
 */

int lcs(vector<int> &X, vector<int> &Y, int m, int n)
{
    int **L = new int *[m + 1];
    for (size_t i = 0; i < m + 1; i++)
    {
        L[i] = new int[n + 1];
    }

    int i, j;

    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;

            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    return L[m][n];
}

void FifthWeek::LongestCommonSubsequenceOfTwoSequences()
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
}

//********************