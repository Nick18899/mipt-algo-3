#include <iostream>

#include "random"

#include <vector>

#include <cmath>

class AVLTree {
 public:
  struct Node {
    long long count{0};
    Node* left{nullptr};
    Node* right{nullptr};
    std::pair<long long, long long> value;
    unsigned char height{0};
  };

  AVLTree() : root_(nullptr) {}

  void Insert(long long value, long long sec) {
    root_ = Insert(root_, value, sec);
  }

  ~AVLTree() { Clear(root_); }

  long long Height() { return (long long)root_->height; }

  void Clear() {
    Clear(root_);
    root_ = nullptr;
  }

  long long FindValueByKey(long long value) {
    long long res = (long long)pow(10, 9) + 1;
    return FindValueByKey(root_, value, res);
  }

  long long FindIdByValue(long long value) {
    long long res = (long long)pow(10, 9) + 1;
    return FindIdByValue(root_, value, res);
  }

  Node* OrderStat(long long k) { return KthSmallest(root_, k); }

  bool BFindByValue(long long value) { return BFindByValue(root_, value); }

  void Erase(long long value) { root_ = Erase(root_, value); }

 private:
  Node* KthSmallest(Node* root, long long k) {
    if (root == nullptr) {
      return nullptr;
    }
    long long count = root->count + 1;
    if (count == k) {
      return root;
    }
    if (count > k) {
      return KthSmallest(root->left, k);
    }
    return KthSmallest(root->right, k - count);
  }

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

  static long long FindIdByValue(Node* node, long long value, long long res) {
    if (node == nullptr) {
      return -1;
    }
    if (node->value.second == value) {
      return node->value.first;
    }
    if (value < node->value.second) {
      return FindValueByKey(node->left, value, res);
    }
    return FindValueByKey(node->right, value, res);
  }

