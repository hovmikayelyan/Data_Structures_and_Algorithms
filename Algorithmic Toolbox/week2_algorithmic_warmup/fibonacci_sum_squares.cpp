#include <iostream>
#include <cmath>
using namespace std;

long long fib(long long n)
{
    long get_last_dig = n;
    long first = 0;
    long second = 1;

    for (int i = 0; i < n - 1; i++)
    {
        get_last_dig = (first + second) % 10;
        first = second;
        second = get_last_dig;
    }

    return get_last_dig;
}

long long get_last_dig(long long n)
{
    long smaller = n % 60;
    long larger = (n + 1) % 60;
    return (fib(smaller) * fib(larger)) % 10;
}

int main()
{
    long long n;
    cin >> n;
    cout << get_last_dig(n) << endl;
}