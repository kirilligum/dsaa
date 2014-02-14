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

size_t my_hash(int key) {
  return key*key;
}

template<typename o>
class quadratic_probing {
public:
  explicit quadratic_probing (int size = 101) : table(next_prime(size)) { make_empty();}
  bool contains(const o& x) const {
    return is_active(find_position(x));
  }
  void make_empty() {
    isize = 0;
    for(auto & e:table) e.info=empty;
  }
  bool insert(const o & x) {
    int ipos = find_position(x);
    if(is_active(ipos)) return false;
    table[ipos].element = x;
    table[ipos].info = active;
    if(++isize>table.size()/2) rehash();
    return true;
  }
  bool insert(const o && x) {
    int ipos = find_position(x);
    if(is_active(ipos)) return false;
    table[ipos].element = std::move(x);
    table[ipos].info = active;
    if(++isize>table.size()/2) rehash();
    return true;
  }
  bool remove(const o& x) {
    int ipos = find_position(x);
    if(!is_active(ipos)) return false;
    table[ipos].info = deleted;
    return true;
  }
  enum entry_type { active, empty, deleted};
private: 
  struct entry {
    o element;
    entry_type info;
    entry(const o & e = o{}, entry_type i = empty) : element{e} , info{i} {}
    entry(o && e, entry_type i = empty) : element{std::move(e)} , info{i} {}
  };
  vector<entry> table;
  int isize;
  bool is_active( int ipos) const {
    return table[ipos].info==active;
  }
  int find_position(const o& x) const {
    int offset =1;
    int ipos = hash_function(x);
    while(table[ipos].info != empty && table[ipos].element !=x) {
      ipos += offset;
      offset +=2;
      if(ipos>=table.size()) ipos-=table.size();
    }
    return ipos;
    //return 1;
  }
  void rehash() {
    auto old = table;
    table.resize(next_prime(2*old.size()));
    for(auto & e:table) e.info = empty;
    isize=0;
    for(auto & e:old) if(e.info==active) insert(std::move(e.element));
  }
  size_t hash_function(const o& x) const {
    static hash<o> hf;
    //cout << x << "  " << my_hash(x) << "  " << my_hash(x)%table.size();
    return hf(x)%table.size();
    //return 1;
  }
};
