/**
 * @file 2)partition_to3(souvenirs).cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-11-08
 *
 * @copyright Copyright (c) 2021
 *
 *
 * PROBLEM DESCRIPTION
 * You and two of your friends have just returned back home after visiting various countries. Now you would
 * like to evenly split all the souvenirs that all three of you bought
 *
 * Input Format. The first line contains an integer 𝑛. The second line contains integers 𝑣1, 𝑣2, . . . , 𝑣𝑛 separated
 * by spaces.
 *
 * Constraints. 1 ≤ 𝑛 ≤ 20, 1 ≤ 𝑣𝑖 ≤ 30 for all 𝑖.
 *
 * Output Format. Output 1, if it possible to partition 𝑣1, 𝑣2, . . . , 𝑣𝑛 into three subsets with equal sums, and
 * 0 otherwise.
 *
 */

#include <iostream>
#include <map>
#include <deque>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <iterator>

using namespace std;

// a struct for combinations, numbers with their indexes
struct Pair
{
  int val;
  int pos;
};

deque<Pair> howSum(int targetSum, vector<int> &numbers)
{
  // each element is Nx2 matrix,
  // which contains all included numbers for that num, with indexes from @numbers variable
  map<int, deque<Pair>> table;
  // first item - 0, to get the number 0, we need just 0
  table[0].push_back({0, 0});

  // loop until our target number, which we need to compute
  for (size_t i = 0; i <= targetSum; i++)
  {
    // like, our first element is not empty, cuz 0 has only 1 elem - 0
    if (!table[i].empty())
    {

      // loop, going through all our @numbers
      for (int num = 0; num < numbers.size(); num++)
      {
        // to check if selected number is already used or not
        bool repeated = 0;
        // a container, which copying all elements from table
        deque<Pair> combination = table[i];

        // temporary Pair vairable, with number and its index
        Pair temp;
        temp.val = numbers[num];
        temp.pos = num;

        // check if element is already in our table[i] or not, if yes, then marking that
        for (auto item : combination)
        {
          if (item.pos == num && item.val == numbers[num])
          {
            repeated = 1;
          }
        }

        // if @number was repeated, we skip that number, cuz itts already in table[i]
        if (repeated)
          continue;

        // the number didnt found in table[i], so we push that number in temporary container
        combination.push_back(temp);

        // is there any container, like, if our index is 0, and our num = 4,
        // we creating below a container with index 4, and adding to it our number,
        // cuz the easiest way to compute 4
        // is just adding 4
        auto it = table.find(i + numbers[num]);

        // the second condition checks if our solution is smaller than already existing one, than >
        // we choose the easiest way
        if (it == table.end() || table[i + numbers[num]].size() > combination.size())
        {
          table[i + numbers[num]] = combination;
        }
      }
    }
  }

  // is the target reachable
  if (!table[targetSum].empty())
  {
    return table[targetSum];
  }
  else
  {
    deque<Pair> failed;
    table[targetSum] = failed;
    return failed;
  }
}

bool check()
{
  int n;
  cin >> n;

  vector<int> Elems;
  copy_n(istream_iterator<int>(cin), n, inserter(Elems, Elems.begin()));

  int sum = 0;
  for (int num : Elems)
  {
    sum += num;
  }
  if (sum % 3 != 0)
  {
    return false;
  }

  int targetPoint = sum / 3;
  vector<int> tempNumbers = Elems;

  for (size_t session = 0; session < 3; session++)
  {
    vector<int> tempNumbers = Elems;
    deque<Pair> main = howSum(targetPoint, tempNumbers);

    if (main.empty())
    {
      return false;
    }

    // remove 0 from container
    for (int index = 0; index < main.size(); index++)
    {
      if (main[index].val == 0 && main[index].pos == 0)
      {
        main.erase(main.begin() + index);
        break;
      }
    }

    // remove used numbers
    for (int num : tempNumbers)
    {
      tempNumbers.erase(remove(tempNumbers.begin(), tempNumbers.end(), num), tempNumbers.end());
    }
  }

  return true;
}

int main()
{
  cout << check() << endl;
  return 0;
}