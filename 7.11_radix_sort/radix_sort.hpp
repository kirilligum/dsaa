#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <boost/range/numeric.hpp>

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


template<typename t> void counting_radix_sort(vector<t> &l) {
  vector<t> buf=l;
  vector<t> *in=&l;
  vector<t> *out=&buf;
  for(int pos=l.front().size()-1; pos>=0; --pos) {
    int nbusk=256;
    vector<int> count(nbusk);
    for(auto s:(*in))
      ++count[s[pos]+1];
    boost::partial_sum(count,begin(count));
    for(auto s:(*in))
      (*out)[count[s[pos]]++]=move(s);
    swap(in,out);
  }
  if(l.front().size()%2==1)
    for (size_t i = 0; i < l.size(); ++i) {
      (*out)[i]=move((*in)[i]);
    }
}

template<typename t> void vari_radix_sort(vector<t> &l) {
  int max_length=12;
  vector<vector<t>> by_length(max_length+1);
  vector<vector<t>> buckets(256);
  for(auto s:l)
    by_length[s.size()].push_back(move(s));
  int idx=0;
  for(auto&b:by_length)
    for(auto&bl:b)
      l[idx++]=move(bl);
  int starting_index = l.size();
  for(int pos=by_length.size()-1; pos>=0;--pos) {
    starting_index-=by_length[pos+1].size();
    for(int i=starting_index;i<l.size();++i)
      buckets[l[i][pos]].push_back(move(l[i]));
    idx=starting_index;
    for(auto&b:buckets) {
      for(auto&s:b)
        l[idx++]=move(s);
      b.clear();
    }
  }
}
