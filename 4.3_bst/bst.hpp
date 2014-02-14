#pragma once
#include <iostream>

using namespace std;

template <typename o>
class bst {
private: 
  struct node {
    node (const o& d = o(), node* l = nullptr, node* r = nullptr) : data(d), left(l), right (r) { }
    o data;
    node* left;
    node* right;
  };
  node* root;
  void insert(const o& x, node* &n) {
    if(n==nullptr)
      n = new node{x};
    else if (x<n->data)
      insert(x,n->left);
    else if (x>n->data)
      insert(x,n->right);
    else
      ; ///> duplicate
  }
  bool contains(const o& x, node* n) {
    if(x==n->data)
      return 1;
    else if (x<n->data)
      return contains(x,n->left);
    else if (x>n->data)
      return contains(x,n->right);
    else
      return 0;
  }
  node* find_min(node* n) const  {
    if(n==nullptr)
      return nullptr;
    if(n->left==nullptr)
      return n;
    return find_min(n->left);
  }
  node* find_max(node* n) const  {
    if(n==nullptr)
      return nullptr;
    if(n->right==nullptr)
      return n;
    return find_max(n->right);
  }
  void remove(const o& x, node* &n) {
    if (n==nullptr) return;
    if (x>n->data)
      remove(x,n->right);
    else if (x<n->data)
      remove(x,n->left);
    else if (n->left != nullptr && n->right!=nullptr) {
      n->data = find_min(n->right)->data;
      remove(n->data,n->right);
    } else {
      node* old = n;
      n = (n->left!=nullptr) ? n->left : n->right;
      delete old;
    }
  }
  void clear(node* & n) {
    if(n!=nullptr) {
      clear(n->left);
      clear(n->right);
      delete n;
    }
    n=nullptr;
  }
  void print(node* n) {
    if(n!=nullptr) { 
      cout <<"(";
      print(n->left);
      print(n->right);
      cout <<")";
      cout << n->data << "  ";
    }
  }
  node* clone(bst * n) {
    if(n==nullptr)
      return nullptr;
    else 
      return new node(n->element,clone(n->left), clone(n->right));
  }
  void make_empty(node*& n) {
    if(n!=nullptr) {
      make_empty(n->left);
      make_empty(n->right);
      delete n;
    }
    n = nullptr;
  }
public:
  bst () : root{nullptr} {}
  bst (const bst & rhs) : root{nullptr}{ root = clone(rhs.root); }
  bst (bst && rhs) : root{rhs.root} {root =nullptr;}
  ~bst() { make_empty(); }
  bst & operator=(const bst& rhs) {
    bst* copy = rhs;
    std::swap(*this,copy);
    return *this;
  }
  bst & operator=(bst && rhs) {
    std::swap(root,rhs.root);
    return *this;
  }
  bool is_empty() {return root==nullptr;}
  void make_empty() {make_empty(root);}
  void insert(const o& x) { insert(x,root); }
  bool contains(const o& x) { return contains(x,root);}
  const o& find_min() const  { return find_min(root)->data; }
  const o& find_max() const  { return find_max(root)->data; }
  void remove(const o&  x) { remove(x,root);}
  void clear() {clear(root);}
  void print() {print(root);}
};
