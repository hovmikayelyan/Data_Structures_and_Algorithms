#include <iostream>
#include <map>
#include <deque>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

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

int main()
{
    int targetSum = 7;
    vector<int> numbers = {5, 3, 4, 7};
    deque<int> main = bestSum(targetSum, numbers);
    main.erase(remove(main.begin(), main.end(), 0), main.end());
    for (auto num : main)
    {
        cout << num << "\t";
    }
    cout << endl;
    return 0;
}
