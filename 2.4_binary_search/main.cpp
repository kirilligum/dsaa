#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include "binary_search.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "hi\n";
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0,100);
  vector<int> v(20);
  //fill(begin(v),end(v),dis(gen));
  iota(begin(v),end(v),-10);
  copy(begin(v),end(v),ostream_iterator<int>(cout," "));
  cout << endl;
  cout << "bs 4 :  " << binary_search<int>(v,4);
  return 0;
}
