/**
 * @file tree-height.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-11-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

struct Node
{
  int index;
  Node *parent;
  vector<Node *> children;

  Node()
  {
    this->parent = NULL;
  }

  void setParent(Node *theParent)
  {
    parent = theParent;
    parent->children.push_back(this);
  }
};

void implementNode(int count, vector<Node> &nodes)
{

  for (size_t i = 0; i < count; i++)
  {
    int parent_index;
    cin >> parent_index;

    if (parent_index >= 0)
    {
      nodes[i].setParent(&nodes[parent_index]);
    }
    nodes[i].index = i;
  }
}

int countOfParent(Node &node, map<int, int> &memo)
{
  if (memo.find(node.index) != memo.end())
  {
    return memo[node.index];
  }

  if (node.parent == NULL)
  {
    memo[node.index] = 1;
    return 1;
  }

  memo[node.index] = 1 + countOfParent(*(node.parent), memo);
  return memo[node.index];
}

int heightOfTree(int count, vector<Node> &nodes, map<int, int> &memo)
{
  set<int> sums;

  queue<Node> q;
  for (auto elem : nodes)
  {
    q.push(elem);
  }

  while (!q.empty())
  {
    int maxHeight = 0;

    Node temp = q.front();
    q.pop();

    if (temp.children.empty())
    {
      maxHeight += countOfParent(temp, memo);
    }
    sums.insert(maxHeight);
  }

  return *(sums.rbegin());
}

int main()
{
  ios_base::sync_with_stdio(0);
  int count;
  cin >> count;

  vector<Node> nodes(count);
  map<int, int> memo;

  implementNode(count, nodes);
  cout << heightOfTree(count, nodes, memo) << endl;

  return 0;
}