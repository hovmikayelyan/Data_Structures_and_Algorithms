/**
 * @file main.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-13
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
#include <chrono>
auto start = chrono::steady_clock::now();
bool returnStatement(bool var)
{
    cout << "\n";
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Used Time - 0," << chrono::duration<double, milli>(diff).count() << " s" << endl;

    return var;
}

struct Query
{
    string type, name;
    int number, hash;
};

int hash_it(int number, int nel)
{
    int p, a, b;

    p = 100019; /* prime number bigger than the largest phone number */
    a = 34;     /* any integer a such that 1 <= a <= p - 1 */
    b = 2;      /* any integer b such that 1 <= b <= p - 1 */
    return ((a * number + b) % p) % nel;
}

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
        {
            cin >> queries[i].number >> queries[i].name;
        }
        else
        {
            cin >> queries[i].number;
        }
        queries[i].hash = hash_it(queries[i].number, n);
    }
    return queries;
}

void write_responses(const vector<string> &result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries)
{
    vector<string> result;
    unordered_map<int, Query> contacts;
    unordered_map<int, int> hashes;

    for (size_t i = 0; i < queries.size(); i++)
    {
        if (queries[i].type == "add")
        {
            bool was_founded = false;

            auto found_it = hashes.find(queries[i].hash);
            if (found_it != hashes.end())
            {
                int j = found_it->first;
                contacts[j].name = queries[i].name;
                was_founded = true;
            }

            if (!was_founded)
            {
                contacts.insert({i, queries[i]});
                hashes.insert({i, queries[i].hash});
            }
        }
        else if (queries[i].type == "del")
        {
            auto found_it = hashes.find(queries[i].hash);
            if (found_it != hashes.end())
            {
                int j = found_it->first;
                contacts.erase(j);
                hashes.erase(j);
            }
        }
        else
        {
            string response = "not found";
            auto found_it = hashes.find(queries[i].hash);
            // cout<<"found_it**   "<<found_it->first<<endl;
            // chi gtnum, erb vor police a linum CHGITES XI, chshti xi!!!
            if (found_it != hashes.end())
            {
                int j = found_it->first;
                response = contacts[j].name;
            }
            result.push_back(response);
        }
    }
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}