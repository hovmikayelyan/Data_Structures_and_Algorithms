/**
 * @file submited.cpp
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

struct Query
{
    string type, name;
    size_t number;
};

class QueryProcessor
{

    int BUCKET;
    unordered_map<int, list<string>> table;

    size_t hash(const string &s) const
    {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % BUCKET;
    }

public:
    QueryProcessor(int V)
    {
        this->BUCKET = V;
    }

    void insertItem(const string &s)
    {
        if (findItem(s))
            return;

        size_t key = hash(s);
        table[key].push_front(s);
    }

    void deleteItem(const string &s)
    {
        size_t key = hash(s);

        auto &row = table[key];
        auto it = std::find(row.begin(), row.end(), s);

        if (it != row.end())
            row.erase(it);
    }

    bool findItem(const string &s)
    {
        size_t key = hash(s);
        auto &row = table[key];
        auto it = std::find(row.begin(), row.end(), s);

        return (it != row.end()) ? true : false;
    }

    string checkItem(int key)
    {
        ostringstream elems;
        auto &row = table[key];
        copy(row.begin(), row.end(), ostream_iterator<string>(elems, " "));

        return elems.str();
    }
};

vector<Query> read_queries(int S)
{
    vector<Query> queries(S);
    for (int i = 0; i < S; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type != "check")
            cin >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void process_queries(const vector<Query> &queries, int &buckets_size, int &queries_size)
{
    QueryProcessor hashes(buckets_size);
    vector<string> result;

    for (size_t i = 0; i < queries_size; ++i)
    {
        string cmd = queries[i].type;
        if (cmd == "add")
        {
            hashes.insertItem(queries[i].name);
        }
        if (cmd == "del")
        {
            hashes.deleteItem(queries[i].name);
        }
        if (cmd == "find")
        {
            bool found = hashes.findItem(queries[i].name);
            found ? result.emplace_back("yes") : result.emplace_back("no");
        }
        if (cmd == "check")
        {
            string found = hashes.checkItem(queries[i].number);
            result.emplace_back(found);
        }
    }

    copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));
}

int main()
{
    ios_base::sync_with_stdio(false);
    int buckets_size, queries_size;
    cin >> buckets_size >> queries_size;

    process_queries(read_queries(queries_size), buckets_size, queries_size);
    return 0;
}