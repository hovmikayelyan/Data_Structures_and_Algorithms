#include <iostream>
#include <cmath>
using namespace std;

long long last_digit_of_fib(long long n)
{
    if (n <= 1)
        return n;

    n %= 60;

    if (n == 0)
        return 0;

    long current = 0;
    long first = 0;
    long second = 1;

    for (int i = 0; i <= n; i++)
    {
        current = (first + second) % 60;
        first = second;
        second = current;
    }

    return (current - 1) % 10;
}

int main()
{
    long long n;
    cin >> n;
    long long fib = last_digit_of_fib(n);
    cout << fib;
}