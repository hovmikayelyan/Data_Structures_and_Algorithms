/**
 * @file job_queue.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>
#include <queue>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

struct Duad
{
  long long worker;
  long long started_at;
};

class JobQueue
{
private:
  int num_workers;
  deque<int> jobs;
  deque<pair<long long, long long>> start_times;
  deque<Duad> assigned_workers;

  void SiftDown_minHeap(int i)
  {
    int minIndex = i;
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    if (l < num_workers)
    {
      if (start_times[minIndex].second > start_times[l].second)
      {
        minIndex = l;
      }
      else if (start_times[minIndex].second == start_times[l].second)
      {
        if (start_times[minIndex].first > start_times[l].first)
        {
          minIndex = l;
        }
      }
    }
    if (r < num_workers)
    {
      if (start_times[minIndex].second > start_times[r].second)
      {
        minIndex = r;
      }
      else if (start_times[minIndex].second == start_times[r].second)
      {
        if (start_times[minIndex].first > start_times[r].first)
        {
          minIndex = r;
        }
      }
    }

    if (i != minIndex)
    {
      swap(start_times[minIndex], start_times[i]);

      SiftDown_minHeap(minIndex);
    }
  }

public:
  JobQueue(int num_workers, deque<int> &jobs)
  {
    this->num_workers = num_workers;
    this->jobs = jobs;

    for (int it = 0; it < num_workers; it++)
    {
      this->start_times.push_back({it, 0});
    }
  }

  void NextWorker(int job)
  {
    long long _next_worker = start_times.front().first;
    long long _started_at = start_times.front().second;

    this->assigned_workers.push_back({_next_worker, _started_at});
    this->start_times.front().second += job;

    this->SiftDown_minHeap(0);
  }

  void WriteResponse() const
  {
    for (auto elem : this->assigned_workers)
    {
      cout << elem.worker << " " << elem.started_at << "\n";
    }
  }
};

int main()
{
  ios_base::sync_with_stdio(false);

  int num_workers, jobs_size;
  cin >> num_workers >> jobs_size;
  deque<int> jobs;

  int tempNum;
  for (int i = 0; i < jobs_size; i++)
  {
    cin >> tempNum;
    jobs.push_back(tempNum);
  }

  JobQueue job_queue(num_workers, jobs);
  for (auto job : jobs)
  {
    job_queue.NextWorker(job);
  }
  deque<Duad> assigned_workers;
  job_queue.WriteResponse();

  return 0;
}
