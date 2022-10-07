#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <iostream>
#include <limits>

#include "s21_base_va.h"

namespace s21 {
template <typename T>
class Vector : public BaseForVA<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

 private:
  size_type capacity_;

 public:
  Vector();
  explicit Vector(size_type n);
  explicit Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector();
  Vector<T> &operator=(const Vector &v);
  Vector<T> &operator=(Vector &&v);

  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  void realloc(size_type size);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
};
}  // namespace s21

#include "s21_vector.inl"

#endif  // SRC_S21_VECTOR_H_
