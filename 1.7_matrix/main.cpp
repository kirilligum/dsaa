#include <iostream>

#include "matrix.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "hi\n";
  matrix<int> m(3,4);
  cout << m[2][3] << endl;
  m[2][3]=1;
  cout << m[2][3] << endl;
  return 0;
}
