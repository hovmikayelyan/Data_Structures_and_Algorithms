/**
 * @file bwt.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string BWT(const string &text)
{
  string result = "";

  vector<string> rotations(text.size());

  for (int j = 0; j < text.size(); ++j)
    rotations[j] = text.substr(text.size() - j, string::npos) + text.substr(0, text.size() - j);

  sort(rotations.begin(), rotations.end());

  for (auto &ch : rotations)
    result += ch.back();

  return result;
}

int main()
{
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}