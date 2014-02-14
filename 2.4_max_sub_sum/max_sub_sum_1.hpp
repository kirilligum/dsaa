#pragma once

#include <vector>

inline int max_sub_sum_1(const std::vector<int> &v) {
  using namespace std;
  int current_sum =0, max_sum=0;
  for (size_t i = 0; i < v.size(); ++i) {
    for (size_t j = i; j < v.size(); ++j) {
      current_sum =0;
      for (size_t k = i; k <= j; ++k) {
        current_sum += v[k];
      }
      if(current_sum>max_sum)
        max_sum=current_sum;
    }
  }
  return max_sum;
}
