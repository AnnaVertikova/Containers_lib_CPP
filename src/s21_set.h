#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <cstdarg>
#include <iostream>
#include <limits>

#include "s21_set_node.h"

namespace s21 {

template <typename K>
class Set {
 public:
  //  ============== Set Member type ============== //

  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 protected:
  SetNode<K> *root;
  size_type setSize;

 public:
  class SetIterator {
   public:
    SetNode<K> *itCurrent_;
    SetNode<K> *itParent_;

    SetIterator() : itCurrent_(nullptr), itParent_(nullptr) {}
    SetIterator(SetNode<K> *itCurrent, SetNode<K> *itParent)
        : itCurrent_(itCurrent), itParent_(itParent) {}
    explicit SetIterator(SetNode<K> *other)
        : itCurrent_(other), itParent_(other->pParent_) {}

    SetIterator &operator++();
    SetIterator &operator--();
    reference operator*();
    bool operator!=(const SetIterator &other) {
      return itCurrent_ != other.itCurrent_;
    }
    bool operator==(const SetIterator &other) {
      return itCurrent_ == other.itCurrent_;
    }

   private:
    SetIterator findMaxIt();
    SetIterator findMinIt();
    SetIterator getRootIt();
  };

  class SetConstIterator : public SetIterator {
   public:
    SetConstIterator() : SetIterator() {}
    explicit SetConstIterator(SetNode<K> *other) : SetIterator(other) {}
  };

  using iterator = SetIterator;
  using const_iterator = SetConstIterator;
  using pair_it_bool_type = std::pair<iterator, bool>;

  //  ============== Set Member functions ============== //

  Set();
  explicit Set(std::initializer_list<value_type> const &items);
  Set(const Set &m);
  Set(Set &&m);
  ~Set();
  Set<K> &operator=(const Set &m);
  Set<K> &operator=(Set &&m);

  //  =============== Set Iterators =============== //

  iterator begin();
  iterator end();

  //  =============== Set Capacity =============== //

  bool empty();
  size_type size();
  size_type max_size();

  //  =============== Set Modifiers =============== //

  void clear();
  pair_it_bool_type insert(const_reference value);
  void erase(iterator pos);
  void swap(Set &other);
  void merge(Set &other);

  //  =============== Set Lookup ================== //

  iterator find(const K &key);
  bool contains(const K &key);

  //  =============== Set Bonus Task =============== //

  template <typename... Args>
  pair_it_bool_type emplace(Args &&...args);

  //  ============== Set additional functions ============== //

 protected:
  void freeNode(SetNode<K> *node);
  void deleteContainer(SetNode<K> *node);
  void copyNode(SetNode<K> *node);
  SetNode<K> *findNodeAndParent(const K &key);
  void rotateLeft(SetNode<K> *&node);
  void rotateRight(SetNode<K> *&node);
  int getBalanceFactor(SetNode<K> *node);
  int getHeight(SetNode<K> *node);
  void fixHeight(SetNode<K> *node);
  void balanceNode(SetNode<K> *node);
  SetNode<K> *findMin();
  SetNode<K> *findMax();
  SetNode<K> *internalInsert(const_reference newValue);
  void internalRemove(const_reference remValue);
  int insertOrAssign = 0;
};
}  // namespace s21

#include "s21_set.inl"
#endif  //  SRC_S21_SET_H_
