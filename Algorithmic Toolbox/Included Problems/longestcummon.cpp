
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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