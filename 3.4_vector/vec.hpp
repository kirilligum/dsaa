#pragma once
#include <utility>

using std::size_t;

template< class T>
class vec {
  public:
    explicit vec(size_t size_=0, const T & value=T()) : size_{size_}, capacity_{size_}, data{new T[capacity_]} {
      for (size_t i = 0; i < size_; ++i) {
        data[i]=value;
      }
    }
    vec(const vec &other) : size_{other.size_}, capacity_{other.capacity_},data{nullptr} {
      data = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        data[i]=other.data[i];
      }
    }
    vec &operator= (const vec &other) {
      vec tmp(other);
      std::swap(this, tmp);
      return *this;
    }
    ~vec() {
      delete[] data;
    }
    vec(vec &&other) : size_{other.size_}, capacity_{other.capacity_},data{other.data} {
      other.size_ = 0;
      other.capacity_ = 0;
      other.data=nullptr;
    }
    vec &operator= (vec &&other) {
      std::swap(size_,other.size_);
      std::swap(capacity_,other.capacity_);
      std::swap(data,other.data);
      return *this;
    }
    void resize(size_t new_size) {
      if(new_size>capacity_)
        reserve(new_size*2);
      size_ = new_size;
    }
    void reserve(size_t new_capacty) {
      if(new_capacty<size_)
        return;
      T *new_data = new T[new_capacty];
      for (size_t i = 0; i < size_; ++i) 
        new_data[i] = std::move(data[i]);
      capacity_= new_capacty;
      std::swap(data,new_data);
      delete[] new_data;
    }
    T & operator[] (int i) {
      return data[i];
    }
    const T & operator[] (int i) const {
      return data[i];
    }
    bool empty() const {
      return size_()==0;
    }
    size_t size() const {
      return size_;
    }
    size_t capacity() const {
      return capacity_;
    }
    void push_back(const T & x) {
      if(size_==capacity_)
        reserve(2*capacity_+1);
      data[size_++]=x;
    }
    void push_back(T && x) {
      if(size_==capacity_)
        reserve(2*capacity_+1);
      data[size_++]=std::move(x);
    }
    void pop_back() {
      --size_;
    }
    const T & back() const {
      return data[size_-1];
    }
    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin() {
      return &data[0];
    }
    const_iterator begin() const{
      return &data[0];
    }
    iterator end() {
      return &data[size()];
    }
    const_iterator end() const{
      return &data[size()];
    }
  private:
    T *data;
    size_t size_, capacity_;
};
