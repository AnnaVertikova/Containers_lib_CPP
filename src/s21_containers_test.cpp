#include "s21_containers.h"

#include <gtest/gtest.h>

#include "s21_containersplus.h"

TEST(list_functions, list_functions_default_constructor_Test) {
  s21::List<int> lst1;
  ASSERT_EQ(lst1.size(), 0);
}

TEST(list_functions, list_functions_parameterized_constructor_Test1) {
  s21::List<int> lst1(3);
  ASSERT_EQ(lst1.size(), 3);
}

TEST(list_functions, list_functions_initializer_list_constructor_Test1) {
  s21::List<int> lst1{1, 2, 3, 4, 5};
  ASSERT_EQ(lst1.size(), 5);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 5);
}

TEST(list_functions, list_functions_initializer_list_constructor_Test2) {
  s21::List<double> lst1{1.1, 2.2, 3.3};
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.front(), 1.1);
  ASSERT_EQ(lst1.back(), 3.3);
}

TEST(list_functions, list_functions_copy_constructor_Test) {
  s21::List<int> lst1(5);
  s21::List<int> lst2(lst1);
  ASSERT_EQ(lst2.size(), 5);
}

TEST(list_functions, list_functions_move_constructor_Test) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int> lst2(std::move(lst1));
  ASSERT_EQ(lst1.size(), 0);
  ASSERT_EQ(lst2.size(), 3);
  ASSERT_EQ(lst2.back(), 3);
}

TEST(list_element_access, list_element_access_front_Test1) {
  s21::List<int> lst1{1, 2, 3};
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.front(), 1);
}

TEST(list_element_access, list_element_access_back_Test1) {
  s21::List<int> lst1{1, 2, 3};
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_iterators, list_iterators_pointer_Test1) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.begin());
  ASSERT_EQ(*it, 1);
}

TEST(list_iterators, list_iterators_pointer_Test2) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.end());
  --it;
  ASSERT_EQ(*it, 3);
}

TEST(list_iterators, list_iterators_increment_Test1) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.begin());
  ++it;
  ASSERT_EQ(it.pPos_->data_, 2);
}

TEST(list_iterators, list_iterators_decrement_Test1) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.end());
  --it;
  ASSERT_EQ(it.pPos_->data_, 3);
}

TEST(list_iterators, list_iterators_equality_Test) {
  s21::List<int> lst1{1, 2};
  s21::List<int>::iterator itBegin(lst1.begin());
  s21::List<int>::iterator itEnd(lst1.end());
  ++itBegin;
  --itEnd;
  ASSERT_TRUE(itBegin == itEnd);
}

TEST(list_iterators, list_iterators_inequality_Test) {
  s21::List<int> lst1{1, 2};
  s21::List<int>::iterator itBegin(lst1.begin());
  s21::List<int>::iterator itEnd(lst1.end());
  ASSERT_TRUE(itBegin != itEnd);
}

TEST(list_iterators, list_iterators_begin_Test1) {
  s21::List<int> lst1{1, 2};
  s21::List<int>::iterator it(lst1.begin());
  ASSERT_EQ(it.pPos_->data_, 1);
}

TEST(list_iterators, list_iterators_begin_Test2) {
  s21::List<int> lst1;
  s21::List<int>::iterator it(lst1.begin());
  ASSERT_EQ(it.pPos_, nullptr);
}

TEST(list_iterators, list_iterators_end_Test1) {
  s21::List<int> lst1{1, 2};
  s21::List<int>::iterator it(lst1.end());
  ASSERT_EQ(it.pPos_, nullptr);
}

TEST(list_iterators, list_iterators_end_Test2) {
  s21::List<int> lst1;
  s21::List<int>::iterator it(lst1.end());
  ASSERT_EQ(it.pPos_, nullptr);
}

TEST(list_iterators, const_list_iterators_cbegin_Test1) {
  s21::List<int> lst1{1, 2};
  s21::List<int>::const_iterator it(lst1.cbegin());
  ASSERT_EQ(it.pPos_->data_, 1);
}

TEST(list_iterators, const_list_iteratorss_cbegin_Test2) {
  s21::List<int> lst1;
  s21::List<int>::const_iterator it(lst1.cbegin());
  ASSERT_EQ(it.pPos_, nullptr);
}

TEST(list_iterators, list_iterators_cend_Test1) {
  s21::List<int> lst1{1, 2};
  s21::List<int>::const_iterator it(lst1.cend());
  ASSERT_EQ(it.pPos_, nullptr);
}

TEST(list_iterators, const_list_iterators_cend_Test2) {
  s21::List<int> lst1;
  s21::List<int>::const_iterator it(lst1.cend());
  ASSERT_EQ(it.pPos_, nullptr);
}

TEST(list_capacity, list_capacity_empty_Test1) {
  s21::List<int> lst1;
  ASSERT_TRUE(lst1.empty());
}

TEST(list_capacity, list_capacity_empty_Test2) {
  s21::List<int> lst1;
  lst1.push_back(1);
  ASSERT_FALSE(lst1.empty());
}

TEST(list_capacity, list_capacity_size_Test1) {
  s21::List<int> lst1{1, 2, 3};
  ASSERT_EQ(lst1.size(), 3);
}

TEST(list_capacity, list_capacity_size_Test2) {
  s21::List<int> lst1;
  ASSERT_EQ(lst1.size(), 0);
}

TEST(list_capacity, list_capacity_max_size_Test) {
  s21::List<int> lst1;
  ASSERT_EQ(lst1.max_size(), 384307168202282325);
}

TEST(list_modifiers, list_modifiers_clear_Test) {
  s21::List<int> lst1{1, 2, 3};
  lst1.clear();
  ASSERT_EQ(lst1.size(), 0);
}

TEST(list_modifiers, list_modifiers_insert_Test1) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.begin());
  lst1.insert(it, 0);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.front(), 0);
}

TEST(list_modifiers, list_modifiers_insert_Test2) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.begin());
  ++it;
  it = lst1.insert(it, 0);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(it.pPos_->data_, 0);
}

TEST(list_modifiers, list_modifiers_erase_Test1) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.begin());
  lst1.erase(it);
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(lst1.front(), 2);
}

TEST(list_modifiers, list_modifiers_erase_Test3) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.end());
  --it;
  lst1.erase(it);
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(lst1.back(), 2);
}

TEST(list_modifiers, list_modifiers_erase_Test4) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.end());
  --it;
  --it;
  lst1.erase(it);
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, list_modifiers_erase_Test5) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int>::iterator it(lst1.begin());
  ++it;
  lst1.erase(it);
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, list_modifiers_push_back_Test) {
  s21::List<int> lst1{1, 2, 3};
  lst1.push_back(4);
  lst1.push_back(5);
  ASSERT_EQ(lst1.size(), 5);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 5);
}

TEST(list_modifiers, list_modifiers_pop_back_Test1) {
  s21::List<int> lst1{1, 2, 3};
  lst1.pop_back();
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(lst1.back(), 2);
}

TEST(list_modifiers, list_modifiers_push_front_Test1) {
  s21::List<int> lst1;
  lst1.push_front(0);
  ASSERT_EQ(lst1.size(), 1);
  ASSERT_EQ(lst1.front(), 0);
  ASSERT_EQ(lst1.back(), 0);
}

TEST(list_modifiers, list_modifiers_push_front_Test2) {
  s21::List<int> lst1{1, 2, 3};
  lst1.push_front(0);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.front(), 0);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, list_modifiers_pop_front_Test1) {
  s21::List<int> lst1{1, 2, 3};
  lst1.pop_front();
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(lst1.front(), 2);
}

TEST(list_modifiers, list_modifiers_swap_Test) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int> lst2{4, 5};
  lst1.swap(lst2);
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(lst1.front(), 4);
  ASSERT_EQ(lst1.back(), 5);
  ASSERT_EQ(lst2.size(), 3);
  ASSERT_EQ(lst2.front(), 1);
  ASSERT_EQ(lst2.back(), 3);
}

TEST(list_modifiers, list_modifiers_merge_Test1) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int> lst2{4, 5};
  lst1.merge(lst2);
  ASSERT_EQ(lst1.size(), 5);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 5);
}

TEST(list_modifiers, list_modifiers_merge_Test2) {
  s21::List<int> lst1{3, 1, 2};
  s21::List<int> lst2{5, 4};
  lst1.merge(lst2);
  ASSERT_EQ(lst1.size(), 5);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 5);
}

TEST(list_modifiers, list_modifiers_splice_Test1) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int> lst2{4, 5, 6, 7};
  s21::List<int>::const_iterator it(lst1.cbegin());
  ++it;
  lst1.splice(it, lst2);
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, list_modifiers_splice_Test2) {
  s21::List<int> lst1{1, 2, 3};
  s21::List<int> lst2{4, 5, 6, 7};
  s21::List<int>::const_iterator it(lst1.cend());
  lst1.splice(it, lst2);
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 7);
}

TEST(list_modifiers, list_modifiers_reverse_Test1) {
  s21::List<int> lst1{1, 2, 3, 4, 5};
  lst1.reverse();
  ASSERT_EQ(lst1.size(), 5);
  ASSERT_EQ(lst1.front(), 5);
  ASSERT_EQ(lst1.back(), 1);
}

TEST(list_modifiers, list_modifiers_reverse_Test2) {
  s21::List<int> lst1{1, 2, 3, 4};
  lst1.reverse();
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.front(), 4);
  ASSERT_EQ(lst1.back(), 1);
}

