#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <cstdarg>
#include <iostream>
#include <limits>

#include "s21_set.h"

namespace s21 {

template <typename K>
class MultiSet : public Set<K> {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename Set<K>::SetIterator;
  using const_iterator = typename Set<K>::SetConstIterator;
  using pair_iterator = std::pair<iterator, iterator>;
  using pair_it_bool_type = std::pair<iterator, bool>;

  //  ============== MultiSet Member functions ============== //

  MultiSet() : Set<K>() {}
  explicit MultiSet(std::initializer_list<value_type> const &items);

  //  =============== MultiSet Modifiers =============== //

  iterator insert(const_reference value);
  void merge(MultiSet &other);  // splices sets

  //  =============== MultiSet Lookup ================== //

  size_type count(const_reference key);
  pair_iterator equal_range(const_reference key);
  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);

  //  =============== MultiSet Bonus Task =============== //

  template <typename... Args>
  pair_it_bool_type emplace(Args &&...args);

  //  =============== MultiSet Additional =============== //

 private:
  SetNode<K> *internalInsert(const_reference newValue);
};
}  // namespace s21

#endif  //  SRC_S21_MULTISET_H_
#include "s21_multiset.inl"
