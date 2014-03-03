#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "sort.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << " hi \n";
  vector<int> v(20);
  iota(begin(v),end(v),0);
  copy(begin(v),end(v),ostream_iterator<int>(cout," ")); cout << endl;
  random_shuffle(begin(v),end(v));
  copy(begin(v),end(v),ostream_iterator<int>(cout," ")); cout << endl;
  insertion_sort<int>(v);
  copy(begin(v),end(v),ostream_iterator<int>(cout," ")); cout << endl;
  return 0;
}
