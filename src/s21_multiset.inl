
namespace s21 {

template <typename K>
MultiSet<K>::MultiSet(std::initializer_list<value_type> const &items) {
  this->root = nullptr;
  this->setSize = 0;
  if (items.size() >= this->max_size()) {
    throw std::invalid_argument("ERROR: items size >= set max size");
  }
  for (value_type value : items) {
    insert(value);
  }
}

template <typename K>
typename MultiSet<K>::iterator MultiSet<K>::insert(const_reference value) {
  iterator curIt(internalInsert(value));
  return curIt;
}

template <typename K>
void MultiSet<K>::merge(MultiSet &other) {
  if (!other.empty()) {
    iterator otherIt = other.begin();

    while (otherIt != other.end()) {
      this->insert(otherIt.itCurrent_->value_);
      ++otherIt;
    }
    other.clear();
  }
}

template <typename K>
typename MultiSet<K>::size_type MultiSet<K>::count(const_reference key) {
  size_type counter = 0;
  iterator itB = this->begin();

  while (itB != this->end()) {
    if (itB.itCurrent_->value_ == key) {
      ++counter;
    }
    ++itB;
  }
  return counter;
}

template <typename K>
typename MultiSet<K>::pair_iterator MultiSet<K>::equal_range(
    const_reference key) {
  pair_iterator range;
  iterator itB = this->begin();

  while (itB != this->end()) {
    if (itB.itCurrent_->value_ == key) {
      range.first = itB;
      break;
    }
    ++itB;
  }

  while (itB != this->end()) {
    if (itB.itCurrent_->value_ == key) {
      ++itB;
      range.second = itB;
    } else {
      ++itB;
    }
  }
  return range;
}

template <typename K>
typename MultiSet<K>::iterator MultiSet<K>::lower_bound(const_reference key) {
  return equal_range(key).first;
}

template <typename K>
typename MultiSet<K>::iterator MultiSet<K>::upper_bound(const_reference key) {
  return equal_range(key).second;
}

//  =============== MultiSet Bonus Task =============== //

template <typename K>
template <typename... Args>
typename MultiSet<K>::pair_it_bool_type MultiSet<K>::emplace(Args &&...args) {
  pair_it_bool_type emResult;
  Set<K> emSet{args...};
  iterator itB = emSet.begin();
  iterator itE = emSet.end();

  while (itB != itE) {
    emResult.first = insert(itB.itCurrent_->value_);
    ++itB;
  }
  emResult.second = true;
  return emResult;
}

template <typename K>
SetNode<K> *MultiSet<K>::internalInsert(const_reference newValue) {
  SetNode<K> *current = this->root;
  SetNode<K> *cur_parent = nullptr;
  while (current) {
    cur_parent = current;
    if (newValue < current->value_) {
      current = current->pLeft_;
    } else {
      current = current->pRight_;
      this->fixHeight(this->root);
    }
  }
  SetNode<K> *newNode = new SetNode<K>(newValue, nullptr, nullptr, cur_parent);
  if (!cur_parent) {
    this->root = newNode;
    this->root->pParent_ = nullptr;

  } else if (newValue < cur_parent->value_) {
    cur_parent->pLeft_ = newNode;
    if (cur_parent->pParent_) this->balanceNode(cur_parent->pParent_);
    this->balanceNode(cur_parent);

  } else {
    cur_parent->pRight_ = newNode;
    if (cur_parent->pParent_) this->balanceNode(cur_parent->pParent_);
    this->balanceNode(cur_parent);
  }

  this->balanceNode(this->root);
  ++this->setSize;
  return this->findNodeAndParent(newValue);
}

}  // namespace s21