TEST(list_modifiers, list_modifiers_unique_Test1) {
  s21::List<int> lst1;
  lst1.push_back(1);
  lst1.push_back(2);
  lst1.push_back(1);
  lst1.push_back(3);
  lst1.push_back(2);
  lst1.push_back(1);
  lst1.push_back(3);
  lst1.push_back(2);
  lst1.push_back(3);
  lst1.push_back(2);
  lst1.push_back(1);
  lst1.push_back(3);
  lst1.push_back(3);
  lst1.push_back(1);
  lst1.unique();
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, list_modifiers_sort_Test1) {
  s21::List<int> lst1;
  lst1.push_back(3);
  lst1.push_back(1);
  lst1.push_back(2);
  lst1.push_back(5);
  lst1.push_back(4);
  lst1.sort();
  ASSERT_EQ(lst1.size(), 5);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 5);
}

TEST(list_modifiers, bounus_emplace_iterator_Test1) {
  s21::List<int> lst1;
  s21::List<int>::const_iterator itC(lst1.cbegin());
  s21::List<int>::iterator it;
  it = lst1.emplace(itC, 1, 2, 3);
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);
  ASSERT_EQ(*it, 3);
}

TEST(list_modifiers, bounus_emplace_iterator_Test2) {
  s21::List<int> lst1{7, 8, 9};
  s21::List<int>::const_iterator itC(lst1.cbegin());
  s21::List<int>::iterator it;
  it = lst1.emplace(itC, 1, 2, 3);
  ASSERT_EQ(lst1.size(), 6);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 9);
}

TEST(list_modifiers, bounus_emplace_back_Test1) {
  s21::List<int> lst1;
  lst1.emplace_back(1, 2, 3);
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, bounus_emplace_back_Test2) {
  s21::List<int> lst1{9, 8, 7};
  lst1.emplace_back(1, 2, 3);
  ASSERT_EQ(lst1.size(), 6);
  ASSERT_EQ(lst1.front(), 9);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, bounus_emplace_front_Test1) {
  s21::List<int> lst1;
  lst1.emplace_front(1, 2, 3);
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(list_modifiers, bounus_emplace_front_Test2) {
  s21::List<int> lst1{9, 8, 7};
  lst1.emplace_front(1, 2, 3);
  ASSERT_EQ(lst1.size(), 6);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 7);
}

TEST(queue_functions, queue_functions_default_constructor_Test) {
  s21::Queue<int> q1;
  ASSERT_EQ(q1.size(), 0);
}

TEST(queue_functions, queue_functions_initializer_list_constructor_Test1) {
  s21::Queue<int> q1{1, 2, 3, 4, 5};
  ASSERT_EQ(q1.size(), 5);
  ASSERT_EQ(q1.front(), 1);
  ASSERT_EQ(q1.back(), 5);
}

TEST(queue_functions, queue_functions_initializer_list_constructor_Test2) {
  s21::Queue<double> q1{1.1, 2.2, 3.3};
  ASSERT_EQ(q1.size(), 3);
  ASSERT_EQ(q1.front(), 1.1);
  ASSERT_EQ(q1.back(), 3.3);
}

TEST(queue_functions, queue_functions_copy_constructor_Test) {
  s21::Queue<int> q1{1, 2, 3, 4, 5};
  s21::Queue<int> q2(q1);
  ASSERT_EQ(q2.size(), 5);
}

TEST(queue_functions, queue_functions_move_constructor_Test) {
  s21::Queue<int> q1{1, 2, 3};
  s21::Queue<int> q2(std::move(q1));
  ASSERT_EQ(q1.size(), 0);
  ASSERT_EQ(q2.size(), 3);
  ASSERT_EQ(q2.back(), 3);
}

TEST(queue_element_access, queue_element_access_front_Test1) {
  s21::Queue<int> q1{1, 2, 3};
  ASSERT_EQ(q1.size(), 3);
  ASSERT_EQ(q1.front(), 1);
}

TEST(queue_element_access, queue_element_access_back_Test1) {
  s21::Queue<int> q1{1, 2, 3};
  ASSERT_EQ(q1.size(), 3);
  ASSERT_EQ(q1.back(), 3);
}

TEST(queue_capacity, queue_capacity_empty_Test1) {
  s21::Queue<int> q1;
  ASSERT_TRUE(q1.empty());
}

TEST(queue_capacity, queue_capacity_empty_Test2) {
  s21::Queue<int> q1;
  q1.push(1);
  ASSERT_FALSE(q1.empty());
}

TEST(queue_capacity, queue_capacity_size_Test1) {
  s21::Queue<int> q1{1, 2, 3};
  ASSERT_EQ(q1.size(), 3);
}

TEST(queue_capacity, queue_capacity_size_Test2) {
  s21::Queue<int> q1;
  ASSERT_EQ(q1.size(), 0);
}

TEST(queue_modifiers, queue_modifiers_push_Test) {
  s21::Queue<int> q1{1, 2, 3};
  q1.push(4);
  q1.push(5);
  ASSERT_EQ(q1.size(), 5);
  ASSERT_EQ(q1.front(), 1);
  ASSERT_EQ(q1.back(), 5);
}

TEST(queue_modifiers, queue_modifiers_pop_Test1) {
  s21::Queue<int> q1{1, 2, 3};
  q1.pop();
  ASSERT_EQ(q1.size(), 2);
  ASSERT_EQ(q1.front(), 2);
}

TEST(queue_modifiers, queue_modifiers_swap_Test) {
  s21::Queue<int> q1{1, 2, 3};
  s21::Queue<int> q2{4, 5};
  q1.swap(q2);
  ASSERT_EQ(q1.size(), 2);
  ASSERT_EQ(q1.front(), 4);
  ASSERT_EQ(q1.back(), 5);
  ASSERT_EQ(q2.size(), 3);
  ASSERT_EQ(q2.front(), 1);
  ASSERT_EQ(q2.back(), 3);
}

TEST(queue_modifiers, bounus_emplace_back_Test1) {
  s21::Queue<int> q1;
  q1.emplace_back(1, 2, 3);
  ASSERT_EQ(q1.size(), 3);
  ASSERT_EQ(q1.front(), 1);
  ASSERT_EQ(q1.back(), 3);
}

TEST(queue_modifiers, bounus_emplace_back_Test2) {
  s21::Queue<int> q1{1, 2, 3};
  q1.emplace_back(7, 8, 9);
  ASSERT_EQ(q1.size(), 6);
  ASSERT_EQ(q1.front(), 1);
  ASSERT_EQ(q1.back(), 9);
}

TEST(stack_functions, stack_functions_default_constructor_Test) {
  s21::Stack<int> st1;
  ASSERT_EQ(st1.size(), 0);
}

TEST(stack_functions, stack_functions_initializer_list_constructor_Test1) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  ASSERT_EQ(st1.size(), 5);
  ASSERT_EQ(st1.top(), 5);
}

TEST(stack_functions, stack_functions_initializer_list_constructor_Test2) {
  s21::Stack<double> st1{1.1, 2.2, 3.3};
  ASSERT_EQ(st1.size(), 3);
  ASSERT_EQ(st1.top(), 3.3);
}

TEST(stack_functions, stack_functions_copy_constructor_Test) {
  s21::Stack<int> st1{1, 2, 3};
  s21::Stack<int> st2(st1);
  ASSERT_EQ(st1.size(), st2.size());
  ASSERT_EQ(st1.top(), 3);
}

TEST(stack_functions, stack_functions_move_constructor_Test) {
  s21::Stack<int> st1{1, 2, 3};
  s21::Stack<int> st2(std::move(st1));
  ASSERT_EQ(st1.size(), 0);
  ASSERT_EQ(st2.size(), 3);
  ASSERT_EQ(st2.top(), 3);
}

TEST(stack_element_access, stack_element_access_top_Test1) {
  s21::Stack<int> st1{1, 2, 3};
  ASSERT_EQ(st1.size(), 3);
  ASSERT_EQ(st1.top(), 3);
}

TEST(stack_capacity, stack_capacity_empty_Test1) {
  s21::Stack<int> st1;
  ASSERT_TRUE(st1.empty());
}

TEST(stack_capacity, stack_capacity_empty_Test2) {
  s21::Stack<int> st1;
  st1.push(1);
  ASSERT_FALSE(st1.empty());
}

TEST(stack_capacity, stack_capacity_size_Test1) {
  s21::Stack<int> st1{1, 2, 3};
  ASSERT_EQ(st1.size(), 3);
}

TEST(stack_capacity, stack_capacity_size_Test2) {
  s21::Stack<int> st1;
  ASSERT_EQ(st1.size(), 0);
}

TEST(stack_modifiers, stack_modifiers_push_Test) {
  s21::Stack<int> st1{1, 2, 3};
  st1.push(4);
  st1.push(5);
  ASSERT_EQ(st1.size(), 5);
  ASSERT_EQ(st1.top(), 5);
}

TEST(stack_modifiers, stack_modifiers_pop_Test1) {
  s21::Stack<int> st1{1, 2, 3};
  st1.pop();
  ASSERT_EQ(st1.size(), 2);
  ASSERT_EQ(st1.top(), 2);
}

TEST(stack_modifiers, stack_modifiers_swap_Test) {
  s21::Stack<int> st1{1, 2, 3};
  s21::Stack<int> st2{4, 5};
  st1.swap(st2);
  ASSERT_EQ(st1.size(), 2);
  ASSERT_EQ(st1.top(), 5);
  ASSERT_EQ(st2.size(), 3);
  ASSERT_EQ(st2.top(), 3);
}

TEST(stack_modifiers, bounus_emplace_front_Test1) {
  s21::Stack<int> st1;
  st1.emplace_front(1, 2, 3);
  ASSERT_EQ(st1.size(), 3);
  ASSERT_EQ(st1.top(), 3);
}

