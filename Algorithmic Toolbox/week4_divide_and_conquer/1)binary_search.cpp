/**
 * @file 1)binary_search.cpp
 * @author Hovhannes Mikayelyan
 * @brief 
 * @version 0.1
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;


long find_binary(vector<long> &a, long x, long left, long right)
{
    if (right >= left)
    {
        long half = left + (right - left) / 2;

        if (x == a[half])
        {
            return half;
        }
        if (x > a[half])
        {
            return find_binary(a, x, half + 1, right);
        }
        return find_binary(a, x, left, half - 1);
    }

    return -1;
}

int main()
{
    int n;
    cin >> n;
    vector<long> a(n);
    for (size_t i = 0; i < a.size(); i++)
    {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int m;
    cin >> m;
    vector<long> b(m);
    for (int i = 0; i < m; ++i)
    {
        cin >> b[i];
    }
    for (int i = 0; i < m; ++i)
    {
        cout << find_binary(a, b[i], 0, (long)a.size()) << " ";
    }
    return 0;
}
