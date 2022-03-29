#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

void printMax(deque<int> arr, int n, int k)
{
    deque<int> box(k);

    size_t i;
    for (i = 0; i < k; ++i)
    {
        while ((!box.empty()) && arr[i] >= arr[box.back()])
            box.pop_back();

        box.push_back(i);
    }

    for (; i < n; ++i)
    {

        cout << arr[box.front()] << " ";

        while ((!box.empty()) && box.front() <= i - k)
            box.pop_front();

        while ((!box.empty()) && arr[i] >= arr[box.back()])
            box.pop_back();

        box.push_back(i);
    }

    cout << arr[box.front()];
}

int main()
{
    int num_queries;
    cin >> num_queries;

    deque<int> numbers;
    for (size_t i = 0; i < num_queries; i++)
    {
        int value;
        cin >> value;
        numbers.push_back(value);
    }

    int box_size;
    cin >> box_size;

    printMax(numbers, num_queries, box_size);
    return 0;
}

// int main()
// {
//     int num_queries = 0;
//     cin >> num_queries;

//     deque<int> numbers;
//     deque<int> box;

//     for (size_t i = 0; i < num_queries; i++)
//     {
//         int value;
//         cin >> value;
//         numbers.push_back(value);
//     }

//     int box_size;
//     cin >> box_size;

//     for (size_t i = 0; i < num_queries; i++)
//     {
//         box.push_back(numbers[i]);
//         if (box.size() == box_size)
//         {
//             cout << *max_element(box.begin(), box.end()) << " ";
//             box.pop_front();
//         }
//     }

//     return 0;
// }