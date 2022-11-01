#include <cmath>
#include <iostream>

class AVLTree {
 public:
  struct Node {
    long long sum;
    Node* left{nullptr};
    Node* right{nullptr};
    long long value;
    unsigned char height{0};
  };

  AVLTree() : root_(nullptr) {}

  void Insert(long long value) { root_ = Insert(root_, value); }

  long long SumOnSegment(long long left, long long right) {
    return SumOnSegment(root_, left, right);
  }

  static long long SumForNode(Node* node) {
    return node == nullptr ? 0 : node->sum;
  }

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
      new_node->sum = value;
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
    node->sum = SumForNode(node->left) + SumForNode(node->right) + node->value;
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

  long long SumOnSegment(Node* node, long long left, long long right,
                         long long minima = kMinValue,
                         long long maxima = kMaxValue) {
    if (node == nullptr) {
      return 0;
    }
    if (node->value < left) {
      return SumOnSegment(node->right, left, right, node->value, maxima);
    }
    if (node->value > right) {
      return SumOnSegment(node->left, left, right, minima, node->value);
    }
    long long res_sum = node->value;
    if (minima >= left) {
      res_sum += SumForNode(node->left);
    } else {
      res_sum += SumOnSegment(node->left, left, right, minima, node->value);
    }
    if (maxima <= right) {
      res_sum += SumForNode(node->right);
    } else {
      res_sum += SumOnSegment(node->right, left, right, node->value, maxima);
    }
    return res_sum;
  }

  Node* root_;
  const static long long kMinValue{0};
  const static long long kMaxValue{1000000000};
};

long InputTreatment(const char* cmd, AVLTree* avl, long last_v, char last_op) {
  long inserting_value1, lval;
  std::cin >> inserting_value1;
  lval = -1;
  switch (cmd[0]) {
    case '+':
      if (last_op == '?') {
        inserting_value1 = (last_v + inserting_value1) % (int)1e9;
        if (!(avl->Find1(inserting_value1))) {
          avl->Insert(inserting_value1);
        }
      } else {
        if (!(avl->Find1(inserting_value1))) {
          avl->Insert(inserting_value1);
        }
      }
      break;
    case '?':
      long inserting_value2;
      std::cin >> inserting_value2;
      lval = avl->SumOnSegment(inserting_value1, inserting_value2);
      std::cout << lval << '\n';
      break;
    default:
      break;
  }
  return lval;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long n;
  std::cin >> n;
  char str[5];
  char last_op = 'e';
  long last_value = -1;
  long x;
  auto* st = new AVLTree();
  for (long i = 0; i < n; ++i) {
    std::cin >> str;
    x = InputTreatment(str, st, last_value, last_op);
    if (x != -1) {
      last_value = x;
    }
    last_op = str[0];
  }
  delete st;
  return 0;
}
