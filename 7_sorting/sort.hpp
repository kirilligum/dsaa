#pragma once

#include <vector>
using namespace std;

template < typename t >
void insertion_sort(vector<t> &a,int left, int right) {
  for (size_t i = left; i <= right; ++i) {
    auto tmp = move(a[i]);
    int j;
    for(j=i;j>0&&tmp<a[j-1];--j) {
      a[j]=move(a[j-1]);
    }
    a[j]=move(tmp);
  }
}
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

template <
  typename t
> void shell_sort(vector<t> &a) {
  for(int gap = a.size()/2; gap > 0; gap/=2) {
    for(int i=gap; i<a.size(); ++i) {
      auto tmp = move(a[i]);
      int j = i;
      for(;j>=gap&&tmp<a[j-gap];j-=gap) {
        a[j]=move(a[j-gap]);
      }
      a[j]=move(tmp);
    }
  }
}

int left_child(int i) { return 2*i+1;}
template <
  typename t
> void perc_down(vector<t> &a , int i, int n) {
  int child;
  t tmp;
  for(tmp=move(a[i]);left_child(i)<n;i=child){
    child=left_child(i);
    if(child!=n-1 && a[child]<a[child+1]) ++child;
    if(tmp<a[child])
      a[i]=move(a[child]);
    else
      break;
  }
  a[i]=move(tmp);
}
template <
  typename t
> void heap_sort(vector<t> &a) {
  for(int i=a.size()/2-1;i>=0;--i)
    perc_down(a,i,a.size());
  for(int i=a.size()-1;i>0;--i) {
    swap(a[0],a[i]);
    perc_down(a,0,i);
  }
}

template <
  typename t
> void merge(vector<t> &a, vector<t>& ta, int left_pos,int right_pos, int right_end) {
  int left_end = right_pos-1;
  int tmp_pos = left_pos;
  int num_el = right_end - left_pos +1;
  while(left_pos<=left_end && right_pos<=right_end)
    if(a[left_pos]<=a[right_pos])
      ta[tmp_pos++]=move(a[left_pos++]);
    else
      ta[tmp_pos++]=move(a[right_pos++]);
  while(left_pos<=left_end)
    ta[tmp_pos++]=move(a[left_pos++]);
  while(right_pos<=right_end)
    ta[tmp_pos++]=move(a[right_pos++]);
  for(int i=0;i<=num_el;++i,--right_end) 
    a[right_end]=move(ta[right_end]);
}
template <
  typename t
> void merge_sort(vector<t> &a, vector<t>&ta, int left, int right) {
  if(left<right) {
    int center = (left+right)/2;
    merge_sort(a,ta,left,center);
    merge_sort(a,ta,center+1,right);
    merge(a,ta,left,center+1,right);
  }
}
template <
  typename t
> void merge_sort(vector<t> &a) {
  auto ta = a;
  merge_sort(a,ta,0, a.size()-1);
}

template <
  typename t
> void simple_quick_sort(vector<t> &a) {
  int pivot = a.size()/2;
  vector<t> smaller,larger,same;
  for (size_t i = 0; i < a.size(); ++i) {
    if(a[i]<a[pivot]) smaller.push_back(a[i]);
    else if(a[i]>a[pivot]) larger.push_back(a[i]);
    else same.push_back(a[i]);
  }
  if(smaller.size()>0) simple_quick_sort(smaller);
  if(larger.size()>0) simple_quick_sort(larger);
  move(begin(smaller),end(smaller),begin(a));
  move(begin(same),end(same),begin(a)+smaller.size());
  move(begin(larger),end(larger),begin(a)+smaller.size()+same.size());
}

template< typename t > t & median3(vector<t>&a, int left, int right) {
  int center = (left+right)/2;
  if(a[left]>a[center]) swap(a[left],a[center]);
  if(a[center]>a[right]) swap(a[center],a[right]);
  if(a[left]>a[center]) swap(a[left],a[center]);
  swap(a[center],a[right-1]);
  return a[right-1];
}
template <
  typename t
> void quick_sort(vector<t> &a, int left, int right) {
  if(right-left>=10){
    const t& pivot= median3(a,left,right);
    int i=left,j=right-1;
    for(;;) {
      while(a[++i]<pivot) {}
      while(pivot<a[--j]) {}
      if(i<j)
        swap(a[i],a[j]);
      else
        break;
    }
    swap(a[i],a[right-1]);
    quick_sort(a,left,i-1);
    quick_sort(a,i+1,right);
  } else {
    insertion_sort(a,left,right);
  }
}
template <
  typename t
> void quick_sort(vector<t> &a) {
  quick_sort(a, 0, a.size()-1);
}
