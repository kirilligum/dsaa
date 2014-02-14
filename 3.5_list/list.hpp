#pragma once

#include <iostream>
#include <algorithm>
using namespace std;

template <typename t>
class list {
private: 
  struct node {
    t data;
    node* prev;
    node* next;
    node(const t& d = t{}, node * p = nullptr, node * n = nullptr)
      : data{d}, prev{p}, next{n} {}
    node(t&& d, node * p = nullptr, node * n = nullptr)
      : data{std::move(d)}, prev{p}, next{n} {}
  };
  int size_;
  node* head;
  node* tail;
  void init() {
    size_=0;
    head = new node;
    tail = new node;
    head->next=tail;
    tail->prev=head;
  }
public:
  class const_iterator {
    public:
      const_iterator(): current(nullptr){}
      const t& operator*() { return retrive();}
      const_iterator& operator++() {
        current=current->next;
        return *this;
      }
      const_iterator operator++(int) {
        const_iterator old = *this;
        ++(*this);
        return old;
      }
      const_iterator& operator--() {
        current=current->prev;
        return *this;
      }
      const_iterator operator--(int) {
        const_iterator old = *this;
        --(*this);
        return old;
      }
      bool operator==(const const_iterator& rhs) const {
        return current==rhs.current;
      }
      bool operator!=(const const_iterator& rhs) const {
        return !(*this==rhs);
      }
    protected:
      node* current;
      t& retrive() const { return current->data;}
      const_iterator(node *p) : current(p){}
      friend class list<t>;
  };
  class iterator : public const_iterator {
    public:
      iterator() {}
      t& operator*() {return const_iterator::retrive();}
      iterator& operator++() {
        this->current=this->current->next;
        return *this;
      }
      iterator operator++(int) {
        iterator old = *this;
        ++(*this);
        return old;
      }
      iterator& operator--() {
        this->current=this->current->prev;
        return *this;
      }
      iterator operator--(int) {
        iterator old = *this;
        --(*this);
        return old;
      }
    private:
      iterator(node *p) : const_iterator{p} {}
      friend class list<t>;
  };
  list () {init();}
  ~list () {
    clear();
    delete head;
    delete tail;
  }
  list(const list & l) {
    init();
    for(auto &x:l) push_back(x);
  }
  list & operator= (const list &l) {
    list copy = l;
    std::swap(*this,copy);
    return *this;
  }
  list(list&&l) : size_(l.size_), head(l.head), tail(l.tail) {
    l.size_ = 0;
    l.head = nullptr;
    l.trail = nullptr;
  }
  list & operator=(list&& l) {
    swap(size_,l.size_);
    swap(head, l.head);
    swap(tail,l.tail);
    return *this;
  }
  iterator begin() { return iterator(head->next);}
  const_iterator begin() const { return const_iterator(head->next);}
  iterator end() { return iterator(tail);}
  const_iterator end() const { return const_iterator(tail);}
  int size() {return size_;}
  bool empty() { return size()==0;}
  void clear(){while(!empty()) pop_front();}
  t& front() { return *begin(); }
  const t& front() const { return *begin(); }
  t& back() {return *--end();}
  const t& back() const {return *--end();}
  void push_front( const t&x) { insert(begin(),x); }
  void push_front( t&&x) { insert(begin(),std::move(x)); }
  void push_back(const t&x) {insert(end(),x);}
  void push_back(t&&x) {insert(end(),std::move(x));}
  void pop_front() {
    erase(begin());
  }
  void pop_back() {
    erase(--end());
  }
  iterator insert( iterator itr, const t& x) {
    node *p = itr.current;
    ++size_;
    return iterator(p->prev=p->prev->next=new node{x,p->prev,p});
  }
  iterator insert( iterator itr, t&& x) {
    node *p = itr.current;
    ++size_;
    return iterator(p->prev=p->prev->next=new node{std::move(x),p->prev,p});
  }
  iterator erase(iterator itr) {
    node *p = itr.current;
    iterator ret_val(p->next);
    p->prev->next=p->next;
    p->next->prev=p->prev;
    delete p;
    --size_;
    return ret_val;
  }
  iterator erase(iterator from, iterator to) {
    for(iterator itr =from; itr!= to;) itr = erase(itr);
    return to;
  }
};
