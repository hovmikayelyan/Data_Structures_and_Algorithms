#include "FirstWeek.h"

#include <iostream>
#include <math.h>
using namespace std;

FirstWeek::Data::Data()
{
}

void FirstWeek::Data::setMaxPairwiseProductInfo(int size, vector<int> &Element)
{
    (*this).size = size;
    (*this).Element = Element;
}

void FirstWeek::Data::MaxElement_1and5comp(int *ref)
{
    int t = 0, min, max;
    for (int i = 0, j = size - 1; i < j; i++, j--)
    {
        if (Element[i] > Element[j])
        {
            t = Element[i], Element[i] = Element[j], Element[j] = t;
        }
    }
    min = Element[0];
    for (int i = 0; i < size / 2; i++)
    {
        if (Element[i] < min)
        {
            min = Element[i];
        }
    }
    max = Element[size / 2];
    for (int j = size / 2 + 1; j < size; j++)
    {
        if (Element[j] > max)
        {
            max = Element[j];
        }
    }

    ref[0] = min;
    ref[1] = max;
}

int FirstWeek::Data::MaxPairwiseProductNaive()
{
    int product = 0;
    int n = Element.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            product = max(product, Element[i] * Element[j]);
        }
    }
    return product;
}

int FirstWeek::Data::MaxPairwiseProductFast()
{
    int n = Element.size();
    int index1 = 0;
    for (int i = 1; i < n; i++)
    {
        if (Element[i] > Element[index1])
            index1 = i;
    }
    int index2 = (index1 == 0 ? 1 : 0);
    for (int i = 0; i < n; ++i)
    {
        if (i != index1 && Element[i] > Element[index2])
        {
            index2 = i;
        }
    }
    return Element[index1] * Element[index2];
}

bool FirstWeek::Data::StressTest(int x, int y)
{
    if (x == y)
    {
        return 1;
    }
    return 0;
}

FirstWeek::Data::~Data()
{
}


/**
 * @brief 
 * 
 * @return int 
 */
int FirstWeek::MaxPairwiseProduct()
{
    int n;
    cin >> n;
    vector<int> numbers(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> numbers[i];
    }

    FirstWeek::Data Elem;
    Elem.setMaxPairwiseProductInfo(n, numbers);

    int product1 = Elem.MaxPairwiseProductNaive();
    int product2 = Elem.MaxPairwiseProductFast();

    if (!Elem.StressTest(product1, product2))
    {
        cout << "Wrong answer: " << product1 << " , " << product2 << "\n";
        return 1;
    }

    cout << "OK \nMaxPairwiseProduct: " << product1 << endl;

    cout << "\nThe min and max code:\n";

    int *maxAndMin = new int[2];
    Elem.MaxElement_1and5comp(maxAndMin);

    cout << maxAndMin[0] << " " << maxAndMin[1] << endl
         << endl;
    return 0;
}
