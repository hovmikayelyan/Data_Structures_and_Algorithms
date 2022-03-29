#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

struct Pair
{
  double value, weight;
};

double solveMaxValOfLootSTRUCT()
{
  int count;
  double capacity;
  cin >> count >> capacity;
  // cout << "$\tkg\n";

  vector<Pair> items(count);

  for (int i = 0; i < count; i++)
  {
    cin >> items[i].value >> items[i].weight;
  }

  sort(items.begin(), items.end(), [](const Pair &a, const Pair &b) -> bool
       { return (a.value / a.weight) < (b.value / b.weight); });

  double sum = 0.0;
  double a;
  for (int i = 0; i < count; i++)
  {
    if (capacity <= 0)
    {
      return sum;
    }
    a = min(items[i].weight, capacity);
    sum += a * (items[i].value / items[i].weight);
    items[i].weight -= a;
    capacity -= a;
  }
  return sum;
}

double solveMaxValOfLoot()
{
  int count;
  double capacity;
  cin >> count >> capacity;
  // cout << "$\tkg\n";
  double **items = new double *[count];
  for (int i = 0; i < count; i++)
  {
    items[i] = new double[3];
  }
  for (int i = 0; i < count; i++)
  {
    // the v
    cin >> items[i][0];
    // the w
    cin >> items[i][1];
    // v/w
    items[i][2] = items[i][0] / items[i][1];
  }

  double *temp;
  for (int i = 0; i < count; i++)
  {
    for (int j = i + 1; j < count; j++)
    {

      if (items[i][2] < items[j][2])
      {
        temp = *(items + i);
        *(items + i) = *(items + j);
        *(items + j) = temp;
      }
    }
  }
  // cout << endl
  //      << "printing" << endl;
  // for (int i = 0; i < count; i++)
  // {
  //   for (int j = 0; j < 2; j++)
  //   {
  //     cout << items[i][j] << "\t";
  //   }
  //   cout << endl;
  // }

  double sum = 0.0;
  double a;
  for (int i = 0; i < count; i++)
  {
    if (capacity <= 0)
    {
      return sum;
    }
    a = min(items[i][1], capacity);
    sum += a * items[i][2];
    items[i][1] -= a;
    capacity -= a;
  }
  return sum;
}

int main()
{
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(4);
  cout << solveMaxValOfLoot() << endl;
  return 0;
}