TEST(stack_modifiers, bounus_emplace_front_Test2) {
  s21::Stack<int> st1{1, 2, 3};
  st1.emplace_front(7, 8, 9);
  ASSERT_EQ(st1.size(), 6);
  ASSERT_EQ(st1.top(), 9);
}

TEST(vector_functions, vector_functions_default_constructor_Test) {
  s21::Vector<int> vctr1;
  ASSERT_EQ(vctr1.size(), 0);
}

TEST(vector_functions, vector_functions_parameterized_constructor_Test1) {
  s21::Vector<int> vctr1(3);
  ASSERT_EQ(vctr1.size(), 3);
}

TEST(vector_functions, vector_functions_initializer_list_constructor_Test1) {
  s21::Vector<int> vctr1{1, 2, 3, 4, 5};
  ASSERT_EQ(vctr1[0], 1);
  ASSERT_EQ(vctr1[3], 4);
  ASSERT_EQ(vctr1.size(), 5);
  ASSERT_EQ(vctr1.front(), 1);
  ASSERT_EQ(vctr1.back(), 5);
}

TEST(vector_functions, vector_functions_initializer_list_constructor_Test2) {
  s21::Vector<double> vctr1{1.1, 2.2, 3.3};
  ASSERT_EQ(vctr1.size(), 3);
  ASSERT_EQ(vctr1.front(), 1.1);
  ASSERT_EQ(vctr1.back(), 3.3);
}

TEST(vector_functions, vector_functions_copy_constructor_Test1) {
  s21::Vector<int> vctr1(5);
  s21::Vector<int> vctr2(vctr1);
  ASSERT_TRUE(vctr1.size() == vctr2.size());
  ASSERT_TRUE(vctr1.capacity() == vctr2.capacity());
}

TEST(vector_functions, vector_functions_copy_constructor_Test2) {
  s21::Vector<int> vctr1;
  s21::Vector<int> vctr2(vctr1);
  ASSERT_TRUE(vctr1.size() == vctr2.size());
  ASSERT_TRUE(vctr1.capacity() == vctr2.capacity());
}

TEST(vector_functions, vector_functions_move_constructor_Test) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int> vctr2(std::move(vctr1));
  ASSERT_EQ(vctr2.front(), 1);
  ASSERT_EQ(vctr2.back(), 3);
}

TEST(vector_element_access, vector_element_access_at_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  ASSERT_EQ(vctr1.at(0), 1);
  ASSERT_EQ(vctr1.at(1), 2);
  ASSERT_EQ(vctr1.at(2), 3);
}

TEST(vector_element_access, vector_element_access_operator_sqbr_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  ASSERT_EQ(vctr1[0], 1);
  ASSERT_EQ(vctr1[1], 2);
  ASSERT_EQ(vctr1[2], 3);
}

TEST(vector_element_access, vector_element_access_front_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  ASSERT_EQ(vctr1.size(), 3);
  ASSERT_EQ(vctr1.front(), 1);
}

TEST(vector_element_access, vector_element_access_back_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  ASSERT_EQ(vctr1.back(), 3);
}

TEST(vector_element_access, vector_element_access_data_Test1) {
  s21::Vector<int> vctr1{1};
  ASSERT_EQ(vctr1.data(), vctr1.data());
}

TEST(vector_iterators, vector_iterators_begin_Test1) {
  s21::Vector<int> vctr1{1, 2};
  s21::Vector<int>::iterator it(vctr1.begin());
  ASSERT_EQ(*it, 1);
}

TEST(vector_iterators, vector_iterators_begin_Test2) {
  s21::Vector<int> vctr1;
  s21::Vector<int>::iterator it(vctr1.begin());
  ASSERT_EQ(it, vctr1.end());
}

TEST(vector_iterators, vector_iterators_end_Test1) {
  s21::Vector<int> vctr1{1, 2};
  s21::Vector<int>::iterator it(vctr1.end());
  --it;
  ASSERT_EQ(*it, vctr1.back());
}

TEST(vector_iterators, vector_iterators_end_Test2) {
  s21::Vector<int> vctr1;
  s21::Vector<int>::iterator it(vctr1.end());
  ASSERT_EQ(it, vctr1.end());
}

TEST(vector_capacity, vector_capacity_empty_Test1) {
  s21::Vector<int> vctr1;
  ASSERT_TRUE(vctr1.empty());
}

TEST(vector_capacity, vector_capacity_empty_Test2) {
  s21::Vector<int> vctr1{1, 2};
  ASSERT_FALSE(vctr1.empty());
}

TEST(vector_capacity, vector_capacity_size_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  ASSERT_EQ(vctr1.size(), 3);
}

TEST(vector_capacity, vector_capacity_size_Test2) {
  s21::Vector<int> vctr1;
  ASSERT_EQ(vctr1.size(), 0);
}

TEST(vector_capacity, vector_capacity_max_size_Test) {
  s21::Vector<int> vctr1;
  ASSERT_EQ(vctr1.max_size(), 2305843009213693951);
}

TEST(vector_capacity, vector_capacity_reserve_Test1) {
  s21::Vector<int> vctr1;
  vctr1.reserve(1);
  ASSERT_EQ(vctr1.capacity(), 1);
}

TEST(vector_capacity, vector_capacity_reserve_Test2) {
  s21::Vector<int> vctr1{1, 2, 3};
  vctr1.reserve(9);
  ASSERT_EQ(vctr1.capacity(), 9);
}

TEST(vector_capacity, vector_capacity_reserve_Test3) {
  s21::Vector<int> vctr1;
  vctr1.reserve(3);
  ASSERT_EQ(vctr1.capacity(), 3);
}

TEST(vector_capacity, vector_capacity_capacity_Test1) {
  s21::Vector<int> vctr1;
  ASSERT_EQ(vctr1.capacity(), 1);
}

TEST(vector_capacity, vector_capacity_capacity_Test2) {
  s21::Vector<int> vctr1{1};
  ASSERT_EQ(vctr1.capacity(), 2);
}

TEST(vector_capacity, vector_capacity_capacity_Test3) {
  s21::Vector<int> vctr1(4);
  ASSERT_EQ(vctr1.capacity(), 8);
}

TEST(vector_capacity, vector_capacity_shrink_to_fit_Test1) {
  s21::Vector<int> vctr1(3);
  vctr1.shrink_to_fit();
  ASSERT_EQ(vctr1.capacity(), 3);
}

TEST(vector_capacity, vector_capacity_shrink_to_fit_Test2) {
  s21::Vector<int> vctr1{1, 2, 3};
  vctr1.reserve(11);
  vctr1.shrink_to_fit();
  ASSERT_EQ(vctr1.capacity(), 3);
}

TEST(vector_modifiers, vector_modifiers_clear_Test) {
  s21::Vector<int> vctr1{1, 2, 3};
  vctr1.clear();
  ASSERT_EQ(vctr1.size(), 0);
  ASSERT_EQ(vctr1.capacity(), 0);
}

TEST(vector_modifiers, vector_modifiers_insert_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int>::iterator it(vctr1.begin());
  vctr1.insert(it, 0);
  ASSERT_EQ(vctr1.size(), 4);
  ASSERT_EQ(vctr1.front(), 0);
}

TEST(vector_modifiers, vector_modifiers_insert_Test2) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int>::iterator it(vctr1.begin());
  ++it;
  it = vctr1.insert(it, 0);
  ASSERT_EQ(vctr1.size(), 4);
  ASSERT_EQ(vctr1.front(), 1);
  ASSERT_EQ(*it, 0);
}

TEST(vector_modifiers, vector_modifiers_insert_Test3) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int>::iterator it(vctr1.end());
  it = vctr1.insert(it, 4);
  ASSERT_EQ(vctr1.size(), 4);
  ASSERT_EQ(vctr1.back(), 4);
  ASSERT_EQ(*it, 4);
}

TEST(vector_modifiers, vector_modifiers_erase_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int>::iterator it(vctr1.begin());
  vctr1.erase(it);
  ASSERT_EQ(vctr1.size(), 2);
  ASSERT_EQ(vctr1.front(), 2);
}

TEST(vector_modifiers, vector_modifiers_erase_Test3) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int>::iterator it(vctr1.end());
  --it;
  vctr1.erase(it);
  ASSERT_EQ(vctr1.size(), 2);
  ASSERT_EQ(vctr1.back(), 2);
}

TEST(vector_modifiers, vector_modifiers_erase_Test4) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int>::iterator it(vctr1.end());
  --it;
  --it;
  vctr1.erase(it);
  ASSERT_EQ(vctr1.size(), 2);
  ASSERT_EQ(vctr1.back(), 3);
}

TEST(vector_modifiers, vector_modifiers_erase_Test5) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int>::iterator it(vctr1.begin());
  ++it;
  vctr1.erase(it);
  ASSERT_EQ(vctr1.size(), 2);
  ASSERT_EQ(vctr1.front(), 1);
  ASSERT_EQ(vctr1.back(), 3);
}

TEST(vector_modifiers, vector_modifiers_push_back_Test1) {
  s21::Vector<int> vctr1;
  vctr1.push_back(1);
  vctr1.push_back(2);
  vctr1.push_back(3);
  ASSERT_EQ(vctr1.size(), 3);
  ASSERT_EQ(vctr1.capacity(), 4);
  ASSERT_EQ(vctr1.front(), 1);
  ASSERT_EQ(vctr1.back(), 3);
}

TEST(vector_modifiers, vector_modifiers_pop_back_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  vctr1.pop_back();
  ASSERT_EQ(vctr1.size(), 2);
  ASSERT_EQ(vctr1.back(), 2);
}

