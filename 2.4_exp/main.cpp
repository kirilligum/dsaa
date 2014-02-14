#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cmath>

using namespace std;

int power(int x, int p) {
  if(p==0) return 1;
  else if (p==1) return x;
  else if (p%2==1) return power(x*x,p/2)*x;
  else if (p%2==0) return power(x*x,p/2);
  else return -1;
}

int main(int argc, char const *argv[]) {
  int x = 2, p =7;
  cout << x << "^" << p << " = " << power(x,p) << "\n"; 
  cout << pow(2,7) << endl;
  return 0;
}
