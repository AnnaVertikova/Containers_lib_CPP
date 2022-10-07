
namespace s21 {

//  ================= Map Member functions ============== //

template <typename K, typename T>
Map<K, T>::Map() : root(nullptr), mapSize(0) {}

template <typename K, typename T>
Map<K, T>::Map(std::initializer_list<value_type> const &items)
    : root(nullptr), mapSize(0) {
  if (items.size() >= max_size()) {
    throw std::invalid_argument("ERROR: items size >= container max size");
  }
  for (value_type value : items) {
    internalInsert(value);
  }
}

template <typename K, typename T>
Map<K, T>::Map(const Map &m) : root(nullptr), mapSize(0) {
  *this = m;
}

template <typename K, typename T>
Map<K, T>::Map(Map &&m) : root(nullptr), mapSize(0) {
  *this = std::move(m);
}

template <typename K, typename T>
Map<K, T>::~Map() {
  deleteContainer(root);
}

template <typename K, typename T>
Map<K, T> &Map<K, T>::operator=(const Map<K, T> &m) {
  if (this != &m) {
    clear();
  }
  if (m.root != nullptr) {
    this->copyNode(m.root);
    mapSize = m.mapSize;
  }
  return *this;
}

template <typename K, typename T>
Map<K, T> &Map<K, T>::operator=(Map<K, T> &&m) {
  if (this != &m) {
    swap(m);
  }
  return *this;
}

//  =================== Map Element access ========================= //

template <typename K, typename T>
T &Map<K, T>::at(const K &key) {
  K min = begin().itCurrent_->keyValue_.first;
  K max = findMax()->keyValue_.first;

  if (key < min || key > max) {
    throw std::out_of_range("ERROR: key is out of range");
  } else {
    MapNode *searchResult = findNodeAndParent(key);
    return searchResult->keyValue_.second;
  }
}

template <typename K, typename T>
T &Map<K, T>::operator[](const K &key) {
  if (!contains(key) || root == nullptr) {
    insert(key, T());
  }
  MapNode *searchResult = findNodeAndParent(key);
  return searchResult->keyValue_.second;
}

//  =================== Map Iterators =================== //

template <typename K, typename T>
typename Map<K, T>::MapIterator &Map<K, T>::MapIterator ::operator++() {
  if (!itCurrent_ && itParent_ == findMaxIt().itCurrent_) {
    throw std::out_of_range("ERROR: can't increment end()");
  }

  if (*this != findMaxIt()) {
    if (itCurrent_->pRight_) {
      if (itCurrent_->pRight_->pLeft_) {
        itParent_ = itCurrent_->pRight_;
        itCurrent_ = itCurrent_->pRight_->pLeft_;
      } else {
        itParent_ = itCurrent_;
        itCurrent_ = itCurrent_->pRight_;
      }
    } else if (itParent_ && itParent_->pLeft_ == itCurrent_) {
      itCurrent_ = itParent_;
      itParent_ = itCurrent_->pParent_;

    } else if (itParent_ && itParent_->pRight_ == itCurrent_) {
      while (itParent_->keyValue_.first < itCurrent_->keyValue_.first) {
        itCurrent_ = itParent_;
        itParent_ = itCurrent_->pParent_;
      }
      itCurrent_ = itParent_;
      itParent_ = itCurrent_->pParent_;
    }
  } else {
    itParent_ = itCurrent_;
    itCurrent_ = itCurrent_->pRight_;
  }
  return *this;
}

template <typename K, typename T>
typename Map<K, T>::MapIterator &Map<K, T>::MapIterator ::operator--() {
  iterator itMax = findMaxIt();

  if (*this == findMinIt()) {
    throw std::out_of_range("ERROR: value is min");
  }

  if (!itCurrent_ && itParent_ == itMax.itCurrent_) {
    *this = itMax;
  } else {
    if (itCurrent_->pLeft_) {
      if (itCurrent_->pLeft_->pRight_) {
        itParent_ = itCurrent_->pLeft_;
        itCurrent_ = itCurrent_->pLeft_->pRight_;
      } else {
        itParent_ = itCurrent_;
        itCurrent_ = itCurrent_->pLeft_;
      }

    } else if (itParent_ && itParent_->pRight_ == itCurrent_) {
      itCurrent_ = itParent_;
      itParent_ = itCurrent_->pParent_;

    } else if (itParent_ && itParent_->pLeft_ == itCurrent_) {
      while (itCurrent_->keyValue_.first < itParent_->keyValue_.first) {
        itCurrent_ = itParent_;
        itParent_ = itCurrent_->pParent_;
      }
      itCurrent_ = itParent_;
      itParent_ = itCurrent_->pParent_;
    }
  }
  return *this;
}

template <typename K, typename T>
typename Map<K, T>::reference Map<K, T>::MapIterator ::operator*() {
  if (!itCurrent_) {
    throw std::out_of_range("ERROR: iterator is nullptr");
  }
  return itCurrent_->keyValue_;
}

template <typename K, typename T>
typename Map<K, T>::MapIterator Map<K, T>::MapIterator ::findMinIt() {
  iterator min = getRootIt();
  while (min.itCurrent_->pLeft_) {
    min.itParent_ = min.itCurrent_;
    min.itCurrent_ = min.itCurrent_->pLeft_;
  }
  return min;
}

template <typename K, typename T>
typename Map<K, T>::MapIterator Map<K, T>::MapIterator ::findMaxIt() {
  iterator max = getRootIt();
  while (max.itCurrent_->pRight_) {
    max.itParent_ = max.itCurrent_;
    max.itCurrent_ = max.itCurrent_->pRight_;
  }
  return max;
}

template <typename K, typename T>
typename Map<K, T>::MapIterator Map<K, T>::MapIterator ::getRootIt() {
  iterator root = *this;
  while (root.itParent_) {
    MapNode *temp = root.itParent_->pParent_;
    root.itCurrent_ = root.itParent_;
    root.itParent_ = temp;
  }
  return root;
}

template <typename K, typename T>
typename Map<K, T>::iterator Map<K, T>::begin() {
  if (empty()) {
    throw std::out_of_range("ERROR: container is empty");
  }
  iterator itBegin(findMin());
  return itBegin;
}

template <typename K, typename T>
typename Map<K, T>::iterator Map<K, T>::end() {
  if (empty()) {
    throw std::out_of_range("ERROR: container is empty");
  }
  iterator itEnd(findMax());
  itEnd.itParent_ = itEnd.itCurrent_;
  itEnd.itCurrent_ = itEnd.itCurrent_->pRight_;
  return itEnd;
}

template <typename K, typename T>
typename Map<K, T>::const_iterator Map<K, T>::cbegin() {
  const_iterator itBegin(findMin());
  return itBegin;
}

template <typename K, typename T>
typename Map<K, T>::const_iterator Map<K, T>::cend() {
  if (empty()) {
    throw std::invalid_argument("ERROR: container is empty");
  }
  const_iterator itEnd(findMax());
  itEnd.itParent_ = itEnd.itCurrent_;
  itEnd.itCurrent_ = itEnd.itCurrent_->pRight_;
  return itEnd;
}

//  =============== Map Capacity =============== //

template <typename K, typename T>
bool Map<K, T>::empty() {
  return mapSize == 0;
}

template <typename K, typename T>
typename Map<K, T>::size_type Map<K, T>::size() {
  return mapSize;
}

template <typename K, typename T>
typename Map<K, T>::size_type Map<K, T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(MapNode) / 2;
}

