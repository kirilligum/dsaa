#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <chrono>
#include <cmath>
#include <random>
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
  return key;
}
size_t my_hash(const string & key) {
  int hash_val = 0;
  for(auto ch:key) hash_val = 37*hash_val+ch;
  return hash_val;
}

int current_time_seconds() {
  auto now = chrono::high_resolution_clock::now().time_since_epoch();
  return chrono::duration_cast<chrono::seconds>(now).count();
}
class uniform_random {
public:
  uniform_random (int seed = current_time_seconds()) : generator(seed) {}
  int next_int () {
    static uniform_int_distribution<unsigned int> distribution;
    return distribution(generator);
  }
  int next_int(int high) {
    return next_int(0,high-1);
  }
  double next_double() {
    static uniform_real_distribution<double> distribution(0,1);
    return distribution(generator);
  }
  int next_int(int low, int high) {
    uniform_int_distribution<int> distribution(low, high); 
    return distribution(generator);
  }
private: 
  mt19937 generator;
};
template<int count> class string_hash_family { 
public:
  string_hash_family() : multipliers(count) {
    generate_new_functions();
  }
  int get_number_of_functions() const {
    return count;
  }
  void generate_new_functions () {
    for(auto & mult : multipliers ) mult = r.next_int();
  }
  size_t hash(const string &x, int which) const {
    const int multiplier = multipliers[which];
    size_t hash_val=0;
    for(auto ch:x) hash_val = multiplier * hash_val +ch;
    return hash_val;
  }
private:
  vector<int> multipliers;
  uniform_random r;
};

//static const double max_load 0.40;
#define max_load 0.40

template<typename o, typename f> class cuckoo_hash_table {
public:
  cuckoo_hash_table (int size =101) : table(next_prime(size)) {
    nhashfun = hash_funcations.get_number_of_functions();
    rehashes = 0;
    make_empty();
  }
  bool contains(const o& x) { return find_pos(x)!=-1;}
  void make_empty() {
    isize = 0 ;
    for(auto & e:table) e.is_active = false;
  }
  bool insert(const o& x) { 
    if(contains(x)) return false;
    if(isize>=table.size()*max_load) expand();
    return insert_helper(x);
  }
  int size() const {return isize;}
  int capacity() const { return table.size();}
  bool remove(const o& x) { 
    int pos = find_pos(x);
    if(!is_active(pos)) return false;
    table[pos].is_active = false;
    --isize;
    return true;
  }
private: 
  struct hash_entry {
    o element;
    bool is_active;
  };
  vector<hash_entry> table;
  int isize;
  int nhashfun;
  int rehashes;
  uniform_random r;
  f hash_funcations;
  static const int ALLOWED_REHASHES = 5;
  bool insert_helper(const o& xx) {
    const int count_limit=100;
    o x = xx;
    while(true) {
      int last_pos = -1;
      int pos;
      for (size_t count = 0; count < count_limit; ++count) {
        for (size_t i = 0; i < nhashfun; ++i) {
          pos = myhash(x,i);
          if(!is_active(pos)) {
            table[pos]= std::move(hash_entry{std::move(x), true});
            ++isize;
            return true;
          }
        }
        int i=0;
        do {
          pos = myhash(x,r.next_int(nhashfun));
        } while(pos==last_pos && i++ < 5);
        last_pos = pos;
        std::swap(x,table[pos].element);
      }
      if(++rehashes> ALLOWED_REHASHES) {
        expand();
        rehashes = 0;
      } else {rehash();}
    }
  }
  bool is_active(int ipos) const { return ipos!=-1 && table[ipos].is_active;}
  int find_pos(const o& x) const {
    for (size_t i = 0; i < nhashfun; ++i) {
      int pos = myhash(x,i);
      if(is_active(pos) && table[pos].element == x) return pos;
    }
    return -1;
  }
  void expand () { rehash( static_cast<int>(table.size()/max_load));}
  void rehash () { 
    hash_funcations.generate_new_functions();
    rehash(table.size());
  }
  void rehash(int new_size) {
    vector<hash_entry> old = table;
    table.resize(next_prime(new_size));
    for(auto & e:table) e.is_active = false;
    isize=0;
    for(auto& e: old) if (e.is_active) insert(std::move(e.element));
  }
  size_t myhash (const o& x, int which ) const {
    return hash_funcations.hash(x,which)%table.size();
  }
};
