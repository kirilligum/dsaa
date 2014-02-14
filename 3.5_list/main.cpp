#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "list.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << " hi \n";
  list<int> l;
  for (size_t i = 0; i < 10; ++i) l.push_back(i);
  for (auto i:l) cout << i << "  "; cout << endl;
  l.pop_back();
  l.pop_front();
  for (auto i:l) cout << i << "  "; cout << endl;
  return 0;
}
