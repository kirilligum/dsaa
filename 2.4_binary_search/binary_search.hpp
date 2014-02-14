#pragma once
#include <vector>

using namespace std;

template<typename C>
int binary_search(const vector<C> & v, const C & x) {
  int low = 0, high = v.size()-1;
  while (low<=high) {
    int mid = (low+high)/2;
    if (v[mid]<x)
      low=mid+1;
    else if (v[mid]>x)
      high=mid-1;
    else 
      return mid;
  }
  return -1;
}
