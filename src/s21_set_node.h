#ifndef SRC_S21_SET_NODE_H_
#define SRC_S21_SET_NODE_H_

namespace s21 {

template <typename K>
class Set;

template <typename K>
class MultiSet;

template <typename K>
class SetNode {
 private:
  K value_;
  SetNode *pLeft_;
  SetNode *pRight_;
  SetNode *pParent_;
  int height_;

 public:
  explicit SetNode(K value = K(), SetNode *pLeft = nullptr,
                   SetNode *pRight = nullptr, SetNode *pParent = nullptr,
                   int height = 1)

      : value_(value),
        pLeft_(pLeft),
        pRight_(pRight),
        pParent_(pParent),
        height_(height) {}

  const K &getValue() { return value_; }

  friend class Set<K>;
  friend class MultiSet<K>;
};
}  // namespace s21

#endif  //  SRC_S21_SET_NODE_H_
