
namespace s21 {

//  ================= Set Member functions ============== //

template <typename K>
Set<K>::Set() : root(nullptr), setSize(0) {}

template <typename K>
Set<K>::Set(std::initializer_list<value_type> const &items)
    : root(nullptr), setSize(0) {
  if (items.size() >= max_size()) {
    throw std::invalid_argument("ERROR: items size >= container max size");
  }
  for (value_type value : items) {
    internalInsert(value);
  }
}

template <typename K>
Set<K>::Set(const Set &m) : root(nullptr), setSize(0) {
  *this = m;
}

template <typename K>
Set<K>::Set(Set &&m) : root(nullptr), setSize(0) {
  *this = std::move(m);
}

template <typename K>
Set<K>::~Set() {
  deleteContainer(root);
}

template <typename K>
Set<K> &Set<K>::operator=(const Set<K> &m) {
  if (this != &m) {
    clear();
  }
  if (m.root != nullptr) {
    this->copyNode(m.root);
    setSize = m.setSize;
  }
  return *this;
}

template <typename K>
Set<K> &Set<K>::operator=(Set<K> &&m) {
  if (this != &m) {
    swap(m);
  }
  return *this;
}

//  =================== Set Iterators =================== //

template <typename K>
typename Set<K>::SetIterator &Set<K>::SetIterator ::operator++() {
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
      while (itParent_ && itParent_->value_ <= itCurrent_->value_) {
        itCurrent_ = itParent_;
        itParent_ = itCurrent_->pParent_;
      }
      if (itParent_) {
        itCurrent_ = itParent_;
        itParent_ = itCurrent_->pParent_;
      }
    }
  } else {
    itParent_ = itCurrent_;
    itCurrent_ = itCurrent_->pRight_;
  }
  return *this;
}

template <typename K>
typename Set<K>::SetIterator &Set<K>::SetIterator ::operator--() {
  iterator itMax = findMaxIt();

  if (*this == findMinIt()) {
    throw std::out_of_range("ERROR: value is min");
  }

  if (!itCurrent_ && itParent_ == itMax.itCurrent_) {
    *this = itMax;
  } else {
    if (itCurrent_->pLeft_) {
      if (itCurrent_->pLeft_->value_ != itCurrent_->value_) {
        if (itCurrent_->pLeft_->pRight_) {
          itParent_ = itCurrent_->pLeft_;
          itCurrent_ = itCurrent_->pLeft_->pRight_;
        } else {
          itParent_ = itCurrent_;
          itCurrent_ = itCurrent_->pLeft_;
        }
      } else {
        itParent_ = itCurrent_;
        itCurrent_ = itCurrent_->pLeft_;
      }
    } else if (itParent_ && itParent_->pRight_ == itCurrent_) {
      itCurrent_ = itParent_;
      itParent_ = itCurrent_->pParent_;

    } else if (itParent_ && itParent_->pLeft_ == itCurrent_) {
      while (itParent_ && itCurrent_->value_ <= itParent_->value_) {
        itCurrent_ = itParent_;
        itParent_ = itCurrent_->pParent_;
      }
      if (itParent_) {
        itCurrent_ = itParent_;
        itParent_ = itCurrent_->pParent_;
      }
    }
  }

  return *this;
}

template <typename K>
typename Set<K>::reference Set<K>::SetIterator ::operator*() {
  if (!itCurrent_) {
    throw std::out_of_range("ERROR: iterator is nullptr");
  } else {
    return itCurrent_->value_;
  }
}

template <typename K>
typename Set<K>::SetIterator Set<K>::SetIterator ::findMinIt() {
  iterator min = getRootIt();
  while (min.itCurrent_->pLeft_) {
    min.itParent_ = min.itCurrent_;
    min.itCurrent_ = min.itCurrent_->pLeft_;
  }
  return min;
}

template <typename K>
typename Set<K>::SetIterator Set<K>::SetIterator ::findMaxIt() {
  iterator max = getRootIt();
  while (max.itCurrent_->pRight_) {
    max.itParent_ = max.itCurrent_;
    max.itCurrent_ = max.itCurrent_->pRight_;
  }
  return max;
}

