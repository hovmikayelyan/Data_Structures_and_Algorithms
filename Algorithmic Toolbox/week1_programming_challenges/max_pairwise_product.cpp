#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Data
{
private:
    int size;
    std::vector<long long> Element;

public:
    Data(){
        
    };

    void setMaxPairwiseProductInfo(int size, vector<long long> &Element)
    {
        (*this).size = size;
        (*this).Element = Element;
    }

    void MaxElement_1and5comp(int *ref)
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

    long long MaxPairwiseProductNaive()
    {
        long long product = 0;
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

    long long MaxPairwiseProductFast()
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

    bool StressTest(int x, int y)
    {
        if (x == y)
        {
            return 1;
        }
        return 0;
    }

    ~Data()
    {
    }
};

/**
 * @brief
 *
 * @return int
 */
int MaxPairwiseProduct()
{
    int n;
    cin >> n;
    vector<long long> numbers(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> numbers[i];
    }

    Data Elem;
    Elem.setMaxPairwiseProductInfo(n, numbers);

    long long product2 = Elem.MaxPairwiseProductFast();

    cout << product2 << endl;
    return 0;
}

int main()
{
    MaxPairwiseProduct();
    return 0;
}
