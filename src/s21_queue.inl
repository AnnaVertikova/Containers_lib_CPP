namespace s21 {
//  ============================================================  //
//  ====================== Queue Functions =====================  //
//  ============================================================  //

template <typename T>
Queue<T>::Queue() : BaseForLSQ<T>::BaseForLSQ() {}

template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const &items)
    : BaseForLSQ<T>::BaseForLSQ(items) {}

//  ============================================================  //
//  ==================== Queue Element access ==================  //
//  ============================================================  //

template <typename T>
typename Queue<T>::const_reference Queue<T>::front() {
  if (BaseForLSQ<T>::empty()) {
    throw std::logic_error("Error: front(): Queue is empty");
  }
  return BaseForLSQ<T>::head_->data_;
}

//  ============================================================  //
//  ====================== Queue Modifiers =====================  //
//  ============================================================  //

template <typename T>
void Queue<T>::pop() {
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

//  ============================================================  //
//  ====================== BONUS: emplace ======================  //
//  ============================================================  //

template <typename T>
template <typename... Args>
void Queue<T>::emplace_back(Args &&...args) {
  value_type arr[sizeof...(Args)] = {args...};
  for (auto value : arr) {
    BaseForLSQ<T>::push(value);
  }
}
}  // namespace s21