  static long long FindValueByKey(Node* node, long long value, long long res) {
    if (node == nullptr) {
      return -1;
    }
    if (node->value.first == value) {
      return node->value.second;
    }
    if (value < node->value.first) {
      return FindValueByKey(node->left, value, res);
    }
    return FindValueByKey(node->right, value, res);
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

  static Node* Insert(Node* node, long long value, long long sec) {
    if (node == nullptr) {
      Node* new_node = new Node;
      new_node->value.first = value;
      new_node->value.second = sec;
      return new_node;
    }
    if (value <= node->value.first) {
      node->left = Insert(node->left, value, sec);
      node->count++;
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

class TreapSet {
 public:
  struct Node {
    Node(long long x, long long y)
        : count(1), x(x), y(y), left(nullptr), right(nullptr) {}
    long long count;
    long long x;
    long long y;
    Node* left;
    Node* right;
  };

  TreapSet() : root_(nullptr) {}

  ~TreapSet() { Clear(root_); }

  long long CountOf(TreapSet::Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->count;
  }

  void UpdateCount(TreapSet::Node* node) {
    node->count = CountOf(node->left) + CountOf(node->right) + 1;
  }

  void Erase(long long value) {
    if (!Find(value)) {
      return;
    }
    std::pair<TreapSet::Node*, TreapSet::Node*> p = Split(root_, value);
    TreapSet::Node* left_with_value = p.first;
    TreapSet::Node* right = p.second;
    p = Split(left_with_value, value - 1);
    TreapSet::Node* left = p.first;
    TreapSet::Node* value_tree = p.second;
    delete value_tree;
    root_ = Merge(left, right);
  }

  void Insert(long long value) {
    if (Find(value)) {
      return;
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(
        0, (long)pow(10, 9) + 1);
    long long y = dist6(rng);
    Node* node = new Node(value, y);
    std::pair<TreapSet::Node*, TreapSet::Node*> p = Split(root_, value);
    TreapSet::Node* first = p.first;
    TreapSet::Node* second = p.second;
    root_ = Merge(Merge(first, node), second);
  }

  std::pair<Node*, Node*> Find1(long long value) {
    long long res = (long long)pow(10, 9) + 1;
    return Find1(root_, value, res);
  }

  std::pair<Node*, Node*> Find2(long long value) {
    long long res = -1;
    return Find2(root_, value, res);
  }

  long long KORderStat(long long k) { return KOrderStat(root_, k); }

  bool Find(long long value) {
    return Find(nullptr, root_, value).second != nullptr;
  }

 private:
  long long KOrderStat(TreapSet::Node* node, long long k) {
    if (node == nullptr) {
      return -1;
    }
    if (k == CountOf(node->left)) {
      return node->x;
    }
    if (k < CountOf(node->left)) {
      return KOrderStat(node->left, k);
    }
    return KOrderStat(node->right, (k - CountOf(node->left) - 1));
  }

  std::pair<Node*, Node*> Find1(Node* node, long long value, long long res) {
    if (node == nullptr && res == (long long)pow(10, 9) + 1) {
      return {nullptr, nullptr};
    }
    if (node == nullptr) {
      Node* node1 = new Node(res, 0);
      return {nullptr, node1};
    }
    if ((node->x > value) && res > node->x) {
      res = node->x;
    }
    if (value < node->x) {
      return Find1(node->left, value, res);
    }
    return Find1(node->right, value, res);
  }

  std::pair<Node*, Node*> Find2(Node* node, long long value, long long res) {
    if (node == nullptr && res == -1) {
      return {nullptr, nullptr};
    }
    if (node == nullptr) {
      Node* node1 = new Node(res, 0);
      return {nullptr, node1};
    }
    if ((node->x < value) && res < node->x) {
      res = node->x;
    }
    if (value < node->x) {
      return Find2(node->left, value, res);
    }
    return Find2(node->right, value, res);
  }

  std::pair<Node*, Node*> Find(Node* parent, Node* node, long long value) {
    if (node == nullptr) {
      return {parent, node};
    }
    if (value == node->x) {
      return {parent, node};
    }
    if (value <= node->x) {
      return Find(node, node->left, value);
    }
    return Find(node, node->right, value);
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  Node* Merge(Node* first, Node* second) {
    if (first == nullptr) {
      return second;
    }
    if (second == nullptr) {
      return first;
    }
    if (first->y > second->y) {
      first->right = Merge(first->right, second);
      UpdateCount(first);
      return first;
    }
    second->left = Merge(first, second->left);
    UpdateCount(second);
    return second;
  }

  std::pair<Node*, Node*> Split(Node* node, long long key) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key >= node->x) {
      std::pair<TreapSet::Node*, TreapSet::Node*> p = Split(node->right, key);
      TreapSet::Node* left = p.first;
      TreapSet::Node* right = p.second;
      node->right = left;
      UpdateCount(node);
      return {node, right};
    }
    std::pair<TreapSet::Node*, TreapSet::Node*> p = Split(node->left, key);
    TreapSet::Node* left = p.first;
    TreapSet::Node* right = p.second;
    node->left = right;
    UpdateCount(node);
    return {left, node};
  }

  Node* root_;
};

void InputTreatment(const char* cmd, TreapSet*& treap, AVLTree*& avl,
                    long long id) {
  long long inserting_value;
  std::cin >> inserting_value;
  switch (cmd[0]) {
    case 'n': {
      auto x = treap->Find1(inserting_value).second;
      if (x != nullptr) {
        std::cout << x->x << std::endl;
      } else {
        std::cout << "none" << std::endl;
      }
      delete x;
      break;
    }
    case 'p': {
      auto x = treap->Find2(inserting_value).second;
      if (x != nullptr) {
        std::cout << x->x << std::endl;
      } else {
        std::cout << "none" << std::endl;
      }
      delete x;
      break;
    }
    case 'e':
      if (treap->Find(inserting_value)) {
        std::cout << "true" << std::endl;
      } else {
        std::cout << "false" << std::endl;
      }
      break;
    case 'd':
      treap->Erase(inserting_value);
      avl->Erase(avl->FindIdByValue(inserting_value));
      break;
    case 'i':
      avl->Insert(id, inserting_value);
      treap->Insert(inserting_value);
      break;
    case 'k':
      if (treap->KORderStat(inserting_value) != -1) {
        std::cout << treap->KORderStat(inserting_value) << std::endl;
      } else {
        std::cout << "none" << std::endl;
      }
      break;
    default:
      break;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  TreapSet* treap = new TreapSet();
  AVLTree* avl = new AVLTree();
  char str[8];
  long long i = 0;
  while (std::cin >> str) {
    InputTreatment(str, treap, avl, i);
    ++i;
  }
  delete avl;
  delete treap;
}
