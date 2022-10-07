namespace s21 {
//  ============================================================  //
//  ====================== List Functions ======================  //
//  ============================================================  //

template <typename T>
List<T>::List() : BaseForLSQ<T>() {}

template <typename T>
List<T>::List(size_type n) : List() {
  if (n > max_size()) {
    throw std::logic_error(
        "Error: List(size_type n): 'n' is bigger than maximum possible number "
        "of elements");
  }
  while (n) {
    push_back(0);
    n--;
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items)
    : BaseForLSQ<T>::BaseForLSQ(items) {}

//  ============================================================  //
//  ==================== List Element access ===================  //
//  ============================================================  //

template <typename T>
typename List<T>::const_reference List<T>::front() {
  if (BaseForLSQ<T>::empty()) {
    throw std::logic_error("Error: front(): List is empty");
  }
  return BaseForLSQ<T>::head_->data_;
}

//  ============================================================  //
//  ====================== List Iterators ======================  //
//  ============================================================  //

template <typename T>
typename List<T>::reference List<T>::ListIterator::operator*() {
  if (pPos_ == nullptr) {
    throw std::logic_error("Error: operator*(): The pointer is nullptr");
  }
  return pPos_->data_;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator++() {
  if (pPos_ == nullptr || pPos_->pNext_ == nullptr) {
    throw std::logic_error("Error: operator++(): The pointer is nullptr");
  }
  pPosPrev_ = pPos_;
  pPos_ = pPos_->pNext_;
  return *this;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator--() {
  if (pPosPrev_ == nullptr) {
    throw std::logic_error("Error: operator--(): The pointer is nullptr");
  }
  pPos_ = pPosPrev_;
  pPosPrev_ = pPos_->pPrev_;
  return *this;
}

template <typename T>
bool List<T>::ListIterator::operator==(const List<T>::ListIterator &it) {
  return pPos_ == it.pPos_;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const List<T>::ListIterator &it) {
  return pPos_ != it.pPos_;
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  iterator itBegin;
  if (BaseForLSQ<T>::empty()) {
    return itBegin;
  } else {
    itBegin.pPos_ = BaseForLSQ<T>::head_;
  }
  return itBegin;
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  iterator itEnd;
  if (BaseForLSQ<T>::empty()) {
    return itEnd;
  } else {
    itEnd.pPos_ = nullptr;
    itEnd.pPosPrev_ = BaseForLSQ<T>::tail_;
  }
  return itEnd;
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() {
  const_iterator itBegin;
  if (BaseForLSQ<T>::empty()) {
    return itBegin;
  } else {
    itBegin.pPos_ = BaseForLSQ<T>::head_;
  }
  return itBegin;
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() {
  const_iterator itEnd;
  if (BaseForLSQ<T>::empty()) {
    return itEnd;
  } else {
    itEnd.pPos_ = nullptr;
    itEnd.pPosPrev_ = BaseForLSQ<T>::tail_;
  }
  return itEnd;
}

//  ============================================================  //
//  ====================== List Capacity =======================  //
//  ============================================================  //

template <typename T>
typename List<T>::size_type List<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(BaseNode<T>) / 2;
}

//  ============================================================  //
//  ====================== List Modifiers ======================  //
//  ============================================================  //

template <typename T>
void List<T>::clear() {
  while (BaseForLSQ<T>::size_) {
    pop_front();
  }
  BaseForLSQ<T>::head_ = nullptr;
  BaseForLSQ<T>::tail_ = nullptr;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  if (BaseForLSQ<T>::size_ == max_size()) {
    throw std::logic_error(
        "Error: insert(iterator pos, const_reference value): The size of the "
        "list after this operation is greater than the maximum possible size");
  }
  if (pos == begin()) {
    push_front(value);
    pos = begin();
  } else if (pos == end()) {
    push_back(value);
    pos = end();
    --pos;
  } else {
    BaseNode<T> *newNode = new BaseNode<T>(value);
    newNode->pPrev_ = pos.pPosPrev_;
    newNode->pNext_ = pos.pPos_;
    newNode->pNext_->pPrev_ = newNode;
    if (newNode->pPrev_ != nullptr) {
      newNode->pPrev_->pNext_ = newNode;
    }
    pos.pPos_ = newNode;
    pos.pPosPrev_ = newNode->pPrev_;
    BaseForLSQ<T>::size_++;
  }
  return pos;
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (pos.pPos_ == nullptr) {
    throw std::logic_error(
        "Error: erase(iterator pos): The pointer is nullptr");
  }
  if (pos == begin()) {
    pop_front();
  } else if (pos.pPos_ == end().pPosPrev_) {
    pop_back();
  } else {
    BaseNode<T> *toDelete = pos.pPos_;
    pos.pPos_->pPrev_->pNext_ = pos.pPos_->pNext_;
    pos.pPos_->pNext_->pPrev_ = pos.pPos_->pPrev_;
    delete toDelete;
    BaseForLSQ<T>::size_--;
  }
}

template <typename T>
void List<T>::push_back(const_reference value) {
  BaseForLSQ<T>::push(value);
}

template <typename T>
void List<T>::pop_back() {
  BaseForLSQ<T>::pop();
}

template <typename T>
void List<T>::push_front(const_reference value) {
  if (BaseForLSQ<T>::size_ == max_size()) {
    throw std::logic_error(
        "Error: push_front(const_reference value): The size of the list after "
        "this operation is greater than the maximum possible size");
  }
  if (BaseForLSQ<T>::head_ == nullptr) {
    BaseForLSQ<T>::head_ = new BaseNode<T>(value);
    BaseForLSQ<T>::tail_ = BaseForLSQ<T>::head_;
  } else {
    BaseNode<T> *newNode = new BaseNode<T>(value);
    BaseForLSQ<T>::head_->pPrev_ = newNode;
    newNode->pNext_ = BaseForLSQ<T>::head_;
    BaseForLSQ<T>::head_ = newNode;
  }
  BaseForLSQ<T>::size_++;
}

template <typename T>
void List<T>::pop_front() {
  if (BaseForLSQ<T>::empty()) {
    throw std::logic_error("Error: pop_front(): The list is empty");
  }
  if (BaseForLSQ<T>::head_ != nullptr) {
    BaseNode<T> *tmp = BaseForLSQ<T>::head_;
    BaseForLSQ<T>::head_ = BaseForLSQ<T>::head_->pNext_;
    delete tmp;
    if (BaseForLSQ<T>::head_ != nullptr) {
      BaseForLSQ<T>::head_->pPrev_ = nullptr;
    }
    tmp = nullptr;
    BaseForLSQ<T>::size_--;
  }
}

template <typename T>
void List<T>::merge(List &other) {
  splice(cend(), other);
  sort();
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  if ((BaseForLSQ<T>::size_ + other.size_) >= max_size()) {
    throw std::logic_error(
        "Error: splice(const_iterator pos, List& other): The size of the list "
        "after this operation is greater than the maximum possible size");
  }
  BaseNode<T> *tmp = other.head_;
  while (tmp != nullptr) {
    insert(pos, tmp->data_);
    pos.pPosPrev_ = pos.pPosPrev_->pNext_;
    other.pop_front();
    tmp = other.head_;
  }
}

template <typename T>
void List<T>::reverse() {
  if (BaseForLSQ<T>::empty()) {
    throw std::logic_error("Error: reverse(): The list is empty");
  }
  iterator itBegin(BaseForLSQ<T>::head_);
  iterator itEnd(BaseForLSQ<T>::tail_);
  if (BaseForLSQ<T>::size() % 2 == 0) {
    while ((itBegin.pPos_ != itEnd.pPos_->pNext_ &&
            itEnd.pPos_ != itBegin.pPos_->pPrev_)) {
      std::swap(*itBegin, *itEnd);
      ++itBegin;
      --itEnd;
    }
  } else {
    while (itBegin != itEnd) {
      std::swap(*itBegin, *itEnd);
      ++itBegin;
      --itEnd;
    }
  }
}

template <typename T>
void List<T>::unique() {
  if (BaseForLSQ<T>::empty()) {
    throw std::logic_error("Error: unique(): The list is empty");
  }
  iterator iCurrent(BaseForLSQ<T>::head_);
  iterator iTmp(BaseForLSQ<T>::tail_);
  while (iCurrent.pPos_->pNext_ != nullptr) {
    while (iTmp.pPos_ != iCurrent.pPos_) {
      if (*iCurrent == *iTmp) {
        erase(iTmp);
        --iTmp;
      } else {
        --iTmp;
      }
    }
    if (iCurrent.pPos_->pNext_) {
      ++iCurrent;
    }
    iTmp.pPos_ = BaseForLSQ<T>::tail_;
    iTmp.pPosPrev_ = BaseForLSQ<T>::tail_->pPrev_;
  }
}

template <typename T>
void List<T>::sort() {
  if (BaseForLSQ<T>::empty()) {
    throw std::logic_error("Error: sort(): Container is empty");
  }
  iterator itCurrent(BaseForLSQ<T>::head_);
  iterator itEnd(BaseForLSQ<T>::tail_);
  size_type count = BaseForLSQ<T>::size();
  while (count != 0) {
    while (itCurrent != itEnd) {
      if (itCurrent.pPos_->data_ > itCurrent.pPos_->pNext_->data_) {
        std::swap(itCurrent.pPos_->data_, itCurrent.pPos_->pNext_->data_);
      }
      ++itCurrent;
    }
    itCurrent.pPos_ = BaseForLSQ<T>::head_;
    count--;
  }
}

//  ============================================================  //
//  ====================== BONUS: emplace ======================  //
//  ============================================================  //

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  s21::List<int> lst{args...};
  iterator val(lst.begin());
  iterator tmp = pos;
  for (size_t i = 0; i < lst.size(); i++) {
    tmp = insert(tmp, *val);
    if (tmp.pPos_ != nullptr && tmp.pPos_->pNext_ != nullptr) {
      ++tmp;
    } else {
      tmp = cend();
    }
    if (val.pPos_->pNext_ != nullptr) {
      ++val;
    }
  }
  --tmp;
  return tmp;
}

template <typename T>
template <typename... Args>
void List<T>::emplace_back(Args &&...args) {
  emplace(cend(), args...);
}

template <typename T>
template <typename... Args>
void List<T>::emplace_front(Args &&...args) {
  emplace(cbegin(), args...);
}
}  // namespace s21
