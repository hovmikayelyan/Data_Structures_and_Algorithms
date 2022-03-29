#pragma once

#include <vector>

namespace FirstWeek
{
    /**
     * @brief 
     * Necassary Data for functions.
     */
    class Data;

    /**
     * @brief 
     * 
     * Find the maximum product of two distinct numbers in a sequence of non-negative integers.
     * @return int 
     */
    int MaxPairwiseProduct();

}

/**
 * @brief 
 * Necassary Data for functions.
 */
class FirstWeek::Data
{
private:
    int size;
    std::vector<int> Element;

public:
    Data();

    void setMaxPairwiseProductInfo(int size, std::vector<int> &Element);

    int getSize()
    {
        return this->Element.size();
    }

    void MaxElement_1and5comp(int *ref);

    int MaxPairwiseProductNaive();

    int MaxPairwiseProductFast();

    bool StressTest(int x, int y);

    virtual ~Data();
};
