#include <iostream>

class TreapSet {
  struct Node {
    Node(long long x1, long long y1) {
      x = x1;
      y = y1;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
    }

    long long x;
    long long y;
    Node* parent;
    Node* left;
    Node* right;
  };

 public:
  TreapSet() : root_(nullptr) {}

  ~TreapSet() { Clear(root_); }

  void CalcParentMin(Node* node) {
    node->parent = parent_;
    parent_->right = node;
    parent_ = node;
  }

  void CalcParentMax(Node* node, long long value) {
    Node* cp = parent_;
    while ((cp != nullptr) && (cp->y > value)) {
      cp = cp->parent;
    }
    if (cp == nullptr) {
      node->parent = nullptr;
      root_->parent = node;
      node->left = root_;
      root_ = node;
    } else {
      Node* right = cp->right;
      right->parent = node;
      node->parent = cp;
      node->left = right;
      cp->right = node;
    }
    parent_ = node;
  }

  void Insert(long long value, long long y) {
    Node* node = new Node(value, y);
    if (root_ == nullptr) {
      node->parent = nullptr;
      root_ = node;
      parent_ = node;
    } else {
      if (parent_->y < y) {
        CalcParentMin(node);
      } else {
        CalcParentMax(node, y);
      }
    }
  }

  void DisplayTree() { return DisplayTree(root_); }

 private:
  std::pair<Node*, Node*> Split(Node* node, long long key) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key >= node->x) {
      std::pair<TreapSet::Node*, TreapSet::Node*> p = Split(node->right, key);
      TreapSet::Node* left = p.first;
      TreapSet::Node* right = p.second;
      node->right = left;
      return {node, right};
    }
    std::pair<TreapSet::Node*, TreapSet::Node*> p = Split(node->left, key);
    TreapSet::Node* left = p.first;
    TreapSet::Node* right = p.second;
    node->left = right;
    return {left, node};
  }

  Node* Merge(Node* first, Node* second) {
    if (first == nullptr) {
      return second;
    }
    if (second == nullptr) {
      return first;
    }
    if (first->y <= second->y) {
      first->right = Merge(first->right, second);
      first->right->parent = first;
      return first;
    }
    second->left = Merge(first, second->left);
    second->left->parent = second;
    return second;
  }

  static long long GetParent(Node* node) {
    if (node->parent == nullptr) {
      return 0;
    }
    return node->parent->x;
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  void DisplayTree(Node* node) {
    if (node != nullptr) {
      DisplayTree(node->left);
      long long left = 0;
      long long right = 0;
      long long parent = GetParent(node);
      if (node->left != nullptr) {
        left = node->left->x;
      }
      if (node->right != nullptr) {
        right = node->right->x;
      }
      std::cout << parent << ' ' << left << " " << right << '\n';
      DisplayTree(node->right);
    }
  }

  Node* root_;
  Node* parent_{nullptr};
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  TreapSet* treap = new TreapSet();
  long long n;
  std::cin >> n;
  long long x, y;
  for (long long i = 0; i < n; ++i) {
    std::cin >> x >> y;
    treap->Insert(i + 1, y);
  }
  std::cout << "YES" << std::endl;
  treap->DisplayTree();
  delete treap;
}
