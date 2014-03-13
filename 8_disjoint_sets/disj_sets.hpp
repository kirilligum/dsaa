#pragma once
#include <vector>
using namespace std;

class disj_sets {
  public:
    explicit disj_sets(int num_elements);
    int find(int x) const;
    int find(int x);
    void union_sets(int r1, int r2);
  private:
    vector<int> s;
};

disj_sets::disj_sets(int num_elements) : s{num_elements+1} {}

void disj_sets::union_sets(int r1, int r2) {
  if(s[r2]<s[r1])
    s[r1]=r2;
  else {
    if(s[r1]==s[r2])
      --s[r1];
    s[r2]=r1;
  }
}

int disj_sets::find(int x) const {
  if(s[x]<0)
    return x;
  else
    return find(s[x]);
}

int disj_sets::find(int x) {
  if(s[x]<0)
    return x;
  else 
    return s[x]=find(s[x]);
}

