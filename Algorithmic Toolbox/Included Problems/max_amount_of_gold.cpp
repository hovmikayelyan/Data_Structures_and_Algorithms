#include <iostream>
#include <map>
#include <deque>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <iterator>

using namespace std;

struct Pair
{
    int val;
    int pos;
};

deque<Pair> bestSum(int targetSum, vector<int> &numbers)
{
    map<int, deque<Pair>> table;
    table[0].push_back({0, 0});

    for (size_t i = 0; i <= targetSum; i++)
    {
        if (!table[i].empty())
        {
            for (int num = 0; num < numbers.size(); num++)
            {
                bool repeated = 0;

                deque<Pair> combination = table[i];

                Pair temp;
                temp.val = numbers[num];
                temp.pos = num;

                for (auto item : combination)
                {
                    if (item.pos == num && item.val == numbers[num])
                    {
                        repeated = 1;
                    }
                }

                if (repeated)
                    continue;

                combination.push_back(temp);

                auto it = table.find(i + numbers[num]);

                if (it == table.end() || table[i + numbers[num]].size() > combination.size())
                {
                    table[i + numbers[num]] = combination;
                }
            }
        }
    }

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
    int targetSum;
    cin >> targetSum;
    int count;
    cin >> count;
    vector<int> numbers;
    copy_n(istream_iterator<int>(cin), count, inserter(numbers, numbers.begin()));

    deque<Pair> main = bestSum(targetSum, numbers);

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