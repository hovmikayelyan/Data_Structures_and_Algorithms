#include "SecondWeek.h"
#include <iostream>
#include <math.h>

using namespace std;

/**
 * @brief 
 * Greatest Common Divisor NAIVE
 * @param a 
 * @param b 
 * @return int 
 */
int SecondWeek::NaiveGCD(int a, int b)
{
    int best = 0;
    for (int d = 1; d < a + b; d++)
    {
        if (b % d == 0 && a % d == 0)
        {
            if (d > best)
            {
                best = d;
            }
        }
    }
    return best;
}

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int SecondWeek::EuclidGCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    a = a % b;
    return EuclidGCD(b, a);
}

/**
 * @brief 
 * 
 * @param n 
 * @return int 
 */
long SecondWeek::fibonacci_naive(int n)
{
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

/**
  * @brief 
  * 
  * @param n 
  * @return int 
  */
long SecondWeek::fibonacci_fast(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        long previous = 0;
        long current = 1;
        long tmp_previous;

        for (int i = 0; i < n - 1; ++i)
        {
            tmp_previous = previous;
            previous = current;
            current = tmp_previous + current;
        }

        return current;
    }
}

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return long 
 */
long SecondWeek::LeastCommonMultiple(int a, int b)
{
    long gcd = EuclidGCD(a, b);
    long leastCommon = a / gcd * b;
    return leastCommon;
}

/**
 * @brief 
 * 
 * @param n 
 * @return int 
 */
long SecondWeek::get_fibonacci_last_digit(int n)
{
    if (n <= 1)
    {
        return n % 10;
    }
    else
    {

        long previous = 0;
        long current = 1;
        long tmp_previous;

        for (int i = 0; i < n - 1; ++i)
        {
            tmp_previous = previous;
            previous = current;
            current = (tmp_previous + current) % 10;
        }

        return current;
        
    }
}

/**
 * @brief 
 * 
 * @param m 
 * @return long 
 * 
 * 
 * Calculate and return Pisano Period
 * The length of a Pisano Period for
 * a given m ranges from 3 to m * m
 */
long SecondWeek::pisano(long m)
{
    long prev = 0;
    long curr = 1;
    long res = 0;

    long temp = 0;
    for (int i = 0; i < m * m; i++)
    {
        temp = curr;
        curr = fmod((prev + curr), m);
        prev = temp;

        if (prev == 0 && curr == 1)
            res = i + 1;
    }
    return res;
}

/**
 * @brief 
 * Calculate Fn mod m
 * @param n 
 * @param m 
 * @return long 
 */
long SecondWeek::fibonacciModulo(long n, long m)
{

    // Getting the period
    long pisanoPeriod = pisano(m);

    n = fmod(n, pisanoPeriod);

    long prev = 0;
    long curr = 1;

    if (n <= 1)
    {
        return n;
    }
    else
    {
        long temp = 0;
        for (int i = 0; i < n - 1; i++)
        {
            temp = curr;
            curr = fmod((prev + curr), m);
            prev = temp;
        }
        return fmod(curr, m);
    }
}

/**
 * @brief 
 * 
 * If m is not 0, then its a from point, like from where to count the sum
 * if m=0, there is no start point
 * 
 * @param n 
 * @param m 
 * @return long 
 */

long SecondWeek::fibonacciSum(int n, int m)
{
    if (n == m)
    {
        return fibonacci_fast(n);
    }
    else
    {
        n += 2;
        long sum = get_fibonacci_last_digit(n);
        sum--;

        if (m)
        {
            sum = sum - (get_fibonacci_last_digit(m + 1) - 1);
        }
        
        return sum;
    }
}

long SecondWeek::fibonacciSumSquares(int n)
{
    return fmod((get_fibonacci_last_digit(n) * get_fibonacci_last_digit(n + 1)), 10);
}




void printarray(int *a, int size)
{

    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int* SecondWeek::findMaxTournament(int low, int high, int A[])
{
    if (low == high)
    {
        int *compared = new int[2];
        compared[0] = 2;
        compared[1] = A[low];
        return compared;
    }
    int *compared1 = findMaxTournament(low, (low + high) / 2, A);
    int *compared2 = findMaxTournament((low + high) / 2 + 1, high, A);
    if (compared1[1] > compared2[1])
    {
        int k = compared1[0] + 1;
        int *newcompared1 = new int[k];
        for (int i = 0; i < k; i++)
        {
            newcompared1[i] = compared1[i];
        }
        newcompared1[0] = k;
        newcompared1[k - 1] = compared2[1];
        return newcompared1;
    }
    int k = compared2[0] + 1;
    int *newcompared2 = new int[k];
    for (int i = 0; i < k; i++)
    {
        newcompared2[i] = compared2[i];
    }
    newcompared2[0] = k;
    newcompared2[k - 1] = compared1[1];
    return newcompared2;
}

int SecondWeek::findSecondRecursive(int n, int A[])
{
    int *firstCompared = findMaxTournament(0, n - 1, A);                             //n-1 comparisons;
    int *secondCompared = findMaxTournament(2, firstCompared[0] - 1, firstCompared); //log2(n)-1 comparisons.
    //Total comparisons: n+log2(n)-2;
    return secondCompared[1];
}

int SecondWeek::LargestSecondElement()
{
    
    cout << "Origial array: ";
    int A[] = {10, 4, 5, 8, 7, 2, 12, 3, 1, 6, 9, 11};
    int size = sizeof(A) / sizeof(*A);
    printarray(A, size);
    int secondMax = findSecondRecursive(size, A);

    cout << "Second largest number in A: " << secondMax;
    return 0;
}