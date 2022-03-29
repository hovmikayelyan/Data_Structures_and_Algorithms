#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> arr(n);
  map<int, int> countsArr;
  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
    countsArr[arr[i]]++;
  }

  int maxCount = 0;
  for (auto const &elem : countsArr)
  {
    if (maxCount < elem.second)
    {
      maxCount = elem.second;
    }
  }

  cout << (maxCount > n / 2 ? 1 : 0) << endl;
  return 0;
}