#include <iostream>
#include <vector>

using std::pair;
using std::vector;

int reach(vector<vector<int>> &adj, int a, int b)
{
  for (auto elem : adj[a])
  {
    if (elem == b)
    {
      return 1;
    }
  }
  return 0;
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
