namespace s21 {
//  ============================================================  //
//  =================== BaseForLSQ Functions ===================  //
//  ============================================================  //

template <typename T>
BaseForLSQ<T>::BaseForLSQ() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
BaseForLSQ<T>::BaseForLSQ(std::initializer_list<value_type> const &items)
    : BaseForLSQ() {
  for (auto value : items) {
    push(value);
  }
}

template <typename T>
BaseForLSQ<T>::BaseForLSQ(const BaseForLSQ &bs) : BaseForLSQ() {
  *this = bs;
}

template <typename T>
BaseForLSQ<T>::BaseForLSQ(BaseForLSQ &&bs) : BaseForLSQ() {
  *this = std::move(bs);
}

template <typename T>
BaseForLSQ<T>::~BaseForLSQ() {
  while (size_) {
    pop();
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
BaseForLSQ<T> &BaseForLSQ<T>::operator=(const BaseForLSQ<T> &bs) {
  BaseNode<T> *copy = bs.head_;
  while (copy != nullptr) {
    push(copy->data_);
    copy = copy->pNext_;
  }
  size_ = bs.size_;
  return *this;
}

template <typename T>
BaseForLSQ<T> &BaseForLSQ<T>::operator=(BaseForLSQ<T> &&bs) {
  swap(bs);
  return *this;
}

//  ============================================================  //
//  =================== BaseForLSQ Functions ===================  //
//  ============================================================  //

//  ============================================================  //
//  ================= BaseForLSQ Element access ================  //
//  ============================================================  //

template <typename T>
typename BaseForLSQ<T>::const_reference BaseForLSQ<T>::back() {
  if (empty()) {
    throw std::logic_error("Error: back(): BaseForLSQ is empty");
  }
  return tail_->data_;
}

//  ============================================================  //
//  ================= BaseForLSQ Element access ================  //
//  ============================================================  //

//  ============================================================  //
//  =================== BaseForLSQ Capacity ====================  //
//  ============================================================  //

template <typename T>
bool BaseForLSQ<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename BaseForLSQ<T>::size_type BaseForLSQ<T>::size() {
  return size_;
}

//  ============================================================  //
//  =================== BaseForLSQ Capacity ====================  //
//  ============================================================  //

//  ============================================================  //
//  =================== BaseForLSQ Modifiers ===================  //
//  ============================================================  //

template <typename T>
void BaseForLSQ<T>::push(const_reference value) {
  if (head_ == nullptr) {
    head_ = new BaseNode<T>(value);
    tail_ = head_;
  } else {
    BaseNode<T> *newNode = new BaseNode<T>(value);
    tail_->pNext_ = newNode;
    newNode->pPrev_ = tail_;
    tail_ = newNode;
  }
  size_++;
}

template <typename T>
void BaseForLSQ<T>::pop() {
  if (empty()) {
    throw std::logic_error("Error: pop_back(): The BaseForLSQ is empty");
  }
  if (head_ != nullptr) {
    BaseNode<T> *tmp = tail_;
    tail_ = tail_->pPrev_;
    delete tmp;
    if (tail_ != nullptr) {
      tail_->pNext_ = nullptr;
    }
    size_--;
  }
}

template <typename T>
void BaseForLSQ<T>::swap(BaseForLSQ<T> &bs) {
  std::swap(size_, bs.size_);
  std::swap(head_, bs.head_);
  std::swap(tail_, bs.tail_);
}

//  ============================================================  //
//  =================== BaseForLSQ Modifiers ===================  //
//  ============================================================  //

//  ============================================================  //
//  =============== BaseForLSQ Additional methods ==============  //
//  ============================================================  //

template <typename T>
void BaseForLSQ<T>::print() {
  BaseForLSQ<T> lst(*this);
  for (size_t i = 0; i < lst.size(); i++) {
    std::cout << lst[i] << ' ';
  }
  std::cout << std::endl;
}

//  ============================================================  //
//  =============== BaseForLSQ Additional methods ==============  //
//  ============================================================  //
// template class BaseForLSQ<int>;
}  // namespace s21
