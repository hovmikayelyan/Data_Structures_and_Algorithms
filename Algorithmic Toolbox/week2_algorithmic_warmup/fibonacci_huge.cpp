#include <iostream>
using namespace std;

long long pisano(long long m)
{
    long prev = 0;
    long curr = 1;
    long res = 0;

    for (int i = 0; i < m * m; i++)
    {
        long temp = 0;
        temp = curr;
        curr = (prev + curr) % m;
        prev = temp;

        if (prev == 0 && curr == 1)
            res = i + 1;
    }
    return res;
}

int main()
{
    long long m, n;
    cin >> n >> m;
    n %= pisano(m);
    long prev = 0;
    long curr = 1;
    long temp;

    if (n == 0)
        curr = 0;

    for (int i = 0; i < n - 1; i++)
    {
        temp = curr;
        curr = (prev + curr) % m;
        prev = temp;
    }

    cout << curr % m;
}
