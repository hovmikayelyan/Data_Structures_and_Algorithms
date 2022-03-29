#include <iostream>
#include <deque>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

class StackWithMax
{
private:
    deque<int> stack;
    deque<int> max;

public:
    void Push(int value)
    {
        if (max.empty())
        {
            max.push_back(value);
        }
        else
        {
            if (value >= max.back())
                max.push_back(value);
        }

        stack.push_back(value);
    }

    void Pop()
    {
        assert(stack.size());

        if (stack.back() == max.back())
            max.pop_back();

        stack.pop_back();
    }

    int Max() const
    {
        assert(stack.size());
        return max.back();
    }
};

int main()
{
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i)
    {
        cin >> query;
        if (query == "push")
        {
            cin >> value;
            stack.Push(stoi(value));
        }
        else if (query == "pop")
        {
            stack.Pop();
        }
        else if (query == "max")
        {
            cout << stack.Max() << "\n";
        }
        else
        {
            assert(0);
        }
    }
    return 0;
}