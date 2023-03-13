#pragma once

#include <vector>
#include <iterator>

namespace ThirdWeek
{
    int MinRefills(int *arr, int n, int L);

    struct Pair
    {
        double value, weight;
    };

    struct Segment
    {
        int start, end;
    };

    int solveMoneyChange();

    double solveMaxValOfLoot();
    double solveMaxValOfLootSTRUCT();

    int MaximumAdvertisementRevenue();

    void optimal_points();
    void optimal_summands();
    void largest_number();

}