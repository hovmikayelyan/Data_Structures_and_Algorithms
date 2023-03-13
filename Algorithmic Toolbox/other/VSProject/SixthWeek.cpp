#include "SixthWeek.h"
#include <iostream>
#include <math.h>
#include <climits>
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief
 *
 * @return int
 */
int SixthWeek::KnapsackWithRepetitions()
{
    int count;
    int capacity;

    cin >> count >> capacity;
    cout << "kg\t$\n";

    vector<Pair> items(count);

    for (int i = 0; i < count; i++)
    {
        cin >> items[i].weight >> items[i].value;
    }

    sort(items.begin(), items.end(), [](const Pair &a, const Pair &b) -> bool
         { return a.weight < b.weight; });

    cout << endl
         << "printing" << endl;
    for (int i = 0; i < count; i++)
    {

        cout << items[i].weight << "\t" << items[i].value << endl;
    }

    int temp;
    vector<int> Weights(capacity + 1);
    Weights[0] = 0;
    for (size_t w = 1; w <= capacity; w++)
    {
        Weights[w] = 0;
        for (size_t i = 0; i < count; i++)
        {
            if (items[i].weight <= w)
            {
                temp = Weights[w - items[i].weight] + items[i].value;
                Weights[w] = max(Weights[w], temp);
            }
        }
    }

    for (int i = 0; i <= capacity; i++)
    {

        cout << Weights[i] << "\t";
    }
    cout << endl;
    return Weights[capacity];
}

//***************************
/**
 * @brief
 *
 * Maximum Amount of Gold
 *
 * @return int
 */

struct numPair
{
    int val;
    int pos;
};

deque<numPair> bestSum(int targetSum, vector<int> &numbers)
{
    map<int, deque<numPair>> table;
    table[0].push_back({0, 0});

    for (size_t i = 0; i <= targetSum; i++)
    {
        if (!table[i].empty())
        {
            for (int num = 0; num < numbers.size(); num++)
            {
                bool repeated = 0;

                deque<numPair> combination = table[i];

                numPair temp;
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

void SixthWeek::KnapsackWithoutRepetitions()
{
    int targetSum;
    cin >> targetSum;
    int count;
    cin >> count;
    vector<int> numbers;
    copy_n(istream_iterator<int>(cin), count, inserter(numbers, numbers.begin()));

    deque<numPair> main = bestSum(targetSum, numbers);

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
}

//******************************
/**
 *
 * @brief
 *
 * Partitioning Souvenirs
 *
 * @return true
 * @return false
 */

deque<numPair> howSum(int targetSum, vector<int> &numbers)
{
    map<int, deque<numPair>> table;
    table[0].push_back({0, 0});

    for (size_t i = 0; i <= targetSum; i++)
    {
        if (!table[i].empty())
        {
            for (int num = 0; num < numbers.size(); num++)
            {
                bool repeated = 0;

                deque<numPair> combination = table[i];

                numPair temp;
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

    if (!table[targetSum].empty())
    {
        return table[targetSum];
    }
    else
    {
        deque<numPair> failed;
        table[targetSum] = failed;
        return failed;
    }
}

bool SixthWeek::PartitioningSouvenirs()
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
        deque<numPair> main = howSum(targetPoint, tempNumbers);

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

        for (int num : tempNumbers)
        {
            tempNumbers.erase(remove(tempNumbers.begin(), tempNumbers.end(), num), tempNumbers.end());
        }
    }
    
    return true;
}