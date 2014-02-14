#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

template <class T>
void remove_every_other_item(vector<int> &v) {
  auto it=v.begin();
  it++;
  while(it!=v.end()) {
    it=v.erase(it);
    if(it!=v.end()) it++;
  }
}

int main(int argc, char const *argv[]) {
  vector<int> v(10);
  iota(begin(v),end(v),0);
  copy(begin(v),end(v),ostream_iterator<int>(cout," "));cout << endl;
  remove_every_other_item<int>(v);
  copy(begin(v),end(v),ostream_iterator<int>(cout," "));cout << endl;
  return 0;
}
