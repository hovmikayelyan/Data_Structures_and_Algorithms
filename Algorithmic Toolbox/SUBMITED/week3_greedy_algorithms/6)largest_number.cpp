#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int compare(string s1, string s2)
{
    string s1s2 = s1.append(s2);
    string s2s1 = s2.append(s1);
 
    return s1s2.compare(s2s1) > 0 ? 1 : 0;
}

string largest_number(vector<string> a)
{
  sort(a.begin(), a.end(), compare);
  
  stringstream ret;
  
  for (int i = 0; i < a.size(); i++)
  {
    ret << a[i];
  }
  
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  cin >> n;
  vector<string> a(n);
  for (int i = 0; i < a.size(); i++)
  {
    cin >> a[i];
  }
  cout << largest_number(a);
}
