/**
 * @file is_bst.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-27
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

class BinaryTree
{
private:
  int nodes;
  bool incorrect;
  vector<Node> tree;
  deque<int> inOrderResult;

public:
  BinaryTree()
  {
    int n;
    cin >> n;
    this->nodes = n;
    this->incorrect = 1;

    if (nodes)
    {
      this->incorrect = 0;

      for (int i = 0; i < nodes; ++i)
      {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
      }
    }
  }

  void in_order(int root)
  {
    if (incorrect)
    {
      return;
    }
    if (root == -1)
    {
      return;
    }

    in_order(tree[root].left);
    if (!inOrderResult.empty())
    {
      if (inOrderResult.back() >= tree[root].key)
      {
        incorrect = 1;
        return;
      }
    }

    inOrderResult.push_back(tree[root].key);
    in_order(tree[root].right);
  }

  bool IsBinarySearchTree()
  {
    in_order(0);
    if (nodes == 0 || !incorrect)
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
};

int main()
{
  BinaryTree tree;

  return tree.IsBinarySearchTree();
}