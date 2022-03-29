#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Variety
{
  string type;
  int position;

  int index = 0;
};

struct Segment
{
  int value;
  Variety variety;
};

vector<Segment> RandomizedQuickSort(vector<int> &starts, vector<int> &ends, vector<int> &points)
{
  vector<Segment> allItems;

  int n = starts.size() + ends.size() + points.size();
  Variety temp;
  Segment segm;

  for (size_t i = 0; i < starts.size(); i++)
  {
    temp.position = 1;
    temp.type = "LEFT";
    segm = {starts[i], temp};
    allItems.push_back(segm);
  }

  for (size_t i = 0; i < ends.size(); i++)
  {
    temp.position = 3;
    temp.type = "RIGHT";
    segm = {ends[i], temp};
    allItems.push_back(segm);
  }

  for (size_t i = 0; i < points.size(); i++)
  {
    temp.position = 2;
    temp.index = i;
    temp.type = "POINT";
    segm = {points[i], temp};
    allItems.push_back(segm);
  }

  sort(allItems.begin(), allItems.end(), [](const Segment &a, const Segment &b) -> bool
       {
             if (a.value <= b.value)
             {
                 if (a.value == b.value)
                 {
                     return (a.variety.position < b.variety.position);
                 }
                 return 1;
             }
             else
             {
                 return 0;
             } });

  return allItems;
}

void fast_count_segments(vector<int> &starts, vector<int> &ends, vector<int> &points, map<int, int> &cnt)
{
  vector<Segment> allSorted = RandomizedQuickSort(starts, ends, points);

  // for (size_t i = 0; i < allSorted.size(); i++)
  // {
  //   cout << "[" << allSorted[i].value << ", " << allSorted[i].variety.type << "]";
  // }
  // cout << endl;

  int counts = 0;
  for (size_t i = 0; i < allSorted.size(); i++)
  {
    if (allSorted[i].variety.type == "LEFT")
    {
      counts++;
    }
    else if (allSorted[i].variety.type == "RIGHT")
    {
      counts--;
    }
    else
    {
      cnt.insert({allSorted[i].variety.index, counts});
    }
  }
}

void naive_count_segments(vector<int> &starts, vector<int> &ends, vector<int> &points, vector<int> &cnt)
{

  for (size_t i = 0; i < points.size(); i++)
  {
    for (size_t j = 0; j < starts.size(); j++)
    {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
}

int main()
{
  int n, m;
  cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++)
  {
    cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++)
  {
    cin >> points[i];
  }

  map<int, int> cnt;
  fast_count_segments(starts, ends, points, cnt);

  for (const auto &elem : cnt)
  {
    std::cout << elem.second << " ";
  }
  return 0;
}