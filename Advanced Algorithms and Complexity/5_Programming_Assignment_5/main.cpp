/**
 * @file main.cpp
 * @author Hovhannes Mikayelyan (@hovmikayelyan)
 * @brief
 * @version 0.1
 * @date 2022-03-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <random>

using std::vector;

struct hash_function
{
  long a, b, p, m;
  long operator()(long x) const noexcept { return ((a * x + b) % p) % m; }
};

struct sign_function
{
  static std::default_random_engine gen;
  static std::uniform_int_distribution<int> dist;

  sign_function() noexcept : hf{dist(gen), dist(gen), 10000019, 1000} {}

  int operator()(long x) const noexcept { return hf(x) > 500 ? 1 : -1; }

  hash_function hf;
};

std::default_random_engine sign_function::gen = std::default_random_engine();
std::uniform_int_distribution<int> sign_function::dist = std::uniform_int_distribution<int>(10, 100);

struct funcs
{
  hash_function hf;
  sign_function sf;
};

struct count_sketch
{
  count_sketch(long n) noexcept : b{(int)log(n) * 50},
                                  t{(int)log(n) + 1},
                                  data{vector<vector<long>>(t, vector<long>(b))},
                                  ith_data{vector<long>(data.size())}
  {
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist(3, 50);

    long p = 10e8 + 19;
    functions.reserve(data.size());

    for (auto i = 0; i < t; ++i)
    {
      functions.push_back(funcs{hash_function{dist(gen), dist(gen), p, b}, sign_function()});
    }
  }

  void update(long i, long frq = 1) noexcept
  {
    for (auto j = 0u; j < data.size(); ++j)
    {
      data[j][functions[j].hf(i)] += (functions[j].sf(i) * frq);
    }
  }

  long estimate(long i) noexcept
  {
    for (auto j = 0u; j < data.size(); ++j)
    {
      ith_data[j] = data[j][functions[j].hf(i)] * functions[j].sf(i);
    }

    return median();
  }

private:
  long median() noexcept
  {
    std::nth_element(ith_data.begin(), ith_data.begin() + ith_data.size() / 2, ith_data.end());
    return *std::next(ith_data.begin(), ith_data.size() / 2);
  }

  const int b, t;

  vector<funcs> functions;
  vector<vector<long>> data;
  vector<long> ith_data;
};

int main()
{
  long n, t, id, merit;
  scanf("%ld %ld", &n, &t);

  count_sketch algo(n);

  for (long i = 0; i < n; ++i)
  {
    scanf("%ld %ld", &id, &merit);
    algo.update(id, merit);
  }

  for (long i = 0; i < n; ++i)
  {
    scanf("%ld %ld", &id, &merit);
    algo.update(id, -merit);
  }

  int num_queries = 0;
  scanf("%d", &num_queries);

  for (int q = 0, query = 0; q < num_queries; ++q)
  {
    scanf("%d", &query);
    printf("%c ", (algo.estimate(query) >= t) ? '1' : '0');
  }

  printf("\n");

  return 0;
}