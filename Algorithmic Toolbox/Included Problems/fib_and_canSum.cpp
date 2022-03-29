#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

long long fib(int n, map<int, long long> &memo)
{
    if (memo.find(n) != memo.end())
    {
        return memo[n];
    }

    if (n <= 2)
    {
        return 1;
    }

    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
    return memo[n];
}

bool canSum(int targetSum, vector<int> &numbers, map<int, long long> &memo)
{
    if (memo.find(targetSum) != memo.end())
    {
        return memo[targetSum];
    }
    if (targetSum == 0)
        return true;
    if (targetSum < 0)
        return false;

    for (auto num : numbers)
    {
        int remainder = targetSum - num;
        if (canSum(remainder, numbers, memo) == true)
        {
            memo[targetSum] = true;
            return true;
        }
    }

    memo[targetSum] = false;
    return false;
}

int main()
{
    map<int, long long> memo;
    vector<int> numbers = {5, 3, 4, 7};
    cout << canSum(7, numbers, memo);
    cout << endl;
    return 0;
}