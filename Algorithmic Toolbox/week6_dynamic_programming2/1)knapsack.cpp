/**
 * @file knapsack.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-11-08
 *
 * @copyright Copyright (c) 2021
 *
 *
 * THE PROBLEM IS
 * You are given a set of bars of gold and your goal is to take as much gold as possible into
 * your bag. There is just one copy of each bar and for each bar you can either take it or not
 * (hence you cannot take a fraction of a bar).
 *
 * 
 * Input Format. The first line of the input contains the capacity 𝑊 of a knapsack and the number 𝑛 of bars
 * of gold. The next line contains 𝑛 integers 𝑤0, 𝑤1, . . . , 𝑤𝑛−1 defining the weights of the bars of gold.
 * 
 * Constraints. 1 ≤ 𝑊 ≤ 104; 1 ≤ 𝑛 ≤ 300; 0 ≤ 𝑤0, . . . , 𝑤𝑛−1 ≤ 105
 * 
 * Output Format. Output the maximum weight of gold that fits into a knapsack of capacity 𝑊.
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

deque<Pair> bestSum(int targetSum, vector<int> &numbers)
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
                    // here we created that element
                    table[i + numbers[num]] = combination;
                }
            }
        }
    }

    // if our target is 10, and numbers are [1,4,8], the biggest target here is 9,
    // so if the program has no way to compute 10, it will return 9 - the biggest lower than 10
    for (size_t i = targetSum; i >= 0; i--)
    {
        if (!table[i].empty())
        {
            return table[i];
        }
    }
}

int main()
{
    // our target number
    int targetSum;
    cin >> targetSum;

    // our count of numbers
    int count;
    cin >> count;

    // creating our numbers container and inserting elements
    vector<int> numbers;
    copy_n(istream_iterator<int>(cin), count, inserter(numbers, numbers.begin()));

    deque<Pair> main = bestSum(targetSum, numbers);

    // counting the sum from solution numbers
    int sum = 0;
    for (auto num : main)
    {
        if (num.val == 0 && num.pos == 0)
        {
            continue;
        }
        sum += num.val;
    }
    cout << sum << endl;
    return 0;
}
