#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <random>
#include "radix_sort.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << " hi \n";
  vector<string> lst(10);
  int len = 10;
  random_device rd;
  uniform_int_distribution<> uni(0,25);
  for(auto &i: lst) {
    i="";
    for (int j = 0; j < len; ++j) {
      i+=static_cast<char>('a'+uni(rd));
    }
  }
  auto original=lst;
  copy(begin(lst),end(lst),ostream_iterator<string>(cout,"  "));
  cout << endl;
  lst=original;radix_sort<string>(lst);
  copy(begin(lst),end(lst),ostream_iterator<string>(cout,"  "));
  cout << endl;
  lst=original;sort(begin(lst),end(lst));
  copy(begin(lst),end(lst),ostream_iterator<string>(cout,"  "));
  cout << endl;
  return 0;
}