TEST(vector_modifiers, vector_modifiers_swap_Test1) {
  s21::Vector<int> vctr1{1, 2, 3};
  s21::Vector<int> vctr2{4, 5};
  vctr1.swap(vctr2);
  ASSERT_EQ(vctr1.size(), 2);
  ASSERT_EQ(vctr1.front(), 4);
  ASSERT_EQ(vctr1.back(), 5);
  ASSERT_EQ(vctr2.size(), 3);
  ASSERT_EQ(vctr2.front(), 1);
  ASSERT_EQ(vctr2.back(), 3);
}

TEST(vector_modifiers, bounus_emplace_iterator_Test1) {
  s21::Vector<int> vctr1;
  s21::Vector<int>::const_iterator itC(vctr1.cbegin());
  s21::Vector<int>::iterator it;
  it = vctr1.emplace(itC, 1, 2, 3);
  ASSERT_EQ(vctr1.size(), 3);
  ASSERT_EQ(vctr1.front(), 1);
  ASSERT_EQ(vctr1.back(), 3);
  ASSERT_EQ(*it, 3);
}

TEST(vector_modifiers, bounus_emplace_iterator_Test2) {
  s21::Vector<int> vctr1{7, 8, 9};
  s21::Vector<int>::const_iterator itC(vctr1.cbegin());
  vctr1.emplace(itC, 1, 2, 3);
  ASSERT_EQ(vctr1.size(), 6);
  ASSERT_EQ(vctr1.front(), 1);
  ASSERT_EQ(vctr1.back(), 9);
}

TEST(vector_modifiers, bounus_emplace_back_Test1) {
  s21::Vector<int> vctr1;
  vctr1.emplace_back(1, 2, 3);
  ASSERT_EQ(vctr1.size(), 3);
  ASSERT_EQ(vctr1.front(), 1);
  ASSERT_EQ(vctr1.back(), 3);
}

TEST(vector_modifiers, bounus_emplace_back_Test2) {
  s21::Vector<int> vctr1{9, 8, 7};
  vctr1.emplace_back(1, 2, 3);
  ASSERT_EQ(vctr1.size(), 6);
  ASSERT_EQ(vctr1.front(), 9);
  ASSERT_EQ(vctr1.back(), 3);
}

TEST(array_functions, array_functions_default_constructor_Test) {
  s21::Array<int, 3> arr1;
  arr1.at(0);
  ASSERT_EQ(arr1.size(), 3);
}

TEST(array_functions, array_functions_initializer_list_constructor_Test1) {
  s21::Array<int, 5> arr1{1, 2, 3, 4, 5};
  ASSERT_EQ(arr1.size(), 5);
  ASSERT_EQ(arr1.at(0), 1);
  ASSERT_EQ(arr1.at(4), 5);
}

TEST(array_functions, array_functions_initializer_list_constructor_Test2) {
  s21::Array<double, 3> arr1{1.1, 2.2, 3.3};
  ASSERT_EQ(arr1.size(), 3);
  ASSERT_EQ(arr1.at(0), 1.1);
  ASSERT_EQ(arr1.at(2), 3.3);
}

TEST(array_functions, array_functions_copy_constructor_Test) {
  s21::Array<int, 3> arr1{1, 2, 3};
  s21::Array<int, 3> arr2(arr1);
  ASSERT_EQ(arr1.size(), 3);
  ASSERT_EQ(arr1.at(0), 1);
  ASSERT_EQ(arr1.at(2), 3);
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr2.at(0), 1);
  ASSERT_EQ(arr2.at(2), 3);
}

TEST(array_functions, array_functions_move_constructor_Test) {
  s21::Array<int, 3> arr1{1, 2, 3};
  s21::Array<int, 3> arr2(std::move(arr1));
  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr2.at(0), 1);
  ASSERT_EQ(arr2.at(1), 2);
  ASSERT_EQ(arr2.at(2), 3);
}

TEST(array_element_access, array_element_access_at_Test1) {
  s21::Array<int, 3> arr1{1, 2, 3};
  ASSERT_EQ(arr1.at(0), 1);
  ASSERT_EQ(arr1.at(1), 2);
  ASSERT_EQ(arr1.at(2), 3);
}

TEST(array_element_access, array_element_access_operator_sqbr_Test1) {
  s21::Array<int, 3> arr1{1, 2, 3};
  ASSERT_EQ(arr1[0], 1);
  ASSERT_EQ(arr1[1], 2);
  ASSERT_EQ(arr1[2], 3);
}

TEST(array_element_access, array_element_access_front_Test1) {
  s21::Array<int, 3> arr1{1, 2, 3};
  ASSERT_EQ(arr1.size(), 3);
  ASSERT_EQ(arr1.front(), 1);
}

TEST(array_element_access, array_element_access_back_Test1) {
  s21::Array<int, 3> arr1{1, 2, 3};
  ASSERT_EQ(arr1.back(), 3);
}

TEST(array_element_access, array_element_access_data_Test1) {
  s21::Array<int, 1> arr1{1};
  ASSERT_EQ(arr1.data(), arr1.data());
}

TEST(array_iterators, array_iterators_begin_Test1) {
  s21::Array<int, 2> arr1{1, 2};
  s21::Array<int, 2>::iterator it(arr1.begin());
  ASSERT_EQ(*it, 1);
}

TEST(array_iterators, array_iterators_begin_Test2) {
  s21::Array<int, 0> arr1;
  s21::Array<int, 0>::iterator it(arr1.begin());
  ASSERT_EQ(it, arr1.end());
}

TEST(array_iterators, array_iterators_end_Test1) {
  s21::Array<int, 2> arr1{1, 2};
  s21::Array<int, 2>::iterator it(arr1.end());
  s21::Array<int, 2>::iterator itB(arr1.begin());
  ++itB;
  ++itB;
  ASSERT_EQ(it, itB);
}

TEST(array_iterators, array_iterators_end_Test2) {
  s21::Array<int, 0> arr1;
  s21::Array<int, 0>::iterator it(arr1.end());
  ASSERT_EQ(it, arr1.end());
}

TEST(array_capacity, array_capacity_empty_Test1) {
  s21::Array<int, 0> arr1;
  ASSERT_TRUE(arr1.empty());
}

TEST(array_capacity, array_capacity_empty_Test2) {
  s21::Array<int, 2> arr1{1, 2};
  ASSERT_FALSE(arr1.empty());
}

TEST(array_capacity, array_capacity_size_Test1) {
  s21::Array<int, 3> arr1{1, 2, 3};
  ASSERT_EQ(arr1.size(), 3);
}

TEST(array_capacity, array_capacity_max_size_Test) {
  s21::Array<int, 1> arr1;
  ASSERT_EQ(arr1.max_size(), 2305843009213693951);
}

TEST(array_modifiers, array_modifiers_swap_Test) {
  s21::Array<int, 3> arr1{1, 2, 3};
  s21::Array<int, 3> arr2{4, 5, 6};
  arr1.swap(arr2);
  ASSERT_EQ(arr1.size(), 3);
  ASSERT_EQ(arr1.front(), 4);
  ASSERT_EQ(arr1.back(), 6);
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr2.front(), 1);
  ASSERT_EQ(arr2.back(), 3);
}

TEST(array_modifiers, array_modifiers_fill_Test1) {
  s21::Array<int, 3> arr1;
  arr1.fill(5);
  for (size_t i = 0; i < arr1.size(); i++) {
    ASSERT_EQ(arr1.at(i), 5);
  }
  ASSERT_EQ(arr1.size(), 3);
}

//  ================================================= //
//  ==================== MAP ======================== //
//  ================================================= //

//  ============== Map Member functions ============== //

TEST(map_memeber_functions, default_constructor) {
  s21::Map<int, int> myMap;
  ASSERT_EQ(0, myMap.size());
}

TEST(map_memeber_functions, initializer_list_constructor) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  ASSERT_EQ(4, myMap.size());
  ASSERT_EQ(155, myMap.at(3));
}

TEST(map_memeber_functions, copy_constructor) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int> myMap2(myMap);
  ASSERT_EQ(4, myMap2.size());
  ASSERT_EQ(155, myMap2.at(3));
}

TEST(map_memeber_functions, move_constructor) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int> myMap2(std::move(myMap));
  ASSERT_EQ(4, myMap2.size());
  ASSERT_EQ(155, myMap2[3]);
}

//  =============== Map Element access =============== //

TEST(map_element_access, at) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  myMap.at(3) = 356;
  ASSERT_EQ(356, myMap.at(3));
}

TEST(map_element_access, sq_brackets) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  myMap[3] = 356;
  ASSERT_EQ(356, myMap[3]);
  ASSERT_EQ(0, myMap[9]);
}

TEST(map_element_access, sq_brackets_2) {
  s21::Map<int, int> myMap;
  myMap[3] = 356;
  ASSERT_EQ(356, myMap[3]);
}

TEST(map_element_access, pointer) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator it = myMap.begin();
  std::pair<int, int> tst = *it;
  ASSERT_EQ(33, tst.second);
  ++it;
  tst = *it;
  ASSERT_EQ(155, tst.second);
}

//  =============== Map Iterators =============== //

TEST(map_iterators, begin) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator it = myMap.begin();
  ASSERT_EQ(33, it.itCurrent_->keyValue_.second);
  ++it;
  ASSERT_EQ(155, it.itCurrent_->keyValue_.second);
}

TEST(map_iterators, end) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator it = myMap.end();
  --it;
  ASSERT_EQ(6, it.itCurrent_->keyValue_.first);
  --it;
  ASSERT_EQ(5, it.itCurrent_->keyValue_.first);
  --it;
  ASSERT_EQ(3, it.itCurrent_->keyValue_.first);
  --it;
  ASSERT_EQ(1, it.itCurrent_->keyValue_.first);
}

