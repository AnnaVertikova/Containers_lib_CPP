namespace s21 {
//  ============================================================  //
//  ===================== Vector Functions =====================  //
//  ============================================================  //

template <typename T>
Vector<T>::Vector() : BaseForVA<T>::BaseForVA() {
  capacity_ = 1;
  BaseForVA<T>::arr_ = new value_type[capacity_];
}

template <typename T>
Vector<T>::Vector(size_type n) {
  if (n > BaseForVA<T>::max_size()) {
    throw std::logic_error(
        "Error: Vector(size_type n): 'n' is bigger than maximum possible "
        "number of elements");
  }
  BaseForVA<T>::size_ = n;
  capacity_ = n * 2;
  BaseForVA<T>::arr_ = new value_type[capacity_];
  if (n) {
    for (size_type i = 0; i < n; i++) {
      BaseForVA<T>::arr_[i] = 0;
    }
  }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items)
    : Vector(items.size()) {
  size_type i = 0;
  for (auto &value : items) {
    BaseForVA<T>::arr_[i] = value;
    i++;
  }
}

template <typename T>
Vector<T>::Vector(const Vector &v) : BaseForVA<T>::BaseForVA() {
  *this = v;
}

template <typename T>
Vector<T>::Vector(Vector &&v) : Vector() {
  *this = std::move(v);
}

template <typename T>
Vector<T>::~Vector() {
  clear();
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  BaseForVA<T>::size_ = v.size_;
  capacity_ = v.capacity_;
  BaseForVA<T>::arr_ = new value_type[capacity_];
  for (size_type i = 0; i < BaseForVA<T>::size(); i++) {
    BaseForVA<T>::arr_[i] = v.arr_[i];
  }
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  swap(v);
  return *this;
}

// //  ============================================================  //
// //                        Vector Capacity                         //
// //  ============================================================  //

template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size > BaseForVA<T>::max_size()) {
    throw std::logic_error(
        "Error: reserve(size_type size): new capacity size is bigger  than "
        "maximum possible number of elements");
  }
  if (size > capacity_) {
    realloc(size);
  }
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  realloc(BaseForVA<T>::size_);
}

//  ============================================================  //
//                        Vector Modifiers                        //
//  ============================================================  //

template <typename T>
void Vector<T>::clear() {
  if (BaseForVA<T>::arr_) {
    delete[] BaseForVA<T>::arr_;
  }
  BaseForVA<T>::size_ = 0;
  capacity_ = 0;
  BaseForVA<T>::arr_ = nullptr;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (BaseForVA<T>::size_ == BaseForVA<T>::max_size()) {
    throw std::logic_error(
        "Error: insert(iterator pos, const_reference value): The container "
        "size is alredy maximum");
  }
  if (this->empty() || pos == BaseForVA<T>::end()) {
    push_back(value);
    pos = this->end();
    --pos;
  } else {
    int index = pos - BaseForVA<T>::arr_;
    for (int i = BaseForVA<T>::size_ - 1; i >= index; --i) {
      BaseForVA<T>::arr_[i + 1] = BaseForVA<T>::arr_[i];
    }
    BaseForVA<T>::arr_[index] = value;
    BaseForVA<T>::size_++;
  }
  return pos;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  if (BaseForVA<T>::empty()) {
    throw std::logic_error(
        "Error: erase(iterator pos): The container is empty");
  }
  if (pos == BaseForVA<T>::end()) {
    throw std::logic_error("Error: erase(iterator pos): The pointer is nulptr");
  }
  if (*pos == BaseForVA<T>::back()) {
    pop_back();
  } else {
    size_t index = pos - BaseForVA<T>::arr_;
    --BaseForVA<T>::size_;
    for (size_t i = index; i != BaseForVA<T>::size_; ++i) {
      BaseForVA<T>::arr_[i] = BaseForVA<T>::arr_[i + 1];
    }
  }
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (BaseForVA<T>::size_ >= BaseForVA<T>::max_size()) {
    throw std::logic_error(
        "Error: push_back(const_reference value): new capacity size is bigger "
        "than maximum possible number of elements");
  }
  if (BaseForVA<T>::size_ >= capacity_) {
    realloc(BaseForVA<T>::size_ * 2);
  }
  BaseForVA<T>::arr_[BaseForVA<T>::size_] = value;
  BaseForVA<T>::size_++;
}

template <typename T>
void Vector<T>::pop_back() {
  if (BaseForVA<T>::empty()) {
    throw std::logic_error(
        "Error: erase(iterator pos): The container is empty");
  }
  BaseForVA<T>::arr_[BaseForVA<T>::size_ - 1] = 0;
  BaseForVA<T>::size_--;
}

template <typename T>
void Vector<T>::swap(Vector &other) {
  BaseForVA<T>::swap(other);
  std::swap(capacity_, other.capacity_);
}

//  ============================================================  //
//  ====================== BONUS: emplace ======================  //
//  ============================================================  //

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  s21::Vector<int> vctr{args...};
  iterator tmp = (iterator)pos;
  for (auto value : vctr) {
    tmp = insert(tmp, value);
    ++tmp;
  }
  --tmp;
  return tmp;
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args &&...args) {
  emplace(this->cend(), args...);
}

//  ============================================================  //
//  ================= Vector Additional methods ================  //
//  ============================================================  //

template <typename T>
void Vector<T>::realloc(size_type size) {
  size_type tmp = BaseForVA<T>::size_;
  value_type *buff = new value_type[size + 1]{0};
  for (size_t i = 0; i < tmp; i++) {
    buff[i] = BaseForVA<T>::arr_[i];
  }
  if (buff) {
    delete[] BaseForVA<T>::arr_;
    BaseForVA<T>::arr_ = buff;
    BaseForVA<T>::size_ = tmp;
    capacity_ = size;
  }
}
}  // namespace s21
