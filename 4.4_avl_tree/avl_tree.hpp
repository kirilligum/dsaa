#pragma once

template<typename c> ///> c for comparable
class avl_tree {
public:
  avl_tree () {}
private: 
  struct avl_node {
    c element;
    avl_node *left;
    avl_node *right;
    int height;
    avl_node(const c & e, avl_node *l, avl_node *r, int h=0) 
      : element(e), left(l), right(r), height(h) {}
    avl_node(c && e, avl_node *l, avl_node *r, int h=0) 
      : element(std::move(e)), left(l), right(r), height(h) {}
  };
  avl_node *root;
  int height( avl_tree *t) const {
    return t==nullptr ? -1 : t->height;
  }
  void insert(const c& x, avl_tree*& t) {
    if(t==nullptr) {
      t = new avl_node(x,nullptr,nullptr);
    } else if (x<t->element) {
      insert(x,t->left);
    } else if (x>t->element) {
      insert(x,t->right);
    }
    balance(t);
  }
  static const int allowed_imbalance = 1;
  void balance(avl_tree * & t) {
    if(t==nullptr) return;
    if(height(t->left)-height(t->right)>allowed_imbalance) {
      if(height(t->left->left)>=height(t->left->right))
        rotate_with_left_child(t);
      else
        double_with_left_child(t);
    } else if(height(t->right)-height(t->left)>allowed_imbalance) {
      if(height(t->right->right)>=height(t->right->left)) 
        rotate_with_right_child(t);
      else 
        double_with_right_child(t);
    }
    t->height = max(height(t->left),height(t->right))+1;
  }
  void rotate_with_left_child(avl_node * & k2) {
    avl_node * k1 = k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k2->height = max(height(k2->left),height(k2->right))+1;
    k1->height = max(height(k1->left),k2->height) +1;
    k2=k1;
  }
  void rotate_with_right_child(avl_node * & k1) {
    avl_node * k2 = k1->right;
    k1->right=k2->left;
    k2->left=k1;
    k1->height = max(height(k1->left),height(k1->right))+1;
    k2->height = max(height(k2->left),k1->height) +1;
    k1=k2;
  }
  void double_with_left_child(avl_tree * & k3) {
    rotate_with_right_child(k3->left);
    rotate_with_left_child(k3);
  }
  void double_with_right_child(avl_tree * & k1) {
    rotate_with_left_child(k1->right);
    rotate_with_right_child(k1);
  }
};
