/**
 * @file main.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief
 * To track time limit
 */
auto start = chrono::steady_clock::now();
bool returnStatement(bool var)
{
    cout << "\n";
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Used Time - 0," << chrono::duration<double, milli>(diff).count() << " s" << endl;

    return var;
}

/**
 * @brief
 * Main Program
 */

class Data
{
    string pattern, text;
    map<size_t, list<size_t>> hashes;

public:
    Data(string pattern, string text)
    {
        (*this).pattern = pattern;
        (*this).text = text;
    }

    void scanData()
    {
        size_t pat_size = pattern.size();
        size_t txt_size = text.size();

        for (size_t i = 0; i + pat_size <= txt_size; ++i)
        {
            std::hash<std::string> hasher;
            size_t strHash = hasher(text.substr(i, pattern.size()));
            strHash %= 10000007;

            hashes[strHash].emplace_back(i);
        }
    }

    void print()
    {
        std::hash<std::string> hasher;
        size_t myHash = hasher(pattern);
        myHash %= 10000007;
        for (auto elem : hashes[myHash])
        {
            cout << elem << " ";
        }
        cout << endl;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);

    string pattern, text;
    cin >> pattern >> text;

    Data data(pattern, text);

    data.scanData();
    data.print();
    return 0;
}
