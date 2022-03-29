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

deque<Pair> howSum(int targetSum, vector<int> &numbers)
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