/**
 * @file is_bst_hard.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-28
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <bits/stdc++.h>

using namespace std;

struct Node
{
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

struct Trio
{
  long long min;
  Node elem;
  long long max;

  Trio(long long min, Node elem, long long max) : min(min), elem(elem), max(max) {}
};

class BinaryTree
{
private:
  int nodes;
  vector<Node> tree;
  deque<Trio> stack;

public:
  BinaryTree()
  {
    int n;
    cin >> n;
    this->nodes = n;

    if (nodes)
    {
      for (int i = 0; i < nodes; ++i)
      {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
      }
    }
  }

  int getCount()
  {
    return nodes;
  }

  bool IsBinarySearchTree()
  {
    stack.push_back(Trio(-9223372036854775807, tree[0], 9223372036854775807));

    while (!stack.empty())
    {
      Trio temp = stack.back();
      stack.pop_back();

      if (temp.elem.key < temp.min || temp.elem.key >= temp.max)
        return false;
      if (temp.elem.left != -1)
        stack.push_back(Trio(temp.min, tree[temp.elem.left], temp.elem.key));
      if (temp.elem.right != -1)
        stack.push_back(Trio(temp.elem.key, tree[temp.elem.right], temp.max));
    }
    return true;
  }
};

int main()
{
  BinaryTree tree;

  if (tree.getCount() == 0 || tree.IsBinarySearchTree())
  {
    cout << "CORRECT" << endl;
    return 1;
  }
  else
  {
    cout << "INCORRECT" << endl;
    return 0;
  }
}