TEST(map_iterators, cbegin) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator it = myMap.cbegin();
  ASSERT_EQ(33, it.itCurrent_->keyValue_.second);
}

TEST(map_iterators, cend) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator it = myMap.cend();
  ASSERT_EQ(6, it.itParent_->keyValue_.first);
}

TEST(map_iterators, inorder_traversal) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator itB = myMap.begin();
  s21::Map<int, int>::iterator itE = myMap.end();

  while (itB != itE) {
    ++itB;
  }
  --itB;
  ASSERT_EQ(itB.itCurrent_->keyValue_.first, 6);
}

TEST(map_iterators, reverse_traversal) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator itB = myMap.begin();
  s21::Map<int, int>::iterator itE = myMap.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itB.itCurrent_->keyValue_.first, 1);
}

TEST(map_iterators, reverse_traversal_1) {
  s21::Map<int, int> myMap{{3, 155},  {1, 33},  {5, 76},  {6, 98},  {7, 155},
                           {10, 33},  {15, 76}, {12, 98}, {17, 76}, {42, 98},
                           {53, 155}, {40, 53}, {39, 76}, {32, 98}, {31, 155}};
  s21::Map<int, int>::iterator itB = myMap.begin();
  s21::Map<int, int>::iterator itE = myMap.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itE.itCurrent_->keyValue_.first, 1);
}

TEST(map_iterators, reverse_traversal_2) {
  s21::Map<int, int> myMap{{53, 155}, {40, 53}, {39, 76}, {32, 98}, {31, 155}};
  s21::Map<int, int>::iterator itB = myMap.begin();
  s21::Map<int, int>::iterator itE = myMap.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itB.itCurrent_->keyValue_.first, 31);
}

//  =============== Map Capacity =============== //

TEST(map_capacity, empty) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int> myMap2;
  ASSERT_EQ(0, myMap.empty());
  ASSERT_EQ(1, myMap2.empty());
}

TEST(map_capacity, size) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  std::map<int, int> myMap2{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  ASSERT_EQ(4, myMap.size());
  ASSERT_EQ(4, myMap2.size());
}

TEST(map_capacity, max_size) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  std::map<int, int> myMap2{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  ASSERT_EQ(myMap2.size(), myMap.size());
}

//  =============== Map Modifiers =============== //

TEST(map_modifiers, clear) {
  // ASSERT_EQ( , );
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  std::map<int, int> myMap2{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  myMap.clear();
  myMap2.clear();
  ASSERT_EQ(myMap2.size(), myMap.size());
}

TEST(map_modifiers, clear_2) {
  s21::Map<int, int> myMap{{3, 15}, {155, 15}, {1, 15}, {33, 15},
                           {5, 15}, {76, 15},  {6, 15}, {98, 15}};
  std::map<int, int> myMap2{{3, 15}, {155, 15}, {1, 15}, {33, 15},
                            {5, 15}, {76, 15},  {6, 15}, {98, 15}};
  myMap.clear();
  myMap2.clear();
  ASSERT_EQ(myMap2.size(), myMap.size());
}

TEST(map_modifiers, insert_pair) {
  s21::Map<int, int> myMap;
  std::pair<int, int> myPair_1(3, 77);
  std::pair<int, int> myPair_2(2, 99);
  std::pair<int, int> myPair_3(4, 88);
  myMap.insert(myPair_1);
  myMap.insert(myPair_2);
  myMap.insert(myPair_3);
  ASSERT_EQ(myMap.at(3), 77);
}

TEST(map_modifiers, insert_K_T) {
  s21::Map<int, int> myMap;
  myMap.insert(3, 77);
  myMap.insert(2, 99);
  myMap.insert(4, 88);
  ASSERT_EQ(myMap.at(3), 77);
}

TEST(map_modifiers, insert_or_assign) {
  s21::Map<int, int> myMap;
  myMap.insert_or_assign(3, 77);
  myMap.insert_or_assign(2, 99);
  myMap.insert_or_assign(4, 88);
  myMap.insert_or_assign(4, 1088);
  myMap.insert_or_assign(4, 155);
  ASSERT_EQ(myMap.at(4), 155);
}

TEST(map_modifiers, erase) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int>::iterator itB = myMap.begin();
  ++itB;
  ++itB;
  myMap.erase(itB);
  ASSERT_EQ(myMap.contains(5), 0);
}

TEST(map_modifiers, erase_1) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33},  {5, 76}, {6, 98},
                           {2, 12},  {9, 113}, {7, 90}};
  s21::Map<int, int>::iterator itB = myMap.begin();
  ++itB;
  ++itB;
  myMap.erase(itB);
  ASSERT_EQ(myMap.contains(3), 0);

  s21::Map<int, int>::iterator itE = myMap.end();
  --itE;
  --itE;
  myMap.erase(itE);
  ASSERT_EQ(myMap.contains(7), 0);

  s21::Map<int, int> myMap2{{3, 155}};
  s21::Map<int, int>::iterator itB1 = myMap2.begin();
  myMap2.erase(itB1);
  ASSERT_EQ(myMap2.size(), 0);
}

TEST(map_modifiers, erase_2) {
  s21::Map<int, int> myMap;

  for (int i = 1; i < 45; i++) {
    std::pair<int, int> myPair_1(i, i + 10);
    myMap.insert(myPair_1);
  }
  ASSERT_EQ(myMap.at(3), 13);

  for (int i = 1; i < 44; i++) {
    s21::Map<int, int>::iterator itB = myMap.begin();
    for (int j = 1; j < 2; j++) {
      ++itB;
    }
    myMap.erase(itB);
  }
  ASSERT_EQ(myMap[1113], 0);
}

TEST(map_modifiers, erase_3) {
  s21::Map<int, int> myMap;
  std::pair<int, int> myPair_1(5, 77);
  std::pair<int, int> myPair_2(3, 99);
  std::pair<int, int> myPair_3(1, 88);
  std::pair<int, int> myPair_4(4, 88);
  myMap.insert(myPair_1);
  myMap.insert(myPair_2);
  myMap.insert(myPair_3);
  myMap.insert(myPair_4);
  s21::Map<int, int>::iterator itB = myMap.begin();
  ++itB;
  ++itB;
  ++itB;

  myMap.erase(itB);

  ASSERT_EQ(myMap.size(), 3);
}

TEST(map_modifiers, swap) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int> myMap2{{3, 1055}, {1, 303}, {5, 706}, {6, 908}};
  myMap.swap(myMap2);
  ASSERT_EQ(myMap.at(3), 1055);
}

TEST(map_modifiers, merge) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  s21::Map<int, int> myMap2{{3, 1055}, {1, 303}, {5, 706}, {6, 908}, {7, 192}};
  myMap.merge(myMap2);
  ASSERT_EQ(myMap.at(3), 155);
  ASSERT_EQ(myMap.at(7), 192);
}

//  =============== Map Lookup ================== //

TEST(map_look_up, contains) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  ASSERT_TRUE(myMap.contains(1));
  ASSERT_FALSE(myMap.contains(7));
}

//  =============== Map Bonus Task ================== //

TEST(map_bonus, emplace) {
  s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
  std::pair<int, int> myPair_1(3, 77);
  std::pair<int, int> myPair_2(2, 99);
  std::pair<int, int> myPair_3(4, 88);
  myMap.emplace(myPair_1, myPair_2, myPair_3);
  ASSERT_TRUE(myMap.contains(2));
  ASSERT_TRUE(myMap.contains(4));
}

//  ================================================= //
//  ==================== MULTISET =================== //
//  ================================================= //

//  ============== MultiSet Member functions ============== //

TEST(multiset_memeber_functions, default_constructor) {
  s21::MultiSet<int> mySet;
  ASSERT_EQ(0, mySet.size());
}

TEST(multiset_memeber_functions, initializer_list_constructor) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(8, mySet.size());
}

TEST(multiset_memeber_functions, copy_constructor) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2(mySet);
  ASSERT_EQ(8, mySet2.size());
}

TEST(multiset_memeber_functions, move_constructor) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2(std::move(mySet));
  ASSERT_EQ(8, mySet2.size());
}

//  =============== MultiSet Iterators =============== //

TEST(multiset_iterators, begin) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int>::iterator it = mySet.begin();
  ASSERT_EQ(1, it.itCurrent_->getValue());
  ++it;
  ASSERT_EQ(3, it.itCurrent_->getValue());
}

TEST(multiset_iterators, end) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int>::iterator it = mySet.end();
  --it;
  ASSERT_EQ(155, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(98, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(76, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(33, it.itCurrent_->getValue());
}

TEST(multiset_iterators, pointer) {
  s21::MultiSet<int> mySet{{3, 155, 1, 33, 5, 76, 6, 98}};
  s21::MultiSet<int>::iterator it = mySet.begin();
  ++it;
  int val = *it;
  ASSERT_EQ(3, val);
  ++it;
  val = *it;
  ASSERT_EQ(5, val);
}

//  =============== MultiSet Capacity =============== //

TEST(multiset_capacity, empty) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2;
  ASSERT_EQ(0, mySet.empty());
  ASSERT_EQ(1, mySet2.empty());
}

TEST(multiset_capacity, size) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(8, mySet.size());
  ASSERT_EQ(8, mySet2.size());
}

TEST(multiset_capacity, max_size) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(mySet2.max_size(), mySet.max_size());
}

//  =============== MultiSet Modifiers =============== //

TEST(multiset_modifiers, clear) {
  // ASSERT_EQ( , );
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  mySet.clear();
  mySet2.clear();
  ASSERT_EQ(mySet2.size(), mySet.size());
}

