#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

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

int main()
{
    string str1;
    string str2;
    cin >> str1 >> str2;

    int n = str1.length(), m = str2.length();
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));

    cout << minDis(str1, str2, n, m, memo);
    return 0;
}