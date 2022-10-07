#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <iostream>
#include <limits>

#include "s21_base_lsq.h"

namespace s21 {
template <typename T>
class Queue : public BaseForLSQ<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue();
  explicit Queue(std::initializer_list<value_type> const &items);

  const_reference front();

  void pop();
  template <typename... Args>
  void emplace_back(Args &&...args);
};
}  // namespace s21

#include "s21_queue.inl"

#endif  // SRC_S21_QUEUE_H_
