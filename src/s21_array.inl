namespace s21 {
template <typename T, size_t N>
void Array<T, N>::fill(const_reference value) {
  if (BaseForVA<T>::empty()) {
    throw std::logic_error(
        "Error: fill(const_reference value): The container is empty");
  }
  for (size_t i = 0; i < BaseForVA<T>::size_; i++) {
    BaseForVA<T>::arr_[i] = value;
  }
}
}  // namespace s21
