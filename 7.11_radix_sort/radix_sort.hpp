#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

template<typename t> void radix_sort(vector<t> &l) {
  vector<vector<t>> buckets(26);
  for(int i=l.front().size()-1;i>=0;--i) {
    for(auto il: l) {
      buckets[il[i]-'a'].push_back(move(il));
    }
    l.clear();
    for(auto &ib: buckets){
      for(auto &jb:ib)
        l.push_back(move(jb));
      ib.clear();
    }
  }
}


