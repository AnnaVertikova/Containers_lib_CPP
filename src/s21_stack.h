#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <iostream>
#include <limits>

#include "s21_base_lsq.h"

namespace s21 {
template <typename T>
class Stack : public BaseForLSQ<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack();
  explicit Stack(std::initializer_list<value_type> const &items);

  const_reference top();

  template <typename... Args>
  void emplace_front(Args &&...args);
};
}  // namespace s21

#include "s21_stack.inl"

#endif  // SRC_S21_STACK_H_
