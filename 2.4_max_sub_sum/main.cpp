#include <iostream>
#include <algorithm>
#include <iterator>

#include "max_sub_sum_1.hpp"
#include "max_sub_sum_2.hpp"
#include "max_sub_sum_3.hpp"
#include "max_sub_sum_4.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "hi\n";
  vector<int> v = {4,-3,5,-2,-1,2,6,-2};
  copy(begin(v),end(v),ostream_iterator<int>(cout," ")); cout << endl;
  cout << "max_sum_1 = " << max_sub_sum_1(v) << endl;
  cout << "max_sum_2 = " << max_sub_sum_2(v) << endl;
  cout << "max_sum_3 = " << max_sub_sum_3(v,0,v.size()) << endl;
  cout << "max_sum_4 = " << max_sub_sum_4(v) << endl;
  return 0;
}
