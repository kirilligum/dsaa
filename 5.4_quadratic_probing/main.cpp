#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "quadratic_probing.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << " hi \n";
  quadratic_probing<int> qb;
  qb.insert(5);
  qb.insert(6);
  qb.remove(6);
  return 0;
}
