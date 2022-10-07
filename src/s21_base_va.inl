namespace s21 {
//  ============================================================  //
//  ==================== BaseForVA Functions ===================  //
//  ============================================================  //

template <typename T>
BaseForVA<T>::BaseForVA() : size_(0), arr_(nullptr) {}

template <typename T>
BaseForVA<T>::BaseForVA(size_type n) : size_(n), arr_(n ? new T[n] : nullptr) {
  if (n > max_size()) {
    throw std::logic_error(
        "Error: List(size_type n): 'n' is bigger than maximum possible number "
        "of elements");
  }
  if (n) {
    for (size_type i = 0; i < n; i++) {
      arr_[i] = 0;
    }
  }
}

template <typename T>
BaseForVA<T>::BaseForVA(std::initializer_list<value_type> const &items)
    : BaseForVA(items.size()) {
  size_type i = 0;
  for (auto &value : items) {
    arr_[i] = value;
    i++;
  }
}

template <typename T>
BaseForVA<T>::BaseForVA(const BaseForVA &b) {
  *this = b;
}

template <typename T>
BaseForVA<T>::BaseForVA(BaseForVA &&b) : BaseForVA() {
  *this = std::move(b);
}

template <typename T>
BaseForVA<T>::~BaseForVA() {
  delete[] arr_;
  reset();
}
template <typename T>
BaseForVA<T> &BaseForVA<T>::operator=(const BaseForVA &b) {
  BaseForVA<T>::size_ = b.size_;
  BaseForVA<T>::arr_ = new value_type[size_];
  for (size_type i = 0; i < BaseForVA<T>::size(); i++) {
    BaseForVA<T>::arr_[i] = b.arr_[i];
  }
  return *this;
}

template <typename T>
BaseForVA<T> &BaseForVA<T>::operator=(BaseForVA &&b) {
  swap(b);
  return *this;
}

//  ============================================================  //
//  ==================== BaseForVA Functions ===================  //
//  ============================================================  //

//  ============================================================  //
//                     BaseForVA Element access                   //
//  ============================================================  //

template <typename T>
typename BaseForVA<T>::reference BaseForVA<T>::at(size_type pos) {
  if (pos > size_) {
    throw std::logic_error("Error: at(size_type pos): Pos is out of range");
  }
  return arr_[pos];
}

template <typename T>
typename BaseForVA<T>::reference BaseForVA<T>::operator[](size_type pos) {
  if (pos > size_) {
    throw std::logic_error(
        "Error: operator[](size_type pos): Pos is out of range");
  }
  return at(pos);
}

template <typename T>
typename BaseForVA<T>::const_reference BaseForVA<T>::front() {
  if (empty()) {
    throw std::logic_error("Error: front(): The container is empty");
  }
  return arr_[0];
}

template <typename T>
typename BaseForVA<T>::const_reference BaseForVA<T>::back() {
  if (empty()) {
    throw std::logic_error("Error: back(): The container is empty");
  }
  return arr_[size_ - 1];
}

template <typename T>
typename BaseForVA<T>::iterator BaseForVA<T>::data() {
  if (empty()) {
    throw std::logic_error("Error: data(): The container is empty");
  }
  return arr_;
}

//  ============================================================  //
//                     BaseForVA Element access                   //
//  ============================================================  //

//  ============================================================  //
//                       BaseForVA Iterators                      //
//  ============================================================  //

template <typename T>
typename BaseForVA<T>::iterator BaseForVA<T>::begin() {
  if (empty()) {
    return end();
  }
  return iterator(arr_);
}

template <typename T>
typename BaseForVA<T>::iterator BaseForVA<T>::end() {
  return iterator(arr_ + size_);
}

template <typename T>
typename BaseForVA<T>::iterator BaseForVA<T>::cbegin() {
  if (empty()) {
    return cend();
  }
  return iterator(arr_);
}

template <typename T>
typename BaseForVA<T>::iterator BaseForVA<T>::cend() {
  return iterator(arr_ + size_);
}

//  ============================================================  //
//                       BaseForVA Iterators                      //
//  ============================================================  //

//  ============================================================  //
//                       BaseForVA Capacity                       //
//  ============================================================  //

template <typename T>
bool BaseForVA<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename BaseForVA<T>::size_type BaseForVA<T>::size() {
  return size_;
}

template <typename T>
typename BaseForVA<T>::size_type BaseForVA<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(arr_);
}

//  ============================================================  //
//                       BaseForVA Capacity                       //
//  ============================================================  //

//  ============================================================  //
//                       BaseForVA Modifiers                      //
//  ============================================================  //

template <typename T>
void BaseForVA<T>::swap(BaseForVA &other) {
  std::swap(size_, other.size_);
  std::swap(arr_, other.arr_);
}

//  ============================================================  //
//                       BaseForVA Modifiers                      //
//  ============================================================  //

template <typename T>
void BaseForVA<T>::print() {
  for (int i = 0; i < size_; i++) {
    std::cout << arr_[i] << " ";
  }
  std::cout << std::endl;
}

//  ============================================================  //
//                   BaseForVA Additional methods                 //
//  ============================================================  //

template <typename T>
void BaseForVA<T>::reset() {
  size_ = 0;
  arr_ = nullptr;
}

}  // namespace s21
