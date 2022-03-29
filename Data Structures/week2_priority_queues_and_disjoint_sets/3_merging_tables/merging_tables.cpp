/**
 * @file merging_tables.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement
{
	int size;
	int parent_index = -1;
	int rank = 0;
};

struct DisjointSets
{
	int n;
	int max_table_size = 0;

	map<int, DisjointSetsElement> elems;

	DisjointSets(int size) : n(size), max_table_size(0)
	{
		for (int i = 0; i < size; i++)
			elems[i].parent_index = i;
	}

	void construct(int i, int s)
	{
		elems[i].size = s;
		max_table_size = max(max_table_size, elems[i].size);
	}

	int getParent(int index)
	{

		if (index != elems[index].parent_index)
		{
			elems[index].parent_index = getParent(elems[index].parent_index);
		}
		return elems[index].parent_index;
	}

	void merge(int destination, int source)
	{
		int realDestination = getParent(destination);
		int realSource = getParent(source);

		if (realDestination != realSource)
		{
			if (elems[realDestination].rank > elems[realSource].rank)
			{
				int s = elems[realSource].size;

				elems[realSource].size = -1;
				elems[realSource].parent_index = realDestination;

				elems[realDestination].size += s;
				max_table_size = max(max_table_size, elems[realDestination].size);
			}
			else
			{
				int s = elems[realDestination].size;

				elems[realDestination].size = -1;
				elems[realDestination].parent_index = realSource;

				elems[realSource].size += s;
				max_table_size = max(max_table_size, elems[realSource].size);

				if (elems[realDestination].rank == elems[realSource].rank)
				{
					elems[realSource].rank++;
				}
			}
		}
	}
};

int main()
{
	int n, m;
	cin >> n >> m;

	DisjointSets box(n);

	for (int i = 0; i < n; i++)
	{
		int size;
		cin >> size;
		box.construct(i, size);
	}

	for (int i = 0; i < m; i++)
	{
		int destination, source;
		cin >> destination >> source;
		--destination;
		--source;

		box.merge(destination, source);
		cout << box.max_table_size << endl;
	}

	return 0;
}