TEST(multiset_modifiers, insert_value) {
  s21::MultiSet<int> mySet;
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);
  ASSERT_EQ(mySet.size(), 3);
}

TEST(multiset_modifiers, erase) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  mySet.erase(itB);
  ASSERT_EQ(mySet.contains(5), 0);
}

TEST(multiset_modifiers, erase_1) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  mySet.erase(itB);
  ASSERT_EQ(mySet.contains(3), 0);

  s21::MultiSet<int>::iterator itE = mySet.end();
  --itE;
  --itE;
  mySet.erase(itE);
  ASSERT_EQ(mySet.contains(7), 0);

  s21::MultiSet<int> mySet2{3};
  s21::MultiSet<int>::iterator itB1 = mySet2.begin();
  mySet2.erase(itB1);
  ASSERT_EQ(mySet2.size(), 0);
}

TEST(multiset_modifiers, swap) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2{3, 1055, 1, 303, 5, 706, 6, 908};
  mySet.swap(mySet2);
  ASSERT_TRUE(mySet.contains(1055));
  ASSERT_FALSE(mySet.contains(33));
}

TEST(multiset_modifiers, merge) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2{3, 1055, 1, 303, 5, 706, 6, 908};
  mySet.merge(mySet2);
  ASSERT_EQ(mySet.size(), 16);
  ASSERT_TRUE(mySet.contains(1055));
}

//  =============== MultiSet Lookup ================== //

TEST(multiset_look_up, find) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7};
  s21::MultiSet<int>::iterator itFind = mySet.find(3);
  s21::MultiSet<int>::iterator itFind2 = mySet.find(99);
  ASSERT_EQ(itFind.itCurrent_->getValue(), 3);
  ASSERT_EQ(itFind2.itCurrent_, mySet.end().itCurrent_);
}

TEST(multiset_look_up, contains) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7};
  ASSERT_EQ(mySet.contains(1), 1);
  ASSERT_EQ(mySet.contains(8), 0);
}

TEST(multiset_look_up, count) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7, 1, 9, 9};

  ASSERT_EQ(mySet.count(1), 2);
  ASSERT_EQ(mySet.count(9), 3);
  ASSERT_EQ(mySet.count(7), 1);
  ASSERT_EQ(mySet.count(17), 0);
}

TEST(multiset_look_up, lower_bound_upper_bound_equal_range) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7, 1, 9, 9};

  ASSERT_EQ(mySet.lower_bound(1).itCurrent_->getValue(), 1);
  ASSERT_EQ(mySet.upper_bound(1).itCurrent_->getValue(), 2);
  ASSERT_EQ(mySet.lower_bound(5).itCurrent_->getValue(), 5);
  ASSERT_EQ(mySet.upper_bound(5).itCurrent_->getValue(), 6);
}

TEST(multiset_bonus, emplace) {
  s21::MultiSet<int> mySet{3, 1, 5, 76, 6, 98};
  mySet.emplace(5, 12, 75, 3, 1);
  ASSERT_TRUE(mySet.contains(12));
  ASSERT_TRUE(mySet.contains(75));
  ASSERT_EQ(mySet.count(3), 2);
  ASSERT_EQ(mySet.count(1), 2);
  ASSERT_EQ(mySet.count(5), 2);
}

//  ================================================= //
//  ============== FOR SET COVERAGE ================= //
//  ================================================= //

//  ============== Set Member functions ============== //

TEST(set_memeber_functions, default_constructor_m) {
  s21::MultiSet<int> mySet;
  ASSERT_EQ(0, mySet.size());
}

TEST(set_memeber_functions, initializer_list_constructor_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(8, mySet.size());
}

TEST(set_memeber_functions, copy_constructor_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2(mySet);
  ASSERT_EQ(8, mySet2.size());
}

TEST(set_memeber_functions, move_constructor_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2(std::move(mySet));
  ASSERT_EQ(8, mySet2.size());
}

//  =============== Set Iterators =============== //

TEST(set_iterators, begin_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int>::iterator it = mySet.begin();
  ASSERT_EQ(1, it.itCurrent_->getValue());
  ++it;
  ASSERT_EQ(3, it.itCurrent_->getValue());
}

TEST(set_iterators, end_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int>::iterator it = mySet.end();
  --it;
  ASSERT_EQ(155, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(98, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(76, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(33, it.itCurrent_->getValue());
}

TEST(set_iterators, inorder_traversal_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  s21::MultiSet<int>::iterator itE = mySet.end();

  while (itB != itE) {
    ++itB;
  }
  --itB;
  ASSERT_EQ(itB.itCurrent_->getValue(), 155);
}

TEST(set_iterators, reverse_traversal_m) {
  s21::MultiSet<int> mySet{3, 1, 5, 6};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  s21::MultiSet<int>::iterator itE = mySet.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itB.itCurrent_->getValue(), 1);
}

TEST(set_iterators, reverse_traversal_1_m) {
  s21::MultiSet<int> mySet{3,  1,  5,  6,  7,  10, 15, 12,
                           17, 42, 53, 40, 39, 32, 31};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  s21::MultiSet<int>::iterator itE = mySet.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itE.itCurrent_->getValue(), 1);
}

TEST(set_iterators, reverse_traversal_2_m) {
  s21::MultiSet<int> mySet{53, 40, 39, 32, 31};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  s21::MultiSet<int>::iterator itE = mySet.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itB.itCurrent_->getValue(), 31);
}

TEST(set_iterators, both_side_traversal_m) {
  s21::MultiSet<int> mySet{3, 1, 5, 99, 99, 99, 3, 3, 5, 5, 1};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  s21::MultiSet<int>::iterator itE = mySet.end();

  while (itB != mySet.end()) {
    ++itB;
  }

  while (itE != mySet.begin()) {
    --itE;
  }

  ASSERT_EQ(itE.itCurrent_->getValue(), 1);
}

TEST(set_iterators, pointer_m) {
  s21::MultiSet<int> mySet{{3, 155, 1, 33, 5, 76, 6, 98}};
  s21::MultiSet<int>::iterator it = mySet.begin();
  ++it;
  int val = *it;
  ASSERT_EQ(3, val);
  ++it;
  val = *it;
  ASSERT_EQ(5, val);
}

//  =============== Set Capacity =============== //

TEST(set_capacity, empty_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2;
  ASSERT_EQ(0, mySet.empty());
  ASSERT_EQ(1, mySet2.empty());
}

TEST(set_capacity, size_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(8, mySet.size());
  ASSERT_EQ(8, mySet2.size());
}

TEST(set_capacity, max_size_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(mySet2.max_size(), mySet.max_size());
}

//  =============== Set Modifiers =============== //

TEST(set_modifiers, clear_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  mySet.clear();
  mySet2.clear();
  ASSERT_EQ(mySet2.size(), mySet.size());
}

TEST(set_modifiers, insert_value_m) {
  s21::MultiSet<int> mySet;
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);
  ASSERT_EQ(mySet.size(), 3);
}

TEST(set_modifiers, erase_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  mySet.erase(itB);
  ASSERT_EQ(mySet.contains(5), 0);
}

TEST(set_modifiers, erase_1_m) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7};
  s21::MultiSet<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  mySet.erase(itB);
  ASSERT_EQ(mySet.contains(3), 0);

  s21::MultiSet<int>::iterator itE = mySet.end();
  --itE;
  --itE;
  mySet.erase(itE);
  ASSERT_EQ(mySet.contains(7), 0);

  s21::MultiSet<int> mySet2{3};
  s21::MultiSet<int>::iterator itB1 = mySet2.begin();
  mySet2.erase(itB1);
  ASSERT_EQ(mySet2.size(), 0);
}

TEST(set_modifiers, erase_2_m) {
  s21::MultiSet<int> mySet;

  for (int i = 1; i < 45; i++) {
    mySet.insert(i + 10);
  }
  ASSERT_TRUE(mySet.contains(13));

  for (int i = 1; i < 44; i++) {
    s21::MultiSet<int>::iterator itB = mySet.begin();
    for (int j = 1; j < 2; j++) {
      ++itB;
    }
    mySet.erase(itB);
  }
  ASSERT_FALSE(mySet.contains(13));
}

TEST(set_modifiers, erase_3_m) {
  s21::MultiSet<int> mySet;
  mySet.insert(5);
  mySet.insert(3);
  mySet.insert(1);
  mySet.insert(4);
  s21::MultiSet<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  ++itB;

  mySet.erase(itB);

  ASSERT_EQ(mySet.size(), 3);
}

TEST(set_modifiers, swap_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2{3, 1055, 1, 303, 5, 706, 6, 908};
  mySet.swap(mySet2);
  ASSERT_TRUE(mySet.contains(1055));
  ASSERT_FALSE(mySet.contains(33));
}

TEST(set_modifiers, merge_m) {
  s21::MultiSet<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::MultiSet<int> mySet2{3, 1055, 1, 303, 5, 706, 6, 908};
  mySet.merge(mySet2);
  ASSERT_EQ(mySet.size(), 16);
  ASSERT_TRUE(mySet.contains(1055));
}

//  =============== Set Lookup ================== //

TEST(set_look_up, find_m) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7};
  s21::MultiSet<int>::iterator itFind = mySet.find(3);
  s21::MultiSet<int>::iterator itFind2 = mySet.find(99);
  ASSERT_EQ(itFind.itCurrent_->getValue(), 3);
  ASSERT_EQ(itFind2.itCurrent_, mySet.end().itCurrent_);
}

