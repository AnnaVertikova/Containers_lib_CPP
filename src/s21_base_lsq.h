#ifndef SRC_S21_BASE_LSQ_H_
#define SRC_S21_BASE_LSQ_H_

#include <iostream>
#include <limits>

#include "s21_node.h"

namespace s21 {
template <typename T>
class BaseForLSQ : public BaseNode<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 protected:
  size_type size_;
  BaseNode<T> *head_;
  BaseNode<T> *tail_;

 public:
  BaseForLSQ();
  explicit BaseForLSQ(std::initializer_list<value_type> const &items);
  BaseForLSQ(const BaseForLSQ &bs);
  BaseForLSQ(BaseForLSQ &&bs);
  ~BaseForLSQ();
  BaseForLSQ<T> &operator=(const BaseForLSQ &bs);
  BaseForLSQ<T> &operator=(BaseForLSQ &&bs);

  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(BaseForLSQ &bs);

  void print();
};
}  // namespace s21

#include "s21_base_lsq.inl"

#endif  // SRC_S21_BASE_LSQ_H_
