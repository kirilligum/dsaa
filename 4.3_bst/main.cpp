#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "bst.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  bst<int> tree;
  cout << tree.is_empty() << endl;
  tree.insert(2);
  tree.insert(0);
  tree.insert(4);
  tree.insert(2);
  tree.insert(7);
  tree.insert(12);
  tree.insert(-2);
  tree.print(); cout << endl;
  cout << tree.contains(2) << endl;
  cout << "min " << tree.find_min() << endl;
  cout << "max " << tree.find_max() << endl;
  tree.remove(12);
  cout << "max " << tree.find_max() << endl;
  cout << " is_empty :  " << tree.is_empty() << endl;
  tree.print(); cout << endl;
  tree.clear();
  cout << " is_empty :  " << tree.is_empty() << endl;
  return 0;
}
