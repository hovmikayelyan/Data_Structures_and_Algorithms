#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minRefills(int tank, vector<long> stations, int dPoint)
{
	int numRefills = 0;
	int currPoint = 0;
	int sPoint = 0;

	while (currPoint <= stations.size()-1)
	{
		if (dPoint - sPoint <= tank)
			return numRefills;

		if (stations[currPoint + 1] - stations[currPoint] > tank)
			return -1;

		while (stations[currPoint] - sPoint <= tank)
		{
			if (currPoint == stations.size()-1)
				break;

			currPoint++;
		}
		
		currPoint--;

		sPoint = stations[currPoint];

		if (currPoint == stations.size()-1)
			sPoint = dPoint;

		numRefills++;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	int sPoint = 0;
	int dPoint = 0;
	cin >> dPoint;
	int tank;
	cin >> tank;
	int stationsCount;
	cin >> stationsCount;
	vector<long> stations(stationsCount);

	for (int i = 0; i < stationsCount; i++)
	{
		cin >> stations[i];
	}

	stations.push_back(dPoint);
	int result = minRefills(tank, stations, dPoint);
	cout << result;
}