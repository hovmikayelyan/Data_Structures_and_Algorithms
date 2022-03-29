#include <iostream>
using namespace std;


int EuclidGCD(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	a = a % b;
	return EuclidGCD(b, a);
}

long long LeastCommonMultiple(int a, int b)
{
    long long gcd = EuclidGCD(a, b);
    long long leastCommon = a / gcd * b;
    return leastCommon;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << LeastCommonMultiple(a, b) << std::endl;
  return 0;
}
