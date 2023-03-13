#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Segment
{
  int start, end;
};
/*******************************
 * @brief
 * Collecting Signatures
 */
void optimal_points()
{
  int n;
  cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i)
  {
    cin >> segments[i].start >> segments[i].end;
  }

  sort(segments.begin(), segments.end(), [](const Segment &a, const Segment &b) -> bool
       { return (a.end < b.end); });

  vector<int> points;
  int temp = segments[0].end;
  points.push_back(temp);
  for (size_t i = 1; i < segments.size(); i++)
  {
    if (temp < segments[i].start || temp > segments[i].end)
    {
      temp = segments[i].end;
      points.push_back(temp);
    }
  }

  cout << points.size() << "\n";

  for (size_t i = 0; i < points.size(); i++)
  {
    cout << points[i] << "\n";
  }
}

int main()
{
  optimal_points();
}
