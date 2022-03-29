/**
 * @file phone_book.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-15
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>

using namespace std;

class Hash
{
private:
    int BUCKET;

    unordered_map<int, pair<int, string>> *table;

public:
    Hash(int V)
    {
        this->BUCKET = V;
        table = new unordered_map<int, pair<int, string>>[BUCKET];
    }

    int hashFunction(int x)
    {
        return (x % BUCKET);
    }

    bool findItem(int key)
    {
        int index = hashFunction(key);
        unordered_map<int, pair<int, string>>::iterator i;

        for (i = table[index].begin();
             i != table[index].end(); i++)
        {
            if (i->second.first == key)
                break;
        }

        if (i != table[index].end())
            return true;

        return false;
    }

    void insertItem(int key, string name, int it)
    {
        int index = hashFunction(key);

        table[index].insert({it, {key, name}});
    }

    void changeItem(int key, string name)
    {
        int index = hashFunction(key);

        int it;
        for (auto elem : table[index])
        {
            if (elem.second.first == key)
            {
                it = elem.first;
                table[index][it].second = name;
            }
        }
    }

    void deleteItem(int key)
    {
        int index = hashFunction(key);
        int it;
        bool status = 0;
        for (auto elem : table[index])
        {
            if (elem.second.first == key)
            {
                it = elem.first;
                status = 1;
                break;
            }
        }

        if (status)
        {
            table[index].erase(it);
        }
    }

    string getName(int key)
    {
        int index = hashFunction(key);

        int it;
        for (auto elem : table[index])
        {
            if (elem.second.first == key)
            {
                it = elem.first;
                return table[index][it].second;
            }
        }
        return "error";
    }
};

struct Query
{
    string type, name;
    int number;
};

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
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

    Hash hashes(queries.size());

    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add")
        {
            bool was_founded = false;

            if (hashes.findItem(queries[i].number))
            {
                hashes.changeItem(queries[i].number, queries[i].name);
                was_founded = true;
            }

            if (!was_founded)
            {
                hashes.insertItem(queries[i].number, queries[i].name, i);
            }
        }
        else if (queries[i].type == "del")
        {
            hashes.deleteItem(queries[i].number);
        }
        else
        {
            string response = "not found";
            if (hashes.findItem(queries[i].number))
            {
                response = hashes.getName(queries[i].number);
            }

            result.push_back(response);
        }
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}
