#pragma once

namespace SecondWeek
{
    long fibonacci_naive(int n);
    long fibonacci_fast(int n);

    long get_fibonacci_last_digit(int n);

    int NaiveGCD(int a, int b);
    int EuclidGCD(int a, int b);

    long LeastCommonMultiple(int a, int b);

    long pisano(long m);
    long fibonacciModulo(long n, long m);
    long fibonacciSum(int n, int startingFrom = 0);
    long fibonacciSumSquares(int n);

    int *findMaxTournament(int low, int high, int A[]);
    int findSecondRecursive(int n, int A[]);
    int LargestSecondElement();
}