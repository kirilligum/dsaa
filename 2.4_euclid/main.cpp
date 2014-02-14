#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int euclid_gcd(int a, int b) {
  while(b!=0) {
    int r = a%b;
    a = b;
    b = r;
  }
  return a;
}

int main(int argc, char const *argv[]) {
  cout << " hi \n";
  int m=11*15*17, n=17*3*2;
  cout << "gcd("<< m <<","<< n <<") = "<< euclid_gcd(m,n) <<"\n";
  return 0;
}
