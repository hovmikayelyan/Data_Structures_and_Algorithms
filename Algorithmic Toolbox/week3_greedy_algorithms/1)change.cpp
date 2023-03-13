#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int solveMoneyChange(int m, int coins[])
{

  int count = 0;
  for (int i = 2; i >= 0; i--)
  {
    count += m / coins[i];
    m -= (m / coins[i]) * coins[i];
  }

  return count;
}

int main()
{
  int m;
  cin >> m;

  int coins[3] = {1, 5, 10};

  int change = solveMoneyChange(m, coins);
  cout << change;
}
