#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long fibonacci_fast(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        long previous = 0;
        long current = 1;
        long tmp_previous;

        for (int i = 0; i < n - 1; ++i)
        {
            tmp_previous = previous;
            previous = current;
            current = tmp_previous + current;
        }

        return current;
    }
}

int main()
{
    int n;
    cin >> n;
    long long fib = fibonacci_fast(n);
    cout << fib;
}