//  =============== Map Modifiers =============== //

template <typename K, typename T>
void Map<K, T>::clear() {
  deleteContainer(root);
}

template <typename K, typename T>
typename Map<K, T>::pair_it_bool_type Map<K, T>::insert(const_reference value) {
  size_type currentSize = mapSize;
  iterator curIt(internalInsert(value));
  pair_it_bool_type success(curIt, true);
  pair_it_bool_type fail(curIt, false);

  if (currentSize < mapSize) {
    return success;
  } else {
    return fail;
  }
}

template <typename K, typename T>
typename Map<K, T>::pair_it_bool_type Map<K, T>::insert(const K &key,
                                                        const T &item) {
  std::pair<K, T> newPair(key, item);
  return insert(newPair);
}

template <typename K, typename T>
typename Map<K, T>::pair_it_bool_type Map<K, T>::insert_or_assign(
    const K &key, const T &item) {
  insertOrAssign = 1;
  std::pair<K, T> newPair(key, item);
  return insert(newPair);
}

template <typename K, typename T>
void Map<K, T>::erase(iterator pos) {
  if (!root) {
    throw std::invalid_argument("ERROR: container is emty");
  }

  if (!pos.itCurrent_) {
    throw std::out_of_range("ERROR: iterator is nullptr");
  }

  internalRemove(pos.itCurrent_->keyValue_);
}

template <typename K, typename T>
void Map<K, T>::swap(Map &other) {
  if (this == &other) {
    throw std::invalid_argument("ERROR: trying swap to itself");
  } else {
    std::swap(root, other.root);
    std::swap(mapSize, other.mapSize);
  }
}

