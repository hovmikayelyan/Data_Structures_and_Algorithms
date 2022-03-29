#include "FourthWeek.h"
#include <bits/stdc++.h>
#include <math.h>
#include <climits>

using namespace std;

/********************************************
/*
 * @brief
 * Binary search
 */

long find_binary(vector<long> &a, long x, long left, long right)
{
    if (right >= left)
    {
        long half = left + (right - left) / 2;

        if (x == a[half])
        {
            return half;
        }
        if (x > a[half])
        {
            return find_binary(a, x, half + 1, right);
        }
        return find_binary(a, x, left, half - 1);
    }

    return -1;
}

void FourthWeek::binary_search()
{
    int n;
    cin >> n;
    vector<long> a(n);
    for (size_t i = 0; i < a.size(); i++)
    {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int m;
    cin >> m;
    vector<long> b(m);
    for (int i = 0; i < m; ++i)
    {
        cin >> b[i];
    }
    for (int i = 0; i < m; ++i)
    {
        cout << find_binary(a, b[i], 0, (long)a.size()) << " ";
    }
}

/*****************************************************
/**
 * @brief
 * Find if there is majority element in array or not.
 */

void FourthWeek::MajorityElement()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    map<int, int> countsArr;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        countsArr[arr[i]]++;
    }

    int maxCount = 0;
    for (auto const &elem : countsArr)
    {
        if (maxCount < elem.second)
        {
            maxCount = elem.second;
        }
    }

    cout << (maxCount > n / 2 ? 1 : 0) << endl;
}

/*******************************************
/**
 *
 * @brief
 * Quick sort 3 partition
 */

void partition3(vector<int> &arr, int low, int high, int &i, int &j)
{
    // To handle 2 elements
    if (high - low <= 1)
    {
        if (arr[high] < arr[low])
            swap(arr[high], arr[low]);
        i = low;
        j = high;
        return;
    }

    int mid = low;
    int pivot = arr[high];
    while (mid <= high)
    {
        if (arr[mid] < pivot)
            swap(arr[low++], arr[mid++]);
        else if (arr[mid] == pivot)
            mid++;
        else if (arr[mid] > pivot)
            swap(arr[mid], arr[high--]);
    }

    // update i and j
    i = low - 1;
    j = mid; // or high+1
}

void sort3Partition(vector<int> &arr, int low, int high)
{
    if (low >= high) // 1 or 0 elements
        return;

    if (low < high)
    {

        int i, j;

        // Note that i and j are passed as reference
        partition3(arr, low, high, i, j);

        // Recur two halves
        sort3Partition(arr, low, i);
        sort3Partition(arr, j, high);
    }
}

void FourthWeek::quickSort3()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (unsigned int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    sort3Partition(arr, 0, n - 1);

    cout << "Sorted array: \n";

    for (unsigned int i = 0; i < n; ++i)
    {
        cout << arr[i] << ' ';
    }
}

/******************************************************
/**
 * @brief
 * Number of Inversions
 *
 */

int _mergeSort(vector<int> &arr, vector<int> &temp, int left, int right);
int merge(vector<int> &arr, vector<int> &temp, int left, int mid,
          int right);

/* This function sorts the
   input array and returns the
number of inversions in the array */
int mergeSort(vector<int> &arr, int array_size)
{
    vector<int> temp(array_size);
    return _mergeSort(arr, temp, 0, array_size - 1);
}

