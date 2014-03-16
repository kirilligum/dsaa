#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <fstream>
#include <map>
#include <queue>
#include <ctime>

using namespace std;

map<string,vector<string>> compute_djacent_words(const vector<string> & words) {
  map<string,vector<string>> adj_words;
  map<int,vector<string>> by_length;
  for(auto w:words) ///> sort by length
    by_length[w.size()].push_back(w);
  for(auto fixed: by_length) {
    map<string,vector<string>> reps;
    for(auto w:fixed){
      for(int i=0; fixed.size();++i){
        string rep = w;
        rep.erase(i,1);
        reps[rep].push_back(w);
      }
    }
  return adj_words;
}

int main(int argc, char const *argv[]) {
  clock_t start, end;
  ifstream fin("dict.txt");
  vector<string> words;
  copy(istream_iterator<string>(fin),istream_iterator<string>(),back_inserter(words));
  //std::copy(std::begin(words), std::end(words),std::ostream_iterator<string>(std::cout," ")); std::cout << std::endl;
  cout << "# of words is " << words.size() << endl;
  map<string,vector<string>> adjacent_words;

  start = clock();
  adjacent_words = compute_djacent_words(words);
  end = clock();
  cout << "elapsed time Fast: " << double(end-start)/CLOCKS_PER_SEC << endl;

  //print_high_changeables(adjacent_words,15);

  return 0;
}
