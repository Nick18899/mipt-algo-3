#include <iostream>

#include <cmath>

#include <string>

class AVLTree {
 public:
  struct Node {
    Node* left{nullptr};
    Node* right{nullptr};
    std::pair<long long, std::string> value;
    unsigned char height{0};
  };

  AVLTree() : root_(nullptr) {}

  void Insert(long long value, std::string sec) {
    root_ = Insert(root_, value, sec);
  }

  ~AVLTree() { Clear(root_); }

  long long Height() { return (long long)root_->height; }

  void Clear() {
    Clear(root_);
    root_ = nullptr;
  }

  std::string FindValueByKey(long long value) {
    return FindValueByKey(root_, value);
  }

  bool BFindByValue(long long value) { return BFindByValue(root_, value); }

  void Erase(long long value) { root_ = Erase(root_, value); }

 private:
  static Node* Erase(Node* node, long long value) {
    if (node == nullptr) {
      return node;
    }
    if (node->value.first == value) {
      Node* left = node->left;
      Node* right = node->right;
      delete node;
      if (right == nullptr) {
        return FixBalance(left);
      }
      Node* min = FindMin(right);
      min->right = UnlinkMin(right);
      min->left = left;
      return FixBalance(min);
    }
    if (value > node->value.first) {
      node->right = Erase(node->right, value);
    } else {
      node->left = Erase(node->left, value);
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

  static bool BFindByValue(Node* node, long long value) {
    if (node == nullptr) {
      std::cout << "false";
      return false;
    }
    if (node->value.first == value) {
      return true;
    }
    if (value < node->value.first) {
      return BFindByValue(node->left, value);
    }
    return BFindByValue(node->right, value);
  }

  static std::string FindValueByKey(Node* node, long long value) {
    if (node == nullptr) {
      return "-1";
    }
    if (node->value.first == value) {
      return node->value.second;
    }
    if (value < node->value.first) {
      return FindValueByKey(node->left, value);
    }
    return FindValueByKey(node->right, value);
  }

  static void Clear(Node* node) {
    if (node != nullptr) {
      if (node->left != nullptr) {
        Clear(node->left);
      }
      if (node->right != nullptr) {
        Clear(node->right);
      }
      delete node;
    }
  }

  static Node* Insert(Node* node, long long value, std::string sec) {
    if (node == nullptr) {
      Node* new_node = new Node;
      new_node->value.first = value;
      new_node->value.second = sec;
      return new_node;
    }
    if (value <= node->value.first) {
      node->left = Insert(node->left, value, sec);
    } else {
      node->right = Insert(node->right, value, sec);
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

long long StringToNumber(std::string& s, const long long* arr) {
  long long hash_code = 0;
  for (long long i = 0; i < (long long)s.size(); ++i) {
    hash_code = (hash_code + (s[i] - 'a' + 1) * arr[i]) % (1000000000 + 7);
  }
  return hash_code;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long* arr = new long long[1000000];
  long long cnst = 29;
  arr[0] = 1;
  for (long long i = 1; i < 1000000; ++i) {
    arr[i] = (arr[i - 1] * cnst) % (1000000000 + 7);
  }
  AVLTree avl1;
  AVLTree avl2;
  long long n, q;
  std::cin >> n;
  std::string x, y;
  for (int i = 0; i < n; ++i) {
    std::cin >> x >> y;
    avl1.Insert(StringToNumber(x, arr), y);
    avl2.Insert(StringToNumber(y, arr), x);
  }
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::cin >> x;
    long long ind = StringToNumber(x, arr);
    std::string res = avl1.FindValueByKey(ind);
    if (res != "-1") {
      std::cout << res << std::endl;
    } else {
      std::cout << avl2.FindValueByKey(ind) << std::endl;
    }
  }
  delete[] arr;
}
