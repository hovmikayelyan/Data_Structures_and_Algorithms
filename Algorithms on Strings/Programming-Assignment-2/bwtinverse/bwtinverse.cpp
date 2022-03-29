/**
 * @file bwtinverse.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>

using namespace std;

int getIndexInRrightColumn(unordered_map<char, int> &symbolsMap, char ch, int cnt)
{
    switch (ch)
    {
    case 'A':
        return cnt;
    case 'C':
        return symbolsMap['A'] + cnt;
    case 'G':
        return symbolsMap['A'] + symbolsMap['C'] + cnt;
    case 'T':
        return symbolsMap['A'] + symbolsMap['C'] + symbolsMap['G'] + cnt;
    default:
        return 0;
    }
}

string inverseBWT(const string &BWT)
{
    if (BWT.size() == 1)
    {
        return BWT;
    }

    unordered_map<char, int> symbolsMap;
    vector<int> indexes;

    indexes.reserve(BWT.size());

    for (int i = 0; i < BWT.size(); ++i)
    {
        indexes.push_back(++symbolsMap[BWT[i]]);
    }

    string temp = "$";

    temp.reserve(BWT.size());

    char ch = BWT[0];
    int j = indexes[0];

    temp += ch;

    for (int i = 2; i < BWT.size(); ++i)
    {
        int indexInRrightColumn = getIndexInRrightColumn(symbolsMap, ch, j);
        temp += BWT[indexInRrightColumn];
        j = indexes[indexInRrightColumn];
        ch = temp.back();
    }

    reverse(temp.begin(), temp.end());
    return temp;
}

int main()
{
    string BWT;
    cin >> BWT;
    cout << inverseBWT(BWT) << std::endl;

    return 0;
}