#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <iostream>
#include <limits>

#include "s21_base_lsq.h"

namespace s21 {
template <typename T>
class List : public BaseForLSQ<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class ListIterator {
   public:
    ListIterator() : pPos_(nullptr), pPosPrev_(nullptr) {}
    explicit ListIterator(BaseNode<T> *node)
        : pPos_(node), pPosPrev_(node->pPrev_) {}
    reference operator*();
    ListIterator &operator++();
    ListIterator &operator--();
    bool operator==(const ListIterator &it);
    bool operator!=(const ListIterator &it);
    BaseNode<T> *pPos_;
    BaseNode<T> *pPosPrev_;
  };
  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator() {}
    explicit ListConstIterator(BaseNode<T> *node) : ListIterator(node) {}
    explicit ListConstIterator(const List<T> &l) : ListIterator(l) {}
  };
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  List();
  explicit List(size_type n);
  explicit List(std::initializer_list<value_type> const &items);

  const_reference front();

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);
};
}  // namespace s21

#include "s21_list.inl"

#endif  // SRC_S21_LIST_H_
