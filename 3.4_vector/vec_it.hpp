#pragma once

template<class T>
class vec_it {
  private:
    T* p;
  public:
    vec_it(T* x) : p(x) {}
    vec_it(const vec_it& it) : p(it.p) {}
    vec_it &operator++() { ++p; return *this;}
    vec_it operator++(int) { vec_it tmp(*this); operator++(); return tmp;}
    bool operator==(const vec_it& rhs) { return p==rhs.p;}
    bool operator!=(const vec_it& rhs) { return p!=rhs.p;}
    T& operator*() {return *p;}
};
