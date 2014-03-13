#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>

#include "disj_sets.hpp"

using namespace std;
using namespace boost;

int main(int argc, char const *argv[]) {
  cout << " hi \n";
  vector<int> a(10);
  iota(a,0);
  copy(a,ostream_iterator<int>(cout,"  "));
  disj_sets(10);
  return 0;
}
