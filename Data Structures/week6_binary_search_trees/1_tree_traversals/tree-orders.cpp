#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders
{
  int n;
  vector<int> key;
  vector<int> left;
  vector<int> right;

  vector<int> inOrderResult;
  vector<int> preOrderResult;
  vector<int> postOrderResult;

public:
  void input()
  {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);

    for (int i = 0; i < n; i++)
    {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void in_order(int root)
  {

    if (root == -1)
    {
      return;
    }

    in_order(left[root]);
    inOrderResult.push_back(key[root]);
    in_order(right[root]);

    return;
  }

  void pre_order(int root)
  {
    if (root == -1)
    {
      return;
    }

    preOrderResult.push_back(key[root]);
    pre_order(left[root]);
    pre_order(right[root]);
  }

  void post_order(int root)
  {
    if (root == -1)
    {
      return;
    }

    post_order(left[root]);
    post_order(right[root]);
    postOrderResult.push_back(key[root]);
  }

  void print(string type)
  {
    vector<int> a;
    if (type == "in")
    {
      a = inOrderResult;
    }
    else if (type == "pre")
    {
      a = preOrderResult;
    }
    else if (type == "post")
    {
      a = postOrderResult;
    }
    else
    {
      return;
    }

    for (size_t i = 0; i < a.size(); i++)
    {
      if (i > 0)
      {
        cout << ' ';
      }
      cout << a[i];
    }
    cout << '\n';
  }
};

int main_large_stack()
{
  ios_base::sync_with_stdio(0);

  TreeOrders theTree;
  theTree.input();

  theTree.in_order(0);
  theTree.print("in");

  theTree.pre_order(0);
  theTree.print("pre");

  theTree.post_order(0);
  theTree.print("post");

  return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
    if (rl.rlim_cur < kStackSize)
    {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0)
      {
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }
#endif

  return main_large_stack();
}
