#pragma once
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

bool is_prime( int n) {
  if(n==2||n==3) return true;
  if(n==1||n%2==0) return false;
  for (size_t i = 3; i*i <= n; ++(++i)) {
    if(n%i==0) return false;
  }
  return true;
}

int next_prime(int n) {
  if(n%2==0) ++n;
  for(;is_prime(n);n+=2) ;
  return n;
}

size_t hash(const string &key) {
  size_t hash_val = 0;
  for( char ch:key)
    hash_val = 37*hash_val + ch;
  return hash_val;
}

size_t hash(int key) {
  return key;
}

template < typename o >
class hash_table {
public:
  explicit hash_table (int hash_size = 101) : size(0), table(hash_size) {}
  bool contains (const o& x) const { 
    auto & the_list = table[hash_function(x)];
    return find(begin(the_list),end(the_list),x) !=end(the_list);
  }
  void make_empty() {
    for(auto & l : table)
      l.clear();
  }
  bool insert(const o& x) {
    auto & the_list = table[hash_function(x)];
    if(find(begin(the_list),end(the_list),x)!=end(the_list)) return false;
    the_list.push_back(x);
    if(++size>table.size()) rehash();
    return true;
  }
  bool insert(o&& x) {
    auto & the_list = table[hash_function(x)];
    if(find(begin(the_list),end(the_list),x)!=end(the_list)) return false;
    the_list.push_back(std::move(x));
    if(++size>table.size()) rehash();
    return true;
  }
  bool remove(const o& x) {
    auto & the_list = table[hash_function(x)];
    auto itr = find(begin(table),end(table),x);
    if(itr == end(table)) return false;
    the_list.erase(itr);
    --size;
    return true;
  }
private: 
  vector<list<o>> table;
  int size;
  void rehash() {
    auto old =table;
    table.resize(next_prime(2*table.size()));
    for(auto & l : table) l.clear();
    size = 0;
    for(auto & l : old) 
      for(auto & i : l)
        insert(std::move(i));
  }
  size_t hash_function(const o& x) {
    static hash<o> hf;
    return hf(x)%table.size();
  }
};