TEST(set_look_up, contains_m) {
  s21::MultiSet<int> mySet{3, 1, 5, 6, 2, 9, 7};
  ASSERT_EQ(mySet.contains(1), 1);
  ASSERT_EQ(mySet.contains(8), 0);
}

TEST(set_bonus, emplace_m) {
  s21::MultiSet<int> mySet{3, 1, 5, 76, 6, 98};
  mySet.emplace(5, 12, 75, 3, 1);
  ASSERT_TRUE(mySet.contains(12));
  ASSERT_TRUE(mySet.contains(75));
  ASSERT_EQ(mySet.size(), 11);
}

//  ================================================= //
//  ==================== SET ======================== //
//  ================================================= //

//  ============== Set Member functions ============== //

TEST(set_memeber_functions, default_constructor) {
  s21::Set<int> mySet;
  ASSERT_EQ(0, mySet.size());
}

TEST(set_memeber_functions, initializer_list_constructor) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(8, mySet.size());
}

TEST(set_memeber_functions, copy_constructor) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int> mySet2(mySet);
  ASSERT_EQ(8, mySet2.size());
}

TEST(set_memeber_functions, move_constructor) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int> mySet2(std::move(mySet));
  ASSERT_EQ(8, mySet2.size());
}

//  =============== Set Iterators =============== //

TEST(set_iterators, begin) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int>::iterator it = mySet.begin();
  ASSERT_EQ(1, it.itCurrent_->getValue());
  ++it;
  ASSERT_EQ(3, it.itCurrent_->getValue());
}

TEST(set_iterators, end) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int>::iterator it = mySet.end();
  --it;
  ASSERT_EQ(155, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(98, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(76, it.itCurrent_->getValue());
  --it;
  ASSERT_EQ(33, it.itCurrent_->getValue());
}

TEST(set_iterators, inorder_traversal) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int>::iterator itB = mySet.begin();
  s21::Set<int>::iterator itE = mySet.end();

  while (itB != itE) {
    ++itB;
  }
  --itB;
  ASSERT_EQ(itB.itCurrent_->getValue(), 155);
}

TEST(set_iterators, reverse_traversal) {
  s21::Set<int> mySet{3, 1, 5, 6};
  s21::Set<int>::iterator itB = mySet.begin();
  s21::Set<int>::iterator itE = mySet.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itB.itCurrent_->getValue(), 1);
}

TEST(set_iterators, reverse_traversal_1) {
  s21::Set<int> mySet{3, 1, 5, 6, 7, 10, 15, 12, 17, 42, 53, 40, 39, 32, 31};
  s21::Set<int>::iterator itB = mySet.begin();
  s21::Set<int>::iterator itE = mySet.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itE.itCurrent_->getValue(), 1);
}

TEST(set_iterators, reverse_traversal_2) {
  s21::Set<int> mySet{53, 40, 39, 32, 31};
  s21::Set<int>::iterator itB = mySet.begin();
  s21::Set<int>::iterator itE = mySet.end();

  while (itE != itB) {
    --itE;
  }
  ASSERT_EQ(itB.itCurrent_->getValue(), 31);
}

TEST(set_iterators, pointer) {
  s21::Set<int> mySet{{3, 155, 1, 33, 5, 76, 6, 98}};
  s21::Set<int>::iterator it = mySet.begin();
  ++it;
  int val = *it;
  ASSERT_EQ(3, val);
  ++it;
  val = *it;
  ASSERT_EQ(5, val);
}

//  =============== Set Capacity =============== //

TEST(set_capacity, empty) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int> mySet2;
  ASSERT_EQ(0, mySet.empty());
  ASSERT_EQ(1, mySet2.empty());
}

TEST(set_capacity, size) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(8, mySet.size());
  ASSERT_EQ(8, mySet2.size());
}

TEST(set_capacity, max_size) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  ASSERT_EQ(mySet2.max_size(), mySet.max_size());
}

//  =============== Set Modifiers =============== //

TEST(set_modifiers, clear) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  std::set<int> mySet2{3, 155, 1, 33, 5, 76, 6, 98};
  mySet.clear();
  mySet2.clear();
  ASSERT_EQ(mySet2.size(), mySet.size());
}

TEST(set_modifiers, insert_value) {
  s21::Set<int> mySet;
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);
  ASSERT_EQ(mySet.size(), 3);
}

TEST(set_modifiers, erase) {
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  mySet.erase(itB);
  ASSERT_EQ(mySet.contains(5), 0);
}

TEST(set_modifiers, erase_1) {
  s21::Set<int> mySet{3, 1, 5, 6, 2, 9, 7};
  s21::Set<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  mySet.erase(itB);
  ASSERT_EQ(mySet.contains(3), 0);

  s21::Set<int>::iterator itE = mySet.end();
  --itE;
  --itE;
  mySet.erase(itE);
  ASSERT_EQ(mySet.contains(7), 0);

  s21::Set<int> mySet2{3};
  s21::Set<int>::iterator itB1 = mySet2.begin();
  mySet2.erase(itB1);
  ASSERT_EQ(mySet2.size(), 0);
}

TEST(set_modifiers, erase_2) {
  s21::Set<int> mySet;

  for (int i = 1; i < 45; i++) {
    mySet.insert(i + 10);
  }
  ASSERT_TRUE(mySet.contains(13));

  for (int i = 1; i < 44; i++) {
    s21::Set<int>::iterator itB = mySet.begin();
    for (int j = 1; j < 2; j++) {
      ++itB;
    }
    mySet.erase(itB);
  }
  ASSERT_FALSE(mySet.contains(13));
}

TEST(set_modifiers, erase_3) {
  s21::Set<int> mySet;
  mySet.insert(5);
  mySet.insert(3);
  mySet.insert(1);
  mySet.insert(4);
  s21::Set<int>::iterator itB = mySet.begin();
  ++itB;
  ++itB;
  ++itB;

  mySet.erase(itB);

  ASSERT_EQ(mySet.size(), 3);
}

TEST(set_modifiers, swap) {  // FIND
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int> mySet2{3, 1055, 1, 303, 5, 706, 6, 908};
  mySet.swap(mySet2);
  ASSERT_TRUE(mySet.contains(1055));
  ASSERT_FALSE(mySet.contains(33));
}

TEST(set_modifiers, merge) {  // FIND
  s21::Set<int> mySet{3, 155, 1, 33, 5, 76, 6, 98};
  s21::Set<int> mySet2{3, 1055, 1, 303, 5, 706, 6, 908};
  mySet.merge(mySet2);
  ASSERT_EQ(mySet.size(), 12);
  ASSERT_TRUE(mySet.contains(1055));
}

//  =============== Set Lookup ================== //

TEST(set_look_up, find) {
  s21::Set<int> mySet{3, 1, 5, 6, 2, 9, 7};
  s21::Set<int>::iterator itFind = mySet.find(3);
  s21::Set<int>::iterator itFind2 = mySet.find(99);
  ASSERT_EQ(itFind.itCurrent_->getValue(), 3);
  ASSERT_EQ(itFind2.itCurrent_, mySet.end().itCurrent_);
}

TEST(set_look_up, contains) {
  s21::Set<int> mySet{3, 1, 5, 6, 2, 9, 7};
  ASSERT_EQ(mySet.contains(1), 1);
  ASSERT_EQ(mySet.contains(8), 0);
}

TEST(set_bonus, emplace) {
  s21::Set<int> mySet{3, 1, 5, 76, 6, 98};
  mySet.emplace(5, 12, 75, 3, 1);
  ASSERT_TRUE(mySet.contains(12));
  ASSERT_TRUE(mySet.contains(75));
  ASSERT_EQ(mySet.size(), 8);
}
// =========== TESTS FOR EXCEPTIONS =========== //

// TEST(list_functions, list_functions_parameterized_constructor_Test2) {
//   ASSERT_ANY_THROW(s21::List<int> lst1(384307168202282326));
// }

// TEST(list_element_access, list_element_access_front_Test2) {
//   s21::List<int> lst1;
//   ASSERT_ANY_THROW(lst1.front());
// }

// TEST(list_element_access, list_element_access_back_Test2) {
//   s21::List<int> lst1;
//   ASSERT_ANY_THROW(lst1.back());
// }

// TEST(list_iterators, list_iterators_pointer_Test3) {
//   s21::List<int> lst1{1, 2, 3};
//   s21::List<int>::iterator it(lst1.end());
//   ASSERT_ANY_THROW(*it);
// }

// TEST(list_iterators, list_iterators_increment_Test2) {
//   s21::List<int> lst1{1, 2};
//   s21::List<int>::iterator it(lst1.end());
//   ASSERT_ANY_THROW(++it);
// }
// TEST(list_iterators, list_iterators_decrement_Test2) {
//   s21::List<int> lst1{1, 2};
//   s21::List<int>::iterator it(lst1.begin());
//   ASSERT_ANY_THROW(--it);
// }

// TEST(list_modifiers, list_modifiers_erase_Test2) {
//   s21::List<int> lst1{1, 2, 3};
//   s21::List<int>::iterator it(lst1.end());
//   ASSERT_ANY_THROW(lst1.erase(it));
// }

// TEST(list_modifiers, list_modifiers_pop_back_Test2) {
//   s21::List<int> lst1;
//   ASSERT_ANY_THROW(lst1.pop_back());
// }

// TEST(list_modifiers, list_modifiers_pop_front_Test2) {
//   s21::List<int> lst1;
//   ASSERT_ANY_THROW(lst1.pop_front());
// }

// TEST(list_modifiers, list_modifiers_reverse_Test3) {
//   s21::List<int> lst1;
//   ASSERT_ANY_THROW(lst1.reverse());
// }

