#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void partition3(vector<int> &arr, int low, int high, int &i, int &j)
{
  // To handle 2 elements
  if (high - low <= 1)
  {
    if (arr[high] < arr[low])
      swap(arr[high], arr[low]);
    i = low;
    j = high;
    return;
  }

  int mid = low;
  int pivot = arr[high];
  while (mid <= high)
  {
    if (arr[mid] < pivot)
      swap(arr[low++], arr[mid++]);
    else if (arr[mid] == pivot)
      mid++;
    else if (arr[mid] > pivot)
      swap(arr[mid], arr[high--]);
  }

  // update i and j
  i = low - 1;
  j = mid; // or high+1
}

void sort3Partition(vector<int> &arr, int low, int high)
{
  if (low >= high) // 1 or 0 elements
    return;

  if (low < high)
  {

    int i, j;

    // Note that i and j are passed as reference
    partition3(arr, low, high, i, j);

    // Recur two halves
    sort3Partition(arr, low, i);
    sort3Partition(arr, j, high);
  }
}

int main()
{
  int n;
  cin >> n;
  vector<int> arr(n);
  for (unsigned int i = 0; i < n; ++i)
  {
    cin >> arr[i];
  }
  sort3Partition(arr, 0, n - 1);

  for (unsigned int i = 0; i < n; ++i)
  {
    cout << arr[i] << ' ';
  }
  return 0;
}