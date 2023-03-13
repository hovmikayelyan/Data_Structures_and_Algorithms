#include <iostream>
using namespace std;

long long fib(long n)
{
    if (n == -1)
    {
        return 0;
    }
    else if (n <= 1)
    {
        return n;
    }

    n %= 60;

    if (n == 0)
        return 0;

    long current = 0;
    long first = 0;
    long second = 1;
    long sum = 0;

    for (int i = 0; i <= n; i++)
    {
        current = (first + second) % 60;
        first = second;
        second = current;
    }

    return (current - 1) % 10;
}

long long LastDigit(long m, long n)
{
    long long result = 10 + fib(n) - fib(m - 1);
    return result % 10;
}

int main()
{
    long m;
    long n;
    cin >> m;
    cin >> n;
    long long fib = LastDigit(m, n);
    cout << fib;
}