#pragma once

#include <vector>

inline int max_sub_sum_3(const std::vector<int> &v, int left, int right) {
  using namespace std;
  if (left==right-1) {
    if(v[left]>0){
      return v[left];
    }else{
      return 0;
    }
  }
  int center = (right+left)/2;
  int current_left =0, current_right =0,max_center_left=0, max_center_right =0;
  for (int i = center-1; i >= left; --i) {
    current_left+=v[i];
    if(current_left>max_center_left) max_center_left=current_left;
  }
  for (int i = center; i <= right-1; ++i) {
    current_right+=v[i];
    if(current_right>max_center_right) max_center_right=current_right;
  }
  return max({max_sub_sum_3(v,left,center),max_sub_sum_3(v,center,right),max_center_left+ max_center_right});
}
