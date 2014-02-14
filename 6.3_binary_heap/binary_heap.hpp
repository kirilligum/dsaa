#pragma once
#include <vector>
using namespace std;

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

template < typename o >
class binary_heap {
public:
  explicit binary_heap (int capacity = 100) 
    : array(capacity+1), current_size{0} {}
  explicit binary_heap (const vector<o> & items) 
    : array(items.size()+10),current_size{items.size()} {
    for (size_t i = 0; i < items.size(); ++i) {
      array[i+1]=items[i];
      build_heap();
    }
  }
  bool is_empty() {
    return current_size==0;
  }
  const o& find_min() {
    if(is_empty()) throw UnderflowException{};
    return array[1];
  }
  void insert( const o & x) {
    if(array.size()==current_size+1) array.resize(array.size()*2);
    int hole = ++current_size;
    o copy = x;
    array[0]=std::move(copy);
    for(;x<array[hole/2];hole/=2) {
      array[hole]=std::move(array[hole/2]);
    }
    array[hole]=std::move(array[0]);
  }
  void delete_min() {
    if(is_empty()) throw UnderflowException{};
    array[1]=std::move(array[current_size--]);
    prelocate_down(1);
  }
  void delete_min( o & min_item) {
    if(is_empty()) throw UnderflowException{};
    min_item = std::move(array[1]);
    array[1] = std::move(array[current_size--]);
    prelocate_down(1);
  }
  void make_empty() {
    current_size = 0;
  }
private: 
  int current_size;
  vector<o> array;
  void build_heap() {
    for( int i= current_size/2;i>0;--i)
      prelocate_down(i);
  }
  void prelocate_down(int hole) {
    int child;
    o tmp = std::move(array[hole]);
    for( ;hole*2<=current_size; hole=child){
      child = hole*2;
      if(child!=current_size && array[child+1]<array[child]) ++child;
      if(array[child]<tmp)
        array[child] = std::move(array[child]);
      else
        break;
    }
    array[hole]=std::move(tmp);
  }
};