template <typename K, typename T>
void Map<K, T>::merge(Map &other) {
  if (!other.empty()) {
    Map<K, T> tempMap;
    iterator otherIt = other.begin();
    iterator itEnd = other.end();
    iterator itMax(other.findMax());

    while (otherIt != itEnd) {
      if ((insert(otherIt.itCurrent_->keyValue_)).second) {
        tempMap.internalInsert(otherIt.itCurrent_->keyValue_);
      }
      ++otherIt;
    }

    iterator tempIt = tempMap.begin();
    iterator tempEnd = tempMap.end();

    while (tempIt != tempEnd) {
      value_type tempKV = tempIt.itCurrent_->keyValue_;
      other.internalRemove(tempKV);
      ++tempIt;
    }
  }
}

//  =============== Map Lookup ================== //

template <typename K, typename T>
bool Map<K, T>::contains(const K &key) {
  return findNodeAndParent(key) ? true : false;
}

//  =============== Map Bonus Task =============== //

template <typename K, typename T>
template <typename... Args>
typename Map<K, T>::pair_it_bool_type Map<K, T>::emplace(Args &&...args) {
  pair_it_bool_type emResult;
  Map<K, T> emSet{args...};
  iterator itB = emSet.begin();
  iterator itE = emSet.end();

  while (itB != itE) {
    emResult = insert(itB.itCurrent_->keyValue_);
    ++itB;
  }
  return emResult;
}

//  =============================================================== //
//  ============== Map additional functions ============== //
//  =============================================================== //

template <typename K, typename T>
void Map<K, T>::freeNode(MapNode *node) {
  if (node) {
    delete node;
  }
  --mapSize;
}

template <typename K, typename T>
void Map<K, T>::deleteContainer(MapNode *node) {
  if (node) {
    deleteContainer(node->pLeft_);
    deleteContainer(node->pRight_);
    delete node;
  }
  root = nullptr;
  mapSize = 0;
}

template <typename K, typename T>
void Map<K, T>::copyNode(MapNode *node) {
  if (node) {
    if (node->pLeft_) copyNode(node->pLeft_);
    if (node->pRight_) copyNode(node->pRight_);
    internalInsert(node->keyValue_);
  }
}

template <typename K, typename T>
typename Map<K, T>::MapNode *Map<K, T>::findNodeAndParent(const K &key) {
  MapNode *current = root;
  int keyFound = 0;
  while (current) {
    if (key == current->keyValue_.first) {
      keyFound = 1;
      break;
    } else {
      if (key < current->keyValue_.first) {
        current = current->pLeft_;
      } else {
        current = current->pRight_;
      }
      keyFound = 1;
    }
  }
  if (!keyFound) {
    current = nullptr;
  }
  return current;
}

template <typename K, typename T>
void Map<K, T>::rotateLeft(MapNode *&node) {
  MapNode *newNode = node->pRight_;
  if (root == node) {
    root = newNode;
    root->pParent_ = nullptr;
  } else {
    newNode->pParent_ = node->pParent_;
  }

  node->pRight_ = newNode->pLeft_;
  if (node->pRight_) node->pRight_->pParent_ = node;
  newNode->pLeft_ = node;
  newNode->pLeft_->pParent_ = newNode;
  node = newNode;

  if (node->pParent_) {
    if (node->keyValue_.first > node->pParent_->keyValue_.first) {
      node->pParent_->pRight_ = node;
    } else {
      node->pParent_->pLeft_ = node;
    }
  }
  fixHeight(root);
}

template <typename K, typename T>
void Map<K, T>::rotateRight(MapNode *&node) {
  MapNode *newNode = node->pLeft_;
  if (root == node) {
    root = newNode;
    root->pParent_ = nullptr;
  } else {
    newNode->pParent_ = node->pParent_;
  }

  node->pLeft_ = newNode->pRight_;
  if (node->pLeft_) node->pLeft_->pParent_ = node;
  newNode->pRight_ = node;
  newNode->pRight_->pParent_ = newNode;
  node = newNode;

  if (node->pParent_) {
    if (node->keyValue_.first > node->pParent_->keyValue_.first) {
      node->pParent_->pRight_ = node;
    } else {
      node->pParent_->pLeft_ = node;
    }
  }
  fixHeight(root);
}

template <typename K, typename T>
int Map<K, T>::getBalanceFactor(MapNode *node) {
  return getHeight(node->pRight_) - getHeight(node->pLeft_);
}

template <typename K, typename T>
int Map<K, T>::getHeight(MapNode *node) {
  return node ? node->height_ : 0;
}

template <typename K, typename T>
void Map<K, T>::fixHeight(MapNode *node) {
  if (node->pLeft_) fixHeight(node->pLeft_);
  if (node->pRight_) fixHeight(node->pRight_);
  int hL = (node->pLeft_ ? getHeight(node->pLeft_) : 0);
  int hR = (node->pRight_ ? getHeight(node->pRight_) : 0);

  node->height_ = (hL > hR ? hL : hR) + 1;
}

