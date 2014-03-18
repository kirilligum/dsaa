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
  for(auto & fixed: by_length) {
    for(int i=0; i< fixed.first;++i){
      map<string,vector<string>> reps;
      for(auto &w:fixed.second){
        string rep = w;
        rep.erase(i,1);
        reps[rep].push_back(w);
      }
      for(auto & ws:reps){
        const vector<string> & clique = ws.second;
        if(clique.size()>=2) {
          for (size_t i = 0; i < clique.size(); ++i) {
            for (size_t j = i+1; j < clique.size(); ++j) {
              adj_words[clique[i]].push_back(clique[j]);
              adj_words[clique[j]].push_back(clique[i]);
            }
          }
        }
      }
    }
  }
  return adj_words;
}

void print_high_changeables(const map<string,vector<string>> & adjacent_words, int min_words = 15) {
  for(auto & connected : adjacent_words) {
    const vector<string> & words = connected.second;
    if(words.size()>=min_words) {
      cout << connected.first << " (" << words.size() << "):";
      for(auto & str: words) cout << "  " << str;
      cout << endl;
    }
  }
}

vector<string> chain_prevs(const map<string,string> & previous, const string & first, const string & second) {
  vector<string> result;
  auto & prev = const_cast<map<string,string>&>(previous);
  for(auto current = second; current!=""; current=prev[current])
    result.push_back(current);
  reverse(begin(result),end(result));
  return result;
}

vector<string> find_chain(const map<string,vector<string>> & adjacent_words, const string & first, const string & second) {
  map<string,string> prev_word;
  queue<string> q ;
  q.push(first);
  while(!q.empty()) {
    string current = q.front(); q.pop();
    auto itr = adjacent_words.find(current);
    if(itr!=adjacent_words.end()){
      const vector<string> & adj = itr->second;
      for(auto &str :adj) {
        if(prev_word[str]=="") {
          prev_word[str]=current;
          q.push(str);
        }
      }
    }
  }
  prev_word[first]="";
  return chain_prevs(prev_word,first,second);
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

  print_high_changeables(adjacent_words,25);

  for(;;) {
    cout << "Enter two words: ";
    string w1,w2;
    cin >> w1 >> w2;
    //w1 = "tare"; w2 = "tore";

    vector<string> path = find_chain(adjacent_words, w1, w2);
    cout << path.size() << endl;
    for(string & word: path)
      cout << word << "  ";
    cout << endl;
  }

  return 0;
}
