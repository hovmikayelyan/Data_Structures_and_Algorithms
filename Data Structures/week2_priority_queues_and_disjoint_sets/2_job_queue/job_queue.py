#
# @file main.py
# @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
# @brief
# @version 0.1
# @date 2021-12-07
# 
# @copyright Copyright (c) 2021
#
#

from collections import namedtuple

Duad = namedtuple('Duad', ['worker', 'started_at'])


class JobQueue:
    def __init__(self, n_workers, jobs):
        self.n = n_workers
        self.jobs = jobs
        self.start_times = []
        self.assigned_jobs = []
        for i in range(self.n):
            self.start_times.append([i, 0])

    def SiftDown(self, i):
        min_index = i
        left = 2 * i + 1
        right = 2 * i + 2
        if left < self.n:
            if self.start_times[min_index][1] > self.start_times[left][1]:
                min_index = left
            elif self.start_times[min_index][1] == self.start_times[left][1]:
                if self.start_times[min_index][0] > self.start_times[left][0]:
                    min_index = left
        if right < self.n:
            if self.start_times[min_index][1] > self.start_times[right][1]:
                min_index = right
            elif self.start_times[min_index][1] == self.start_times[right][1]:
                if self.start_times[min_index][0] > self.start_times[right][0]:
                    min_index = right
        if min_index != i:
            self.start_times[i], self.start_times[min_index] = self.start_times[min_index], self.start_times[i]
            self.SiftDown(min_index)

    def NextWorker(self, job):
        root = self.start_times[0]
        next_worker = root[0]
        started_at = root[1]
        self.assigned_jobs.append(Duad(next_worker,started_at))
        self.start_times[0][1] += job
        self.SiftDown(0)


def main():
    n_workers, n_jobs = map(int, input().split())
    jobs = list(map(int, input().split()))
    assert len(jobs) == n_jobs

    job_queue = JobQueue(n_workers, jobs)
    for job in jobs:
        job_queue.NextWorker(job)
    assigned_jobs = job_queue.assigned_jobs

    for job in assigned_jobs:
        print(job.worker, job.started_at)


if __name__ == "__main__":
    main()