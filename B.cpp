#include <iostream>

#include <vector>

#include <cmath>

class AVLTree {
 public:
  struct Node {
    Node* left{nullptr};
    Node* right{nullptr};
    long long value;
    unsigned char height{0};
  };

  AVLTree() : root_(nullptr) {}

  void Insert(long long value) { root_ = Insert(root_, value); }

  ~AVLTree() { Clear(root_); }

  void Clear() {
    Clear(root_);
    root_ = nullptr;
  }

  long long Find(long long value) {
    long long res = (long long)pow(10, 9) + 1;
    return Find(root_, value, res);
  }

  bool Find1(long long value) { return Find1(root_, value); }

  void Erase(long long value) { root_ = Erase(root_, value); }

 private:
  static Node* Erase(Node* node, long long value) {
    if (node == nullptr) {
      return node;
    }
    if (node->value == value) {
      if (node->right == nullptr) {
        Node* temp = node->left;
        delete node;
        return FixBalance(temp);
      }
      Node* right_min = FindMin(node->right);
      node->right = UnlinkMin(node->right);
      right_min->left = node->left;
      right_min->right = node->right;
      delete node;
      return FixBalance(right_min);
    }
    if (value < node->value) {
      node->left = Erase(node->left, value);
    } else {
      node->right = Erase(node->right, value);
    }
    return FixBalance(node);
  }

  static Node* FindMin(Node* node) {
    if (node->left == nullptr) {
      return node;
    }
    return FindMin(node->left);
  }

  static Node* UnlinkMin(Node* node) {
    if (node->left == nullptr) {
      return node->right;
    }
    node->left = UnlinkMin(node->left);
    return FixBalance(node);
  }

  static bool Find1(Node* node, long long value) {
    if (node == nullptr) {
      return false;
    }
    if (node->value == value) {
      return true;
    }
    if (value < node->value) {
      return Find1(node->left, value);
    }
    return Find1(node->right, value);
  }

  static long long Find(Node* node, long long value, long long res) {
    if (node == nullptr && res == (long long)pow(10, 9) + 1) {
      return -1;
    }
    if (node == nullptr) {
      return res;
    }
    if ((node->value >= value) && (res > node->value)) {
      res = node->value;
    }
    if (value < node->value) {
      return Find(node->left, value, res);
    }
    return Find(node->right, value, res);
  }

  static void Clear(Node* node) {
    if (node->left != nullptr) {
      Clear(node->left);
    }
    if (node->right != nullptr) {
      Clear(node->right);
    }
    delete node;
  }

  static Node* Insert(Node* node, long long value) {
    if (node == nullptr) {
      Node* new_node = new Node;
      new_node->value = value;
      return new_node;
    }
    if (value <= node->value) {
      node->left = Insert(node->left, value);
    } else {
      node->right = Insert(node->right, value);
    }
    return FixBalance(node);
  }

  static long long Height(Node* node) {
    return node == nullptr ? 0 : static_cast<long long>(node->height);
  }

  static long long BalanceFactor(Node* node) {
    return node == nullptr ? 0 : Height(node->right) - Height(node->left);
  }

  static void CalcHeight(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->height = std::max(Height(node->left), Height(node->right)) + 1;
  }

  static Node* RightRotate(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    CalcHeight(p);
    CalcHeight(q);
    return q;
  }

  static Node* LeftRotate(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    CalcHeight(q);
    CalcHeight(p);
    return p;
  }

  static Node* FixBalance(Node* node) {
    CalcHeight(node);
    if (BalanceFactor(node) == 2) {
      if (BalanceFactor(node->right) == -1) {
        node->right = RightRotate(node->right);
      }
      return LeftRotate(node);
    }
    if (BalanceFactor(node) == -2) {
      if (BalanceFactor(node->left) == 1) {
        node->left = LeftRotate(node->left);
      }
      return RightRotate(node);
    }
    return node;
  }

  Node* root_;
};

long long InputTreatment(const char* cmd, AVLTree*& treap, char last_op,
                         long long last_v) {
  long long inserting_value, lval;
  std::cin >> inserting_value;
  lval = -1;
  switch (cmd[0]) {
    case '+':
      if (last_op == '?') {
        inserting_value = (last_v + inserting_value) % (long long)pow(10, 9);
        if (!(treap->Find1(inserting_value))) {
          treap->Insert(inserting_value);
        }
      } else {
        if (!(treap->Find1(inserting_value))) {
          treap->Insert(inserting_value);
        }
      }
      break;
    case '?':
      lval = treap->Find(inserting_value);
      std::cout << lval << std::endl;
  }
  return lval;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  AVLTree* avl = new AVLTree();
  long long n;
  std::cin >> n;
  char str[3];
  char last_op = 'e';
  long long last_value = -1;
  for (long long i = 0; i < n; ++i) {
    std::cin >> str;
    last_value = InputTreatment(str, avl, last_op, last_value);
    last_op = str[0];
  }
  delete avl;
}
