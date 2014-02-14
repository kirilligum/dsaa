#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "cuckoo_hash_table.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << " hi \n";
  cuckoo_hash_table<string,string_hash_family<3>> cht;
  cht.insert("asd");
  return 0;
}
