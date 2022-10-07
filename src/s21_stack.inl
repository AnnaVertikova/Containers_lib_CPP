namespace s21 {
//  ============================================================  //
//  ====================== Stack Functions =====================  //
//  ============================================================  //

template <typename T>
Stack<T>::Stack() : BaseForLSQ<T>::BaseForLSQ() {}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items)
    : BaseForLSQ<T>::BaseForLSQ(items) {}

//  ============================================================  //
//  ==================== Stack Element access ==================  //
//  ============================================================  //

template <typename T>
typename Stack<T>::const_reference Stack<T>::top() {
  return BaseForLSQ<T>::back();
}

//  ============================================================  //
//  ====================== BONUS: emplace ======================  //
//  ============================================================  //

template <typename T>
template <typename... Args>
void Stack<T>::emplace_front(Args &&...args) {
  value_type arr[sizeof...(Args)] = {args...};
  for (auto value : arr) {
    BaseForLSQ<T>::push(value);
  }
}
}  // namespace s21
