#include "ThirdWeek.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <climits>
#include <bits/stdc++.h>

using namespace std;

/*************************
 * @brief 
 * 
 * @param x 
 * @param n 
 * @param L 
 * @return int 
 */
int ThirdWeek::MinRefills(int *x, int n, int L)
{
    x = new int[n];
    int numRefills = 0;
    int currentRefill = 0;
    int lastRefill;
    while (currentRefill <= n)
    {
        lastRefill = currentRefill;

        while (x[currentRefill + 1] - x[lastRefill])
        {
            currentRefill++;
        }
        if (currentRefill == lastRefill)
        {
            return -1;
        }
        if (currentRefill <= n)
        {
            numRefills++;
        }
    }
    return 0;
}


/********************************************
 * @brief 
 * Money Change
 * @return int 
 */

int ThirdWeek::solveMoneyChange()
{
    int n;
    cin >> n;

    set<int, greater<int>> Coins;

    copy_n(istream_iterator<int>(cin), n, inserter(Coins, Coins.begin()));

    int cash;
    cin >> cash;

    int sum = 0;
    for (int i : Coins)
    {
        sum += cash / i;
        cash -= (cash / i) * i;
    }
    cout << sum << endl;
    return sum;
}

/***********************************
 * @brief 
 * Maximum Value of the Loot
 * @return double 
 */


double ThirdWeek::solveMaxValOfLootSTRUCT()
{
    int count;
    double capacity;
    cin >> count >> capacity;
    cout << "$\tkg\n";

    vector<Pair> items(count);

    for (int i = 0; i < count; i++)
    {
        cin >> items[i].value >> items[i].weight;
    }

    sort(items.begin(), items.end(), [](const Pair &a, const Pair &b) -> bool
         { return (a.value / a.weight) < (b.value / b.weight); });

    double sum = 0.0;
    double a;
    for (int i = 0; i < count; i++)
    {
        if (capacity <= 0)
        {
            return sum;
        }
        a = min(items[i].weight, capacity);
        sum += a * (items[i].value / items[i].weight);
        items[i].weight -= a;
        capacity -= a;
    }
    return sum;
}

double ThirdWeek::solveMaxValOfLoot()
{
    int count;
    double capacity;
    cin >> count >> capacity;
    cout << "$\tkg\n";
    double **items = new double *[count];
    for (int i = 0; i < count; i++)
    {
        items[i] = new double[3];
    }
    for (int i = 0; i < count; i++)
    {
        //the v
        cin >> items[i][0];
        //the w
        cin >> items[i][1];
        // v/w
        items[i][2] = items[i][0] / items[i][1];
    }

    double *temp;
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {

            if (items[i][2] < items[j][2])
            {
                temp = *(items + i);
                *(items + i) = *(items + j);
                *(items + j) = temp;
            }
        }
    }
    cout << endl
         << "printing" << endl;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << items[i][j] << "\t";
        }
        cout << endl;
    }

    double sum = 0.0;
    double a;
    for (int i = 0; i < count; i++)
    {
        if (capacity <= 0)
        {
            return sum;
        }
        a = min(items[i][1], capacity);
        sum += a * items[i][2];
        items[i][1] -= a;   //animast chi?? hanumes kilon, bayc meka el ira vra het chi galu, so....
        capacity -= a;
    }
    return sum;
}


/****************************************
 * @brief 
 * Maximum Advertisement Revenue
 * @return int 
 */
int ThirdWeek::MaximumAdvertisementRevenue()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long result = 0;
    for (int i = 0; i < a.size(); i++)
    {
        result += ((long long)a[i]) * b[i];
    }
    return result;
}

/*******************************
 * @brief 
 * Collecting Signatures
 */
void ThirdWeek::optimal_points()
{
    int n;
    cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i)
    {
        cin >> segments[i].start >> segments[i].end;
    }

    sort(segments.begin(), segments.end(), [](const Segment &a, const Segment &b) -> bool
         { return (a.end < b.end); });

    vector<int> points;
    int temp = segments[0].end;
    points.push_back(temp);
    for (size_t i = 1; i < segments.size(); i++)
    {
        if (temp < segments[i].start || temp > segments[i].end)
        {
            temp = segments[i].end;
            points.push_back(temp);
        }
    }

    cout << points.size() << "\n";

    for (size_t i = 0; i < points.size(); i++)
    {
        cout << points[i] << " ";
    }
}

/************************
 * @brief 
 * Maximum Number of Prizes
 */
void ThirdWeek::optimal_summands()
{
    int n;
    std::cin >> n;
    vector<int> summands;
    for (int k = n, l = 1; k > 0; l++)
    {
        if (k <= 2 * l)
        {
            summands.push_back(k);
            k -= k;
        }
        else
        {
            summands.push_back(l);
            k -= l;
        }
    }
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i)
    {
        std::cout << summands[i] << ' ';
    }
}


/***************
 * @brief 
 * Maximum Salary
 * @param s1 
 * @param s2 
 * @return int 
 */

int compare(string s1, string s2)
{
    string s1s2 = s1.append(s2);
    string s2s1 = s2.append(s1);

    return s1s2.compare(s2s1) > 0 ? 1 : 0;
}

void ThirdWeek::largest_number()
{
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < a.size(); i++)
    {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), compare);

    stringstream ret;

    for (int i = 0; i < a.size(); i++)
    {
        ret << a[i];
    }

    string result;
    ret >> result;
    cout << result << endl;
}