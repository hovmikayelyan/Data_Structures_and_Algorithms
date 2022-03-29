/**
 * @file phiX174_error_free_overlap.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief
 * @version 0.1
 * @date 2022-03-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

int calculateOverlap(const string &a, const string &b, const int mer) noexcept
{
    //step by step counting overlap
    for (int i = 0, n = 1 + a.size() - mer; i < n; ++i)
        if (strncmp(b.c_str(), a.c_str() + i, a.size() - i) == 0)
            return a.size() - i;
    return 0;
}

string AssembleGenome(vector<string> reads, const int mer) noexcept
{
    //our genome
    string gen;
    gen.reserve(1000);
    gen += reads.front();

    string first_read = reads.front(), cur_read = "";
    int cur_index = 0;

    while (reads.size() > 1)
    {
        cur_read = move(reads[cur_index]);
        reads.erase(reads.begin() + cur_index);

        int OverlapMax = -1;

        //loop through reads
        for (int j = 0; j < reads.size(); ++j)
        {
            int overlap = calculateOverlap(cur_read, reads[j], mer);
            if (overlap > OverlapMax)
                OverlapMax = overlap, cur_index = j;
        }

        gen += reads[cur_index].substr(OverlapMax);
    }

    gen.erase(0, calculateOverlap(reads[0], first_read, mer));
    return gen;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //All reads
    vector<string> reads;
    reads.reserve(1618);

    string s;
    while (cin >> s)
        if (reads.back() != s)
            reads.push_back(move(s));

    cout << AssembleGenome(move(reads), 12) << endl;

    return 0;
}