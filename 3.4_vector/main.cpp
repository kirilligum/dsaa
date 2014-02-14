#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "vec.hpp"
#include "vec_it.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  vec<int> v(10,2);
  cout << v.size() << "  " << v.capacity() << "  ";
  copy(begin(v),end(v),ostream_iterator<int>(cout," "));cout <<endl;
  v.push_back(4);
  cout << v.size() << "  " << v.capacity() << "  ";
  copy(begin(v),end(v),ostream_iterator<int>(cout," "));cout <<endl;
  vec_it<int> bt(v.begin());
  vec_it<int> et(v.end());
  for(vec_it<int> it=bt;it!=et;++it)
    cout << *it << " ";
  cout << endl;
  return 0;
}
