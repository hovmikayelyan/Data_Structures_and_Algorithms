#include <iostream>
using namespace std;

int EuclidGCD(int &a, int &b)
{
	if (b == 0)
	{
		return a;
	}
	a = a % b;
	return EuclidGCD(b, a);
}

int main(int argc, char *argv[])
{
	int x, y;
	cin >> x >> y;
	;
	int gcd = EuclidGCD(x, y);
	cout << gcd;
}