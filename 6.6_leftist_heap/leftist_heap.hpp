#pragma once

class UnderflowException{};

template <
  typename o
> class leftist_heap {
private: 
  struct node {
    o element;
    node *left;
    node *right;
    int npl;
    node(const o& e,node* lt = nullptr, node *rt = nullptr, int np = 0)
      : element{e}, left{lt}, right{rt}, npl{np} {}
  };
public:
  leftist_heap (): root{nullptr} {}
  leftist_heap (const node & rhs) : root{nullptr} {
    root = clone(rhs.root);
  }
  leftist_heap & operator=(const leftist_heap& rhs) {
    leftist_heap copy = rhs;
    std::swap(*this, copy);
    return *this;
  }
  ~leftist_heap() {
    make_empty();
  }
  bool is_empty() const {return root == nullptr;}
  const o & find_min() const {
    if(is_empty()) throw UnderflowException{};
    return root->element;
  }
  void insert( const o& x) {
    root = merge(new node{std::move(x)},root);
  }
  void delete_min() {
    if(root==nullptr) throw UnderflowException();
    node * old = root;
    root = merge(root->left, root->right);
    delete old;
  }
  void delete_min(o& x) {
    x = find_min();
    delete_min();
  }
  void make_empty() {
    reclaim_memory(root);
    root = nullptr;
  }
  void merge( leftist_heap & rhs) {
    if(this == &rhs) return;
    root = merge(root,rhs.root);
    rhs.root = nullptr;
  }
private: 
  node *root;
  node* merge(node* h1, node* h2) {
    if(h1==nullptr) return h2;
    if(h2==nullptr) return h1;
    if(h1->element < h2->element) return merge1(h1,h2);
    else return merge(h2,h1);
  }
  node* merge1(node* h1, node* h2) {
    if(h1->left == nullptr) h1->left = h2;
    else {
      h1->right = merge(h1->right,h2);
      if(h1->left->npl < h1->right->npl) swap_children(h1);
      h1->npl = h1->right->npl+1;
    }
    return h1;
  }
  void swap_children(node *t) {
    node* tmp = t->left;
    t->left = t->right;
    t->right = tmp;
  }
  void reclaim_memory (node * t) {
    if(t!=nullptr) {
      reclaim_memory(t->left);
      reclaim_memory(t->right);
      delete t;
    }
  }
};
