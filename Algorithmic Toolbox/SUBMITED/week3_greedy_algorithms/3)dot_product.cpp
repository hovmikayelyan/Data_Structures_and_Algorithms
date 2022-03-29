#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	int n;
	cin >> n;
	long long max_value = 0;
	vector<long long> a(n);
	vector<long long> b(n);
	
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
	
	for (int i = 0; i < n; i++)
	{
		max_value += a[i] * b[i];
	}
	
	cout << max_value;
}