#pragma once

#include <vector>

inline int max_sub_sum_2(const std::vector<int> &v) {
  using namespace std;
  int current_sum =0, max_sum=0;
  for (size_t i = 0; i < v.size(); ++i) {
    current_sum =0;
    for (size_t j = j; j < v.size(); ++j) {
      current_sum += v[j];
      if(current_sum>max_sum)
        max_sum=current_sum;
    }
  }
  return max_sum;
}
