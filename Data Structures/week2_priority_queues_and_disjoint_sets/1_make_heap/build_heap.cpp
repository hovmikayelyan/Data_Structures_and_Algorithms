/**
 * @file build_heap.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder
{
protected:
  int size;
  vector<int> data_;
  vector<pair<int, int>> swaps_;

  void ReadData()
  {
    for (int i = 0; i < size; ++i)
    {
      int k;
      cin >> k;
      data_.push_back(k);
    }
  }

  void WriteResponse() const
  {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i)
    {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  int _parent(int it)
  {
    return (it - 1) / 2;
  }

  int _leftChild(int it)
  {
    return (2 * it) + 1;
  }

  int _rightChild(int it)
  {
    return (2 * it) + 2;
  }

  /*
  *** Correct algorithm of SiftDown and SiftUp

      void SiftUp(int i)
      {
          while (i > 1 && data_[_parent(i)] < data_[i])
          {

              swap(data_[_parent(i)], data_[i]);
              i = _parent(i);
          }
      }

      void SiftDown(int i)
      {
          int maxIndex = i;
          int l = _leftChild(i);
          if (l < size && data_[l] > data_[maxIndex])
          {
              maxIndex = l;
          }
          int r = _rightChild(i);
          if (r < size && data_[r] > data_[maxIndex])
          {
              maxIndex = r;
          }
          if (i != maxIndex)
          {
              swap(data_[i], data_[maxIndex]);
              swaps_.push_back(make_pair(i, maxIndex));
              SiftDown(maxIndex);
          }
      }

  */

  void SiftDown_minHeap(int i)
  {
    int maxIndex = i;
    int l = _leftChild(i);
    if (l < size && data_[l] < data_[maxIndex])
    {
      maxIndex = l;
    }
    int r = _rightChild(i);
    if (r < size && data_[r] < data_[maxIndex])
    {
      maxIndex = r;
    }
    if (i != maxIndex)
    {
      swap(data_[i], data_[maxIndex]);
      swaps_.push_back(make_pair(i, maxIndex));
      SiftDown_minHeap(maxIndex);
    }
  }

  void BuildHeap()
  {
    int i = (size / 2) - 1;
    for (; i >= 0; i--)
    {
      SiftDown_minHeap(i);
    }
  }

  void BuildHeap_Sort_GenerateSwaps()
  {
    swaps_.clear();
    BuildHeap();
  }

public:
  HeapBuilder(int n)
  {
    this->size = n;
  }

  void Solve()
  {
    ReadData();
    BuildHeap_Sort_GenerateSwaps();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  HeapBuilder heap_builder(n);
  heap_builder.Solve();
  return 0;
}