/* An auxiliary recursive function
  that sorts the input array and
returns the number of inversions in the array. */
int _mergeSort(vector<int> &arr, vector<int> &temp, int left, int right)
{
    int mid, inv_count = 0;
    if (right > left)
    {
        /* Divide the array into two parts and
        call _mergeSortAndCountInv()
        for each of the parts */
        mid = (right + left) / 2;

        /* Inversion count will be sum of
        inversions in left-part, right-part
        and number of inversions in merging */
        inv_count += _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid + 1, right);

        /*Merge the two parts*/
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

/* This funt merges two sorted arrays
and returns inversion count in the arrays.*/
int merge(vector<int> &arr, vector<int> &temp, int left, int mid,
          int right)
{
    int i, j, k;
    int inv_count = 0;

    i = left; /* i is index for left subarray*/
    j = mid;  /* j is index for right subarray*/
    k = left; /* k is index for resultant merged subarray*/
    while ((i <= mid - 1) && (j <= right))
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];

            /* this is tricky -- see above
            explanation/diagram for merge()*/
            inv_count = inv_count + (mid - i);
        }
    }

    /* Copy the remaining elements of left subarray
(if there are any) to temp*/
    while (i <= mid - 1)
        temp[k++] = arr[i++];

    /* Copy the remaining elements of right subarray
       (if there are any) to temp*/
    while (j <= right)
        temp[k++] = arr[j++];

    /*Copy back the merged elements to original array*/
    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

void FourthWeek::NumberOfInversions()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (unsigned int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    int ans = mergeSort(arr, n);
    cout << "Number of inversions are: " << ans;
}

/******************************************************
/**
 * @brief
 * Organizing a Lottery
 */

struct Variety
{
    string type;
    int position;

    int index = 0;
};

struct Segment
{
    int value;
    Variety variety;
};

vector<Segment> RandomizedQuickSort(vector<int> &starts, vector<int> &ends, vector<int> &points)
{
    vector<Segment> allItems;

    int n = starts.size() + ends.size() + points.size();
    Variety temp;
    Segment segm;

    for (size_t i = 0; i < starts.size(); i++)
    {
        temp.position = 1;
        temp.type = "LEFT";
        segm = {starts[i], temp};
        allItems.push_back(segm);
    }

    for (size_t i = 0; i < ends.size(); i++)
    {
        temp.position = 3;
        temp.type = "RIGHT";
        segm = {ends[i], temp};
        allItems.push_back(segm);
    }

    for (size_t i = 0; i < points.size(); i++)
    {
        temp.position = 2;
        temp.index = i;
        temp.type = "POINT";
        segm = {points[i], temp};
        allItems.push_back(segm);
    }

    sort(allItems.begin(), allItems.end(), [](const Segment &a, const Segment &b) -> bool
         {
             if (a.value <= b.value)
             {
                 if (a.value == b.value)
                 {
                     return (a.variety.position < b.variety.position);
                 }
                 return 1;
             }
             else
             {
                 return 0;
             } });

    return allItems;
}

void fast_count_segments(vector<int> &starts, vector<int> &ends, vector<int> &points, map<int, int> &cnt)
{
    vector<Segment> allSorted = RandomizedQuickSort(starts, ends, points);

    for (size_t i = 0; i < allSorted.size(); i++)
    {
        cout << "[" << allSorted[i].value << ", " << allSorted[i].variety.type << "]";
    }
    cout << endl;

    int counts = 0;
    for (size_t i = 0; i < allSorted.size(); i++)
    {
        if (allSorted[i].variety.type == "LEFT")
        {
            counts++;
        }
        else if (allSorted[i].variety.type == "RIGHT")
        {
            counts--;
        }
        else
        {
            cnt.insert({allSorted[i].variety.index, counts});
        }
    }
}

void naive_count_segments(vector<int> &starts, vector<int> &ends, vector<int> &points, vector<int> &cnt)
{

    for (size_t i = 0; i < points.size(); i++)
    {
        for (size_t j = 0; j < starts.size(); j++)
        {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
}

void FourthWeek::OrganizingALottery()
{
    int n, m;
    cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++)
    {
        cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++)
    {
        cin >> points[i];
    }

    map<int, int> cnt;
    fast_count_segments(starts, ends, points, cnt);

    for (const auto &elem : cnt)
    {
        std::cout << elem.second << " ";
    }
}


/*******************************************
/**
 * @brief 
 * Closest Points
 */
// void minimal_distance(){
//     size_t n;
//   std::cin >> n;
//   vector<int> x(n);
//   vector<int> y(n);
//   for (size_t i = 0; i < n; i++) {
//     std::cin >> x[i] >> y[i];
//   }
//   std::cout << std::fixed;
//   std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
// }