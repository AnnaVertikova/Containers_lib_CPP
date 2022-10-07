#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <iostream>
#include <limits>

#include "s21_base_va.h"

namespace s21 {
template <typename T, size_t N>
class Array : public BaseForVA<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

 public:
  Array() : BaseForVA<T>(N) {}
  explicit Array(std::initializer_list<value_type> const &items)
      : BaseForVA<T>(items) {}

  void fill(const_reference value);
};
}  // namespace s21

#include "s21_array.inl"

#endif  // SRC_S21_ARRAY_H_
