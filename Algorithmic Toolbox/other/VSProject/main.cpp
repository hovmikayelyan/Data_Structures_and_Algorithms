/**
 * @file main.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-09-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>

#include "FirstWeek.h"
#include "SecondWeek.h"
#include "ThirdWeek.h"
#include "FourthWeek.h"
#include "FifthWeek.h"
#include "SixthWeek.h"

using namespace std;

int main()
{

    // FirstWeek::MaxPairwiseProduct();
    // LargestSecondElement();

    // int a;
    // int b;
    // cin >> a >>b;

    // cout << "The last digit of Fibonacci number is: " << get_fibonacci_last_digit_naive(a) << endl;

    // cout << fibonacciSum(a,b) << endl;

    // ThirdWeek::solveMoneyChange();

    // ThirdWeek::largest_number();

    // FourthWeek::OrganizingALottery();

    // FifthWeek::primitveCalculator();

    cout << SixthWeek::PartitioningSouvenirs();

    cout << endl;

    system("pause");

    return 0;
}