template <typename K>
typename Set<K>::SetIterator Set<K>::SetIterator ::getRootIt() {
  iterator root = *this;
  while (root.itParent_) {
    SetNode<K> *temp = root.itParent_->pParent_;
    root.itCurrent_ = root.itParent_;
    root.itParent_ = temp;
  }
  return root;
}

template <typename K>
typename Set<K>::iterator Set<K>::begin() {
  if (empty()) {
    throw std::out_of_range("ERROR: container is empty");
  }
  iterator itBegin(findMin());
  return itBegin;
}

template <typename K>
typename Set<K>::iterator Set<K>::end() {
  if (empty()) {
    throw std::out_of_range("ERROR: container is empty");
  }
  iterator itEnd(findMax());
  itEnd.itParent_ = itEnd.itCurrent_;
  itEnd.itCurrent_ = itEnd.itCurrent_->pRight_;
  return itEnd;
}

//  =============== Set Capacity =============== //

template <typename K>
bool Set<K>::empty() {
  return setSize == 0;
}

template <typename K>
typename Set<K>::size_type Set<K>::size() {
  return setSize;
}

template <typename K>
typename Set<K>::size_type Set<K>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(SetNode<K>) / 2;
}

//  =============== Set Modifiers =============== //

template <typename K>
void Set<K>::clear() {
  deleteContainer(root);
}

template <typename K>
typename Set<K>::pair_it_bool_type Set<K>::insert(const_reference value) {
  size_type currentSize = setSize;
  iterator curIt(internalInsert(value));
  pair_it_bool_type success(curIt, true);
  pair_it_bool_type fail(curIt, false);

  if (currentSize < setSize) {
    return success;
  } else {
    return fail;
  }
}

template <typename K>
void Set<K>::erase(iterator pos) {
  if (!root) {
    throw std::invalid_argument("ERROR: container is emty");
  }
  if (!pos.itCurrent_) {
    throw std::out_of_range("ERROR:iterator is nullptr");
  }
  internalRemove(pos.itCurrent_->value_);
}

template <typename K>
void Set<K>::swap(Set &other) {
  if (this == &other) {
    throw std::invalid_argument("ERROR: trying swap to itself");
  } else {
    std::swap(root, other.root);
    std::swap(setSize, other.setSize);
  }
}

template <typename K>
void Set<K>::merge(Set &other) {
  if (!other.empty()) {
    Set<K> tempSet;
    iterator otherIt = other.begin();
    iterator itEnd = other.end();
    iterator itMax(other.findMax());

    while (otherIt != itEnd) {
      if ((insert(otherIt.itCurrent_->value_)).second) {
        tempSet.internalInsert(otherIt.itCurrent_->value_);
      }
      ++otherIt;
    }

    iterator tempIt = tempSet.begin();
    iterator tempEnd = tempSet.end();

    while (tempIt != tempEnd) {
      value_type tempKV = tempIt.itCurrent_->value_;
      other.internalRemove(tempKV);
      ++tempIt;
    }
  }
}

//  =============== Set Lookup ================== //

template <typename K>
typename Set<K>::iterator Set<K>::find(const K &key) {
  iterator result = end();
  if (contains(key)) {
    iterator itFind(findNodeAndParent(key));
    result = itFind;
  }

  return result;
}

template <typename K>
bool Set<K>::contains(const K &key) {
  return findNodeAndParent(key) ? true : false;
}

//  =============== Set Bonus Task =============== //

template <typename K>
template <typename... Args>
typename Set<K>::pair_it_bool_type Set<K>::emplace(Args &&...args) {
  pair_it_bool_type emResult;
  Set<K> emSet{args...};
  iterator itB = emSet.begin();
  iterator itE = emSet.end();

  while (itB != itE) {
    emResult = insert(itB.itCurrent_->value_);
    ++itB;
  }
  return emResult;
}

//  =============================================================== //
//  ============== Set additional functions ============== //
//  =============================================================== //

template <typename K>
void Set<K>::freeNode(SetNode<K> *node) {
  if (node) {
    delete node;
  }
  --setSize;
}

template <typename K>
void Set<K>::deleteContainer(SetNode<K> *node) {
  if (node) {
    deleteContainer(node->pLeft_);
    deleteContainer(node->pRight_);
    delete node;
  }
  root = nullptr;
  setSize = 0;
}

template <typename K>
void Set<K>::copyNode(SetNode<K> *node) {
  if (node) {
    if (node->pLeft_) copyNode(node->pLeft_);
    if (node->pRight_) copyNode(node->pRight_);
    internalInsert(node->value_);
  }
}

template <typename K>
SetNode<K> *Set<K>::findNodeAndParent(const K &key) {
  SetNode<K> *current = root;
  int keyFound = 0;
  while (current) {
    if (key == current->value_) {
      keyFound = 1;
      break;
    } else {
      if (key < current->value_) {
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

template <typename K>
void Set<K>::rotateLeft(SetNode<K> *&node) {
  SetNode<K> *newNode = node->pRight_;
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
    if (node->value_ >= node->pParent_->value_) {
      node->pParent_->pRight_ = node;
    } else {
      node->pParent_->pLeft_ = node;
    }
  }
  fixHeight(root);
}

template <typename K>
void Set<K>::rotateRight(SetNode<K> *&node) {
  SetNode<K> *newNode = node->pLeft_;
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
    if (node->value_ >= node->pParent_->value_) {
      node->pParent_->pRight_ = node;
    } else {
      node->pParent_->pLeft_ = node;
    }
  }
  fixHeight(root);
}

template <typename K>
int Set<K>::getBalanceFactor(SetNode<K> *node) {
  return getHeight(node->pRight_) - getHeight(node->pLeft_);
}

template <typename K>
int Set<K>::getHeight(SetNode<K> *node) {
  return node ? node->height_ : 0;
}

template <typename K>
void Set<K>::fixHeight(SetNode<K> *node) {
  if (node->pLeft_) fixHeight(node->pLeft_);
  if (node->pRight_) fixHeight(node->pRight_);
  int hL = (node->pLeft_ ? getHeight(node->pLeft_) : 0);
  int hR = (node->pRight_ ? getHeight(node->pRight_) : 0);

  node->height_ = (hL > hR ? hL : hR) + 1;
}

template <typename K>
void Set<K>::balanceNode(SetNode<K> *node) {
  if (setSize != 0) {
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

template <typename K>
SetNode<K> *Set<K>::findMin() {
  SetNode<K> *min = root;
  while (min && min->pLeft_ != nullptr) min = min->pLeft_;
  return min;
}

template <typename K>
SetNode<K> *Set<K>::findMax() {
  SetNode<K> *max = root;
  while (max && max->pRight_ != nullptr) max = max->pRight_;
  return max;
}

template <typename K>
SetNode<K> *Set<K>::internalInsert(const_reference newValue) {
  SetNode<K> *current = root;
  SetNode<K> *cur_parent = nullptr;
  if (!findNodeAndParent(newValue)) {
    while (current) {
      cur_parent = current;
      if (newValue < current->value_) {
        current = current->pLeft_;
      } else {
        current = current->pRight_;
      }
    }
    SetNode<K> *newNode =
        new SetNode<K>(newValue, nullptr, nullptr, cur_parent);
    if (!cur_parent) {
      root = newNode;
      root->pParent_ = nullptr;

    } else if (newValue < cur_parent->value_) {
      cur_parent->pLeft_ = newNode;
      if (cur_parent->pParent_) balanceNode(cur_parent->pParent_);
      balanceNode(cur_parent);

    } else if (newValue > cur_parent->value_) {
      cur_parent->pRight_ = newNode;
      if (cur_parent->pParent_) balanceNode(cur_parent->pParent_);
      balanceNode(cur_parent);
    }

    balanceNode(root);
    ++setSize;
  }
  return findNodeAndParent(newValue);
}

template <typename K>
void Set<K>::internalRemove(const_reference remValue) {
  SetNode<K> *remNode;
  SetNode<K> *repNode;
  remNode = findNodeAndParent(remValue);

  if (remNode) {
    SetNode<K> *remParent = remNode->pParent_;

    if (!remNode->pRight_ && !remNode->pLeft_) {
      if (remNode->pParent_) {
        if (remNode->pParent_->pLeft_ == remNode) {
          remNode->pParent_->pLeft_ = nullptr;
        } else {
          remNode->pParent_->pRight_ = nullptr;
        }
        SetNode<K> *repParent = remNode->pParent_;
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
      SetNode<K> *repParent = remNode;
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

    } else if (remNode->value_ < remParent->value_) {
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