template <typename K, typename T>
void Map<K, T>::balanceNode(MapNode *node) {
  if (mapSize != 0) {
    fixHeight(root);
    if (getBalanceFactor(node) == 2) {
      if (getBalanceFactor(node->pRight_) < 0) {
        rotateRight(node->pRight_);
      }
      rotateLeft(node);
    }
    if (getBalanceFactor(node) == -2) {
      if (getBalanceFactor(node->pLeft_) > 0) {
        rotateLeft(node->pLeft_);
      }
      rotateRight(node);
    }
  }
}

template <typename K, typename T>
typename Map<K, T>::MapNode *Map<K, T>::findMin() {
  MapNode *min = root;
  while (min && min->pLeft_ != nullptr) min = min->pLeft_;
  return min;
}

template <typename K, typename T>
typename Map<K, T>::MapNode *Map<K, T>::findMax() {
  MapNode *max = root;
  while (max && max->pRight_ != nullptr) max = max->pRight_;
  return max;
}

template <typename K, typename T>
typename Map<K, T>::MapNode *Map<K, T>::internalInsert(
    const_reference newPair) {
  MapNode *current = root;
  MapNode *cur_parent = nullptr;
  if (!findNodeAndParent(newPair.first) || insertOrAssign == 1) {
    while (current) {
      cur_parent = current;
      if (newPair.first < current->keyValue_.first) {
        current = current->pLeft_;
      } else if (newPair.first > current->keyValue_.first) {
        current = current->pRight_;
      } else {
        if (insertOrAssign == 1) {
          current->keyValue_.second = newPair.second;
          insertOrAssign = 0;
        }
        fixHeight(root);
        return current;
      }
    }
    MapNode *new_node = new MapNode(newPair, nullptr, nullptr, cur_parent);
    if (!cur_parent) {
      root = new_node;
      root->pParent_ = nullptr;

    } else if (newPair.first < cur_parent->keyValue_.first) {
      cur_parent->pLeft_ = new_node;
      if (cur_parent->pParent_) balanceNode(cur_parent->pParent_);
      balanceNode(cur_parent);

    } else if (newPair.first > cur_parent->keyValue_.first) {
      cur_parent->pRight_ = new_node;
      if (cur_parent->pParent_) balanceNode(cur_parent->pParent_);
      balanceNode(cur_parent);
    }

    balanceNode(root);
    ++mapSize;
  }
  return findNodeAndParent(newPair.first);
}

template <typename K, typename T>
void Map<K, T>::internalRemove(const_reference remPair) {
  MapNode *remNode;
  MapNode *repNode;
  remNode = findNodeAndParent(remPair.first);

  if (remNode) {
    MapNode *remParent = remNode->pParent_;

    if (!remNode->pRight_ && !remNode->pLeft_) {
      if (remNode->pParent_) {
        if (remNode->pParent_->pLeft_ == remNode) {
          remNode->pParent_->pLeft_ = nullptr;
        } else {
          remNode->pParent_->pRight_ = nullptr;
        }
        MapNode *repParent = remNode->pParent_;
        freeNode(remNode);
        fixHeight(repParent);
      } else {
        freeNode(remNode);
        root = nullptr;
      }

      balanceNode(root);
      return;

    } else if (!remNode->pRight_) {
      repNode = remNode->pLeft_;
    } else if (!remNode->pLeft_) {
      repNode = remNode->pRight_;
    } else {
      MapNode *repParent = remNode;
      repNode = remNode->pLeft_;
      while (repNode->pRight_) {
        repParent = repNode;
        repNode = repNode->pRight_;
      }
      if (repParent == remNode) {
        repNode->pRight_ = remNode->pRight_;
        repNode->pRight_->pParent_ = repNode;
      } else {
        repParent->pRight_ = repNode->pLeft_;
        if (repParent->pRight_) repParent->pRight_->pParent_ = repParent;
        repNode->pLeft_ = remNode->pLeft_;
        repNode->pLeft_->pParent_ = repNode;

        repNode->pRight_ = remNode->pRight_;
        repNode->pRight_->pParent_ = repNode;
      }
    }
    if (!remParent) {
      root = repNode;
      root->pParent_ = nullptr;
      if (root->pLeft_) root->pLeft_->pParent_ = root;
      if (root->pRight_) root->pRight_->pParent_ = root;

    } else if (remNode->keyValue_.first < remParent->keyValue_.first) {
      remParent->pLeft_ = repNode;
      repNode->pParent_ = remNode->pParent_;
    } else {
      remParent->pRight_ = repNode;
      repNode->pParent_ = remNode->pParent_;
    }
    balanceNode(root);
    freeNode(remNode);
  }
}
}  // namespace s21
