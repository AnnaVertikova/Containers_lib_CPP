#ifndef SRC_S21_BASE_VA_H_
#define SRC_S21_BASE_VA_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class BaseForVA {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

 protected:
  size_type size_;
  value_type *arr_;

 public:
  BaseForVA();
  explicit BaseForVA(size_type n);
  explicit BaseForVA(std::initializer_list<value_type> const &items);
  BaseForVA(const BaseForVA &b);
  BaseForVA(BaseForVA &&b);
  ~BaseForVA();
  BaseForVA<T> &operator=(const BaseForVA &v);
  BaseForVA<T> &operator=(BaseForVA &&b);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();  //  = iterator data()
  iterator end();
  iterator cbegin();  //  = iterator data()
  iterator cend();

  bool empty();
  size_type size();
  size_type max_size();

  void swap(BaseForVA &other);

  void print();
  void reset();
};
}  // namespace s21

#include "s21_base_va.inl"

#endif  // SRC_S21_BASE_VA_H_
