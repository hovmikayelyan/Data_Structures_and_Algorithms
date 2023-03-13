#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

long binary_search(vector<long> &a, long x)
{
	long left = 0, right = (long)a.size();
	long mid; long result = -1;

	while (left <= right)
	{
		mid = left + (right - left) / 2;

		if (x > a[mid])
		{
			left = mid + 1;
		}
		else if (x < a[mid])
		{
			right = mid - 1;
		}
		else
		{
			result = mid;
			right = mid - 1;
		}
	}

	return result;
}

int main()
{
	int n;
	cin >> n;
	vector<long> a(n);

	for (size_t i = 0; i < a.size(); i++)
	{
		cin >> a[i];
	}

	int m;
	cin >> m;
	vector<long> b(m);

	for (int i = 0; i < m; ++i)
	{
		cin >> b[i];
	}

	sort(a.begin(), a.end());

	for (int i = 0; i < m; ++i)
	{
		cout << binary_search(a, b[i]) << ' ';
	}
}
