#include <iostream>
#include <math.h>
#include <vector>
#include <climits>
#include <map>
#include <deque>
#include <set>

using namespace std;

/*******************************
/**
 * @brief
 * Money Change Again
 */
void solveMoneyChangeDynamic()
{
  set<int> Coins;

  map<int, int> MinNumCoins;
  MinNumCoins.insert({0, 0});

  // int n;
  // cin >> n;
  // //cin coins
  // copy_n(istream_iterator<int>(cin), n, inserter(Coins, Coins.begin()));

  Coins.insert(1);
  Coins.insert(3);
  Coins.insert(4);

  int cash;
  cin >> cash;

  int NumCoins = 0;

  for (size_t m = 1; m <= cash; m++)
  {
    MinNumCoins[m] = 1000000;
    for (int coin : Coins)
    {
      if (m >= coin)
      {
        NumCoins = MinNumCoins[m - coin] + 1;
        if (NumCoins < MinNumCoins[m])
        {
          MinNumCoins[m] = NumCoins;
        }
      }
    }
  }

  cout << MinNumCoins[cash] << endl;
}

/****************************
 * @brief
 *
 * @return int
 */

deque<int> bestSum(int targetSum, vector<int> &numbers)
{
  map<int, deque<int>> table;
  table[0].push_back(0);

  for (size_t i = 0; i <= targetSum; i++)
  {
    if (!table[i].empty())
    {
      for (auto num : numbers)
      {
        deque<int> combo = table[i];
        combo.push_back(num);
        auto it = table.find(i + num);

        if (it == table.end() || table[i + num].size() > combo.size())
        {
          table[i + num] = combo;
        }
      }
    }
  }

  return table[targetSum];
}

void solveFunc()
{
  int targetSum = 7;
  vector<int> numbers = {5, 3, 4, 7};
  deque<int> main = bestSum(targetSum, numbers);
  main.erase(std::remove(main.begin(), main.end(), 0), main.end());
  for (auto num : main)
  {
    cout << num << "\t";
  }
  cout << endl;
}

/*****************************
/**
 * @brief
 *
 * @return int
 */

int main()
{
  solveMoneyChangeDynamic();
  // kaaaaam esi
  //  solveFunc();
  return 0;
}
