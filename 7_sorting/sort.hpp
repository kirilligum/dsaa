#pragma once

#include <vector>
using namespace std;

template < typename t >
void insertion_sort(vector<t> &a) {
  for (size_t i = 0; i < a.size(); ++i) {
    auto tmp = move(a[i]);
    int j =0;
    for(j=i;j>0&&tmp<a[j-1];--j) {
      a[j]=move(a[j-1]);
    }
    a[j]=move(tmp);
  }
}
