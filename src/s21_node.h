#ifndef SRC_S21_NODE_H_
#define SRC_S21_NODE_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class BaseNode {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  value_type data_;
  BaseNode *pNext_;
  BaseNode *pPrev_;
  BaseNode(value_type data = value_type(), BaseNode *pNext = nullptr,
           BaseNode *pPrev = nullptr)
      : data_(data), pNext_(pNext), pPrev_(pPrev) {}
};
}  // namespace s21

#endif  // SRC_S21_NODE_H_