// TEST(list_modifiers, list_modifiers_unique_Test2) {
//   s21::List<int> lst1;
//   ASSERT_ANY_THROW(lst1.unique());
// }

// TEST(list_modifiers, list_modifiers_sort_Test2) {
//   s21::List<int> lst1;
//   ASSERT_ANY_THROW(lst1.sort());
// }

// TEST(queue_element_access, queue_element_access_front_Test2) {
//   s21::Queue<int> q1;
//   ASSERT_ANY_THROW(q1.front());
// }

// TEST(queue_element_access, queue_element_access_back_Test2) {
//   s21::Queue<int> q1;
//   ASSERT_ANY_THROW(q1.back());
// }

// TEST(queue_modifiers, queue_modifiers_pop_Test2) {
//   s21::Queue<int> q1;
//   ASSERT_ANY_THROW(q1.pop());
// }

// TEST(stack_element_access, stack_element_access_top_Test2) {
//   s21::Stack<int> st1;
//   ASSERT_ANY_THROW(st1.top());
// }

// TEST(stack_modifiers, stack_modifiers_pop_Test2) {
//   s21::Stack<int> st1;
//   ASSERT_ANY_THROW(st1.pop());
// }

// TEST(vector_functions, vector_functions_parameterized_constructor_Test2) {
//   ASSERT_ANY_THROW(s21::Vector<int> vctr1(2305843009213693955));
// }

// TEST(vector_element_access, vector_element_access_at_Test2) {
//   s21::Vector<int> vctr1(3);
//   ASSERT_ANY_THROW(vctr1.at(5));
// }

// TEST(vector_element_access, vector_element_access_operator_sqbr_Test2) {
//   s21::Vector<int> vctr1(3);
//   ASSERT_ANY_THROW(vctr1[5]);
// }

// TEST(vector_element_access, vector_element_access_front_Test2) {
//   s21::Vector<int> vctr1;
//   ASSERT_ANY_THROW(vctr1.front());
// }

// TEST(vector_element_access, vector_element_access_back_Test2) {
//   s21::Vector<int> vctr1;
//   ASSERT_ANY_THROW(vctr1.back());
// }

// TEST(vector_element_access, vector_element_access_data_Test2) {
//   s21::Vector<int> vctr1;
//   ASSERT_ANY_THROW(vctr1.data());
// }

// TEST(vector_modifiers, vector_modifiers_erase_Test2) {
//   s21::Vector<int> vctr1{1, 2, 3};
//   s21::Vector<int>::iterator it(vctr1.end());
//   ASSERT_ANY_THROW(vctr1.erase(it));
// }

// TEST(vector_modifiers, vector_modifiers_erase_Test6) {
//   s21::Vector<int> vctr1{1, 2, 3};
//   s21::Vector<int>::iterator it(vctr1.begin());
//   vctr1.clear();
//   ASSERT_ANY_THROW(vctr1.erase(it));
// }

// TEST(vector_modifiers, vector_modifiers_pop_back_Test2) {
//   s21::Vector<int> vctr1;
//   ASSERT_ANY_THROW(vctr1.pop_back());
// }

// TEST(array_element_access, array_element_access_at_Test2) {
//   s21::Array<int, 3> arr1{1, 2, 3};
//   ASSERT_ANY_THROW(arr1.at(5));
// }

// TEST(array_element_access, array_element_access_operator_sqbr_Test2) {
//   s21::Array<int, 3> arr1{1, 2, 3};
//   ASSERT_ANY_THROW(arr1[5]);
// }

// TEST(array_element_access, array_element_access_front_Test2) {
//   s21::Array<int, 0> arr1;
//   ASSERT_ANY_THROW(arr1.front());
// }

// TEST(array_element_access, array_element_access_back_Test2) {
//   s21::Array<int, 0> arr1;
//   ASSERT_ANY_THROW(arr1.back());
// }
// TEST(array_element_access, array_element_access_data_Test2) {
//   s21::Array<int, 0> arr1;
//   ASSERT_ANY_THROW(arr1.data());
// }

// TEST(array_modifiers, array_modifiers_fill_Test2) {
//   s21::Array<int, 0> arr1;
//   ASSERT_ANY_THROW(arr1.fill(5));
// }

// TEST(map_exceptions, map_at) {
//   s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
//   ASSERT_ANY_THROW(myMap.at(119));
// }

// TEST(map_exceptions, increment) {
//   s21::Map<int, int> myMap{{1, 33}};
//   s21::Map<int, int>::iterator itE = myMap.end();
//   ASSERT_ANY_THROW(++itE);
// }

// TEST(map_exceptions, decrement) {
//   s21::Map<int, int> myMap{{3, 155}, {1, 33}, {5, 76}, {6, 98}};
//   s21::Map<int, int>::iterator itB = myMap.begin();
//   ASSERT_ANY_THROW(--itB);
// }

// TEST(map_exceptions, pointer_excp) {
//   s21::Map<int, int> myMap{{1, 33}};
//   s21::Map<int, int>::iterator itE = myMap.end();
//   ASSERT_ANY_THROW(*itE);
// }

// TEST(map_exceptions, begin) {
//   s21::Map<int, int> myMap;
//   ASSERT_ANY_THROW(myMap.begin());
// }

// TEST(map_exceptions, end) {
//   s21::Map<int, int> myMap;
//   ASSERT_ANY_THROW(myMap.end());
// }

// TEST(map_exceptions, cend) {
//   s21::Map<int, int> myMap;
//   ASSERT_ANY_THROW(myMap.cend());
// }

// TEST(map_exceptions, erase) {
//   s21::Map<int, int> myMap{{1, 33}};
//   s21::Map<int, int>::iterator itE = myMap.end();
//   ASSERT_ANY_THROW(myMap.erase(itE));
// }

// TEST(map_exceptions, erase_1) {
//   s21::Map<int, int> myMap{{1, 33}};
//   s21::Map<int, int>::iterator itE = myMap.end();
//   ASSERT_ANY_THROW(myMap.erase(itE));
// }

// TEST(map_exceptions, erase_2) {
//   s21::Map<int, int> myMap{};
//   s21::Map<int, int>::iterator itE;
//   ASSERT_ANY_THROW(myMap.erase(itE));
// }
// TEST(map_exceptions, swap) {
//   s21::Map<int, int> myMap{{1, 33}};
//   ASSERT_ANY_THROW(myMap.swap(myMap));
// }

//  //  ================= SET EXCEPTIONS ===================== //

// TEST(set_exceptions, increment) {
//   s21::Set<int> mySet{{1, 33}};
//   s21::Set<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(++itE);
// }

// TEST(set_exceptions, decrement) {
//   s21::Set<int> mySet{3, 1, 5, 6};
//   s21::Set<int>::iterator itB = mySet.begin();
//   ASSERT_ANY_THROW(--itB);
// }

// TEST(set_exceptions, begin) {
//   s21::Set<int> mySet;
//   ASSERT_ANY_THROW(mySet.begin());
// }

// TEST(set_exceptions, end) {
//   s21::Set<int> mySet;
//   ASSERT_ANY_THROW(mySet.end());
// }

// TEST(set_exceptions, erase) {
//   s21::Set<int> mySet{{1, 33}};
//   s21::Set<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(mySet.erase(itE));
// }

// TEST(set_exceptions, erase_1) {
//   s21::Set<int> mySet{{1, 33}};
//   s21::Set<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(mySet.erase(itE));
// }

// TEST(set_exceptions, erase_2) {
//   s21::Set<int> mySet{};
//   s21::Set<int>::iterator itE;
//   ASSERT_ANY_THROW(mySet.erase(itE));
// }

// TEST(set_exceptions, swap) {
//   s21::Set<int> mySet{{1, 33}};
//   ASSERT_ANY_THROW(mySet.swap(mySet));
// }

// TEST(set_exceptions, pointer_excp) {
//   s21::Set<int> mySet{1};
//   s21::Set<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(*itE);
// }

//  //  ================= MULTISET EXCEPTIONS ================== //

// TEST(set_exceptions, increment_m) {
//   s21::MultiSet<int> mySet{{1, 33}};
//   s21::MultiSet<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(++itE);
// }

// TEST(set_exceptions, decrement_m) {
//   s21::MultiSet<int> mySet{3, 1, 5, 6};
//   s21::MultiSet<int>::iterator itB = mySet.begin();
//   ASSERT_ANY_THROW(--itB);
// }

// TEST(set_exceptions, begin_m) {
//   s21::MultiSet<int> mySet;
//   ASSERT_ANY_THROW(mySet.begin());
// }

// TEST(set_exceptions, end_m) {
//   s21::MultiSet<int> mySet;
//   ASSERT_ANY_THROW(mySet.end());
// }

// TEST(set_exceptions, erase_m) {
//   s21::MultiSet<int> mySet{{1, 33}};
//   s21::MultiSet<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(mySet.erase(itE));
// }

// TEST(set_exceptions, erase_1_m) {
//   s21::MultiSet<int> mySet{{1, 33}};
//   s21::MultiSet<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(mySet.erase(itE));
// }

// TEST(set_exceptions, erase_2_m) {
//   s21::MultiSet<int> mySet{};
//   s21::MultiSet<int>::iterator itE;
//   ASSERT_ANY_THROW(mySet.erase(itE));
// }

// TEST(set_exceptions, swap_m) {
//   s21::MultiSet<int> mySet{{1, 33}};
//   ASSERT_ANY_THROW(mySet.swap(mySet));
// }

// TEST(set_exceptions, pointer_excp_m) {
//   s21::MultiSet<int> mySet{1};
//   s21::MultiSet<int>::iterator itE = mySet.end();
//   ASSERT_ANY_THROW(*itE);
// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
