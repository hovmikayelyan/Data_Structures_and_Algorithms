#include <iostream>
using namespace std;

long long get_fibonacci_last_digit(int n)
{
    if (n <= 1)
    {
        return n % 10;
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
            current = (tmp_previous + current) % 10;
        }

        return current;
        
    }
}

int main()
{
	int n;
	cin >> n;
	long long fib = get_fibonacci_last_digit(n);
	cout << fib;
}