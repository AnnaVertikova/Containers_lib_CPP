#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <cstdarg>
#include <iostream>
#include <limits>

namespace s21 {

template <typename K, typename T>
class Map {
 public:
  //  ============== Map Member type ============== //

  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<K, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  class MapNode {
   public:
    value_type keyValue_;
    MapNode *pLeft_;
    MapNode *pRight_;
    MapNode *pParent_;
    int height_;

    explicit MapNode(value_type keyValue = value_type(),
                     MapNode *pLeft = nullptr, MapNode *pRight = nullptr,
                     MapNode *pParent = nullptr, int height = 1)

        : keyValue_(keyValue),
          pLeft_(pLeft),
          pRight_(pRight),
          pParent_(pParent),
          height_(height) {}
  };
  MapNode *root;
  size_type mapSize;

 public:
  class MapIterator {
   public:
    MapNode *itCurrent_;
    MapNode *itParent_;

    MapIterator() : itCurrent_(nullptr), itParent_(nullptr) {}
    MapIterator(MapNode *itCurrent, MapNode *itParent)
        : itCurrent_(itCurrent), itParent_(itParent) {}
    explicit MapIterator(MapNode *other)
        : itCurrent_(other), itParent_(other->pParent_) {}

    MapIterator &operator++();
    MapIterator &operator--();
    reference operator*();
    bool operator!=(const MapIterator &other) {
      return itCurrent_ != other.itCurrent_;
    }
    bool operator==(const MapIterator &other) {
      return itCurrent_ == other.itCurrent_;
    }

   private:
    MapIterator findMaxIt();
    MapIterator findMinIt();
    MapIterator getRootIt();
  };

  class MapConstIterator : public MapIterator {
   public:
    MapConstIterator() : MapIterator() {}
    explicit MapConstIterator(MapNode *other) : MapIterator(other) {}
  };
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using pair_it_bool_type = std::pair<iterator, bool>;

  //  ============== Map Member functions ============== //

  Map();
  explicit Map(std::initializer_list<value_type> const &items);
  Map(const Map &m);
  Map(Map &&m);
  ~Map();
  Map<K, T> &operator=(const Map &m);
  Map<K, T> &operator=(Map &&m);

  //  =============== Map Element access =============== //

  T &at(const K &key);
  T &operator[](const K &key);

  //  =============== Map Iterators =============== //

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  //  =============== Map Capacity =============== //

  bool empty();
  size_type size();
  size_type max_size();

  //  =============== Map Modifiers =============== //

  void clear();
  pair_it_bool_type insert(const_reference value);
  pair_it_bool_type insert(const K &key, const T &item);
  pair_it_bool_type insert_or_assign(const K &key, const T &item);
  void erase(iterator pos);
  void swap(Map &other);
  void merge(Map &other);

  //  =============== Map Lookup ================== //

  bool contains(const K &key);

  //  =============== Map Bonus Task =============== //

  template <typename... Args>
  pair_it_bool_type emplace(Args &&...args);

  //  ============== Map  additional functions ============== //

 private:
  void freeNode(MapNode *node);
  void deleteContainer(MapNode *node);
  void copyNode(MapNode *node);
  MapNode *findNodeAndParent(const K &key);
  void rotateLeft(MapNode *&node);
  void rotateRight(MapNode *&node);
  int getBalanceFactor(MapNode *node);
  int getHeight(MapNode *node);
  void fixHeight(MapNode *node);
  void balanceNode(MapNode *node);
  MapNode *findMin();
  MapNode *findMax();
  MapNode *internalInsert(const_reference newPair);
  void internalRemove(const_reference remPair);
  int insertOrAssign = 0;
};
}  // namespace s21

#include "s21_map.inl"
#endif  //  SRC_S21_MAP_H_
