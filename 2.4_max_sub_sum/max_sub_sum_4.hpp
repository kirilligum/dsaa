#pragma once

#include <vector>

inline int max_sub_sum_4(const std::vector<int> &v) {
  using namespace std;
  int isum=0,max_sum=0;
  for(auto it = begin(v); it!=end(v); ++it) {
    isum+=*it;
    if(isum>max_sum) 
      max_sum=isum;
    if(isum<0)
      isum=0;
  }
  return max_sum;
}
