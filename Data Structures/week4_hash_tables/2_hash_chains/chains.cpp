/**
 * @file main.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-16
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

class Hash
{
private:
    int BUCKET;

    unordered_map<int, string> *names;

public:
    Hash(int V)
    {
        this->BUCKET = V;
        names = new unordered_map<int, string>[BUCKET];
    }

    size_t hashFunction(const string &s) const
    {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % BUCKET;
    }

    void insertItem(string name, int it)
    {
        size_t index = hashFunction(name);

        names[index].insert({it, name});
    }

    bool findItem(string key)
    {
        int index = hashFunction(key);
        unordered_map<int, string>::iterator i;

        for (i = names[index].begin();
             i != names[index].end(); i++)
        {
            // compare(str1, str2, max(str1.length(), str2.length())
            if (i->second == key)
                break;
        }

        if (i != names[index].end())
            return true;

        return false;
    }

    string findItemPos(int key)
    {
        string result = "";

        if (!names[key].empty())
        {
            for (auto elem : names[key])
            {
                result += elem.second + " ";
            }
        }

        return result;
    }

    void deleteItem(string key)
    {
        int index = hashFunction(key);
        int it;
        bool status = 0;
        for (auto elem : names[index])
        {
            if (elem.second == key)
            {
                it = elem.first;
                status = 1;
                break;
            }
        }

        if (status)
        {
            names[index].erase(it);
        }
    }
};

struct Query
{
    string type, name;
    size_t number;
};

void write_responses(const vector<string> &result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

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

vector<string> process_queries(const vector<Query> &queries, int bucket_size)
{
    vector<string> result;

    Hash hashes(bucket_size);

    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add")
        {
            if (!hashes.findItem(queries[i].name))
            {
                hashes.insertItem(queries[i].name, i);
            }
        }
        else if (queries[i].type == "del")
        {
            hashes.deleteItem(queries[i].name);
        }
        else if (queries[i].type == "find")
        {
            string response = "no";
            if (hashes.findItem(queries[i].name))
            {
                response = "yes";
            }

            result.push_back(response);
        }
        else
        {
            string response = hashes.findItemPos(queries[i].number);

            result.push_back(response);
        }
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int n, S;
    cin >> n >> S;
    write_responses(process_queries(read_queries(S), n));
    return 0;
}
