#include <iostream>
#include <vector>
using namespace std;

vector<int> optimal_summands(int n)
{
  vector<int> summands;
  
    for (int i = 1; n > 0; i++) {
        if (n <= 2 * i) {
            summands.push_back(n);
            n = 0;
        } else {
            summands.push_back(i);
            n -= i;
        }
    }
  
  return summands;
}

int main() {
  int n;
  cin >> n;
  vector<int> summands = optimal_summands(n);
  cout << summands.size() << endl;
  
  for (int i = 0; i < summands.size(); i++)
  {
  	cout << summands[i] << ' ';
  }
}
