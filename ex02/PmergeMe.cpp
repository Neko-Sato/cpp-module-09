/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 06:30:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/10/08 22:12:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iomanip>
#include <list>
#include <sys/time.h>
#include <vector>

unsigned long getTime() {
  timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000 + t.tv_usec;
}

unsigned long jacobsthal(unsigned long i) {
  static std::vector<unsigned long> buf;
  for (std::size_t k; (k = buf.size()) <= i;) {
    if (k == 0)
      buf.push_back(0);
    else if (k == 1)
      buf.push_back(1);
    else {
      unsigned long tmp;
      if (__builtin_mul_overflow(2, buf[k - 2], &tmp) ||
          __builtin_add_overflow(tmp, buf[k - 1], &tmp))
        throw std::overflow_error("jacobsthal");
      buf.push_back(tmp);
    }
  }
  return buf[i];
}

template <typename T> void sort(std::vector<T> &data);
template <typename T> void sort(std::list<T> &data);

void PmergeMe(int *data, std::size_t size) {
  unsigned long start = getTime();
  std::vector<int> v1(data, data + size);
  sort(v1);
  unsigned long middle = getTime();
  std::list<int> v2(data, data + size);
  sort(v2);
  unsigned long end = getTime();
  std::cout << "Before:\t";
  printData(data, data + size);
  std::cout << "After:\t";
  printData(v1.begin(), v1.end());
  std::cout << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::vector : " << middle - start << " us"
            << std::endl
            << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::list : " << end - middle << " us"
            << std::endl;
}

template <typename T> void sort(std::vector<T> &data) {
  if (data.size() < 2)
    return;
  typedef typename TypeSelector<T>::type Type;
  std::vector<Node<Type> > large, small;
  large.reserve(data.size() / 2);
  small.reserve(data.size() / 2 + data.size() % 2);
  for (typename std::vector<T>::iterator it = data.begin(); it != data.end();
       ++it) {
    typename std::vector<T>::iterator pre = it++;
    if (it == data.end()) {
      small.push_back(&*pre);
      break;
    }
    bool isLess = *pre < *it;
    large.push_back(isLess ? &*it : &*pre);
    small.push_back(isLess ? &*pre : &*it);
    large.back().push(&small.back());
  }
  sort(large);
  std::vector<Node<Type> > tmp;
  tmp.reserve(data.size());
  {
    typename std::vector<Node<Type> >::iterator it = large.begin();
    {
      tmp.push_back(*it->pop());
      tmp.push_back(*it);
      ++it;
    }
    for (std::size_t n = 1; it != large.end(); n++) {
      for (std::size_t j = 2 * jacobsthal(n); 0 < j && it != large.end(); --j, ++it)
        tmp.push_back(*it);
      for (typename std::vector<Node<Type> >::reverse_iterator jt = tmp.rbegin();
           jt != tmp.rend();) {
        if (jt->hasPair()) {
          Node<Type> &node = *jt->pop();
          tmp.insert(std::lower_bound(tmp.begin(), --jt.base(), node), node);
        } else
          ++jt;
      }
    }
    if (data.size() % 2) {
      Node<Type> &node = small.back();
      tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), node), node);
    }
  }
  std::vector<T> res;
  res.reserve(data.size());
  for (typename std::vector<Node<Type> >::iterator it = tmp.begin();
       it != tmp.end(); ++it) {
    T *value;
    it->getValue(value);
    res.push_back(*value);
  }
  data.swap(res);
}

template <typename T> void sort(std::list<T> &data) {
  if (data.size() < 2)
    return;
  typedef typename TypeSelector<T>::type Type;
  std::list<Node<Type> > large, small;
  for (typename std::list<T>::iterator it = data.begin(); it != data.end();
       ++it) {
    typename std::list<T>::iterator pre = it++;
    if (it == data.end()) {
      small.push_back(&*pre);
      break;
    }
    bool isLess = *pre < *it;
    large.push_back(isLess ? &*it : &*pre);
    small.push_back(isLess ? &*pre : &*it);
    large.back().push(&small.back());
  }
  sort(large);
  std::list<Node<Type> > tmp;
  {
    typename std::list<Node<Type> >::iterator it = large.begin();
    {
      tmp.push_back(*it->pop());
      tmp.push_back(*it);
      ++it;
    }
    for (std::size_t n = 1; it != large.end(); n++) {
      for (std::size_t j = 2 * jacobsthal(n); 0 < j && it != large.end(); --j, ++it)
        tmp.push_back(*it);
      for (typename std::list<Node<Type> >::reverse_iterator jt = tmp.rbegin();
           jt != tmp.rend();) {
        if (jt->hasPair()) {
          Node<Type> &node = *jt->pop();
          tmp.insert(std::lower_bound(tmp.begin(), --jt.base(), node), node);
        }
        ++jt;
      }
    }
    if (data.size() % 2) {
      Node<Type> &node = small.back();
      tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), node), node);
    }
  }
  std::list<T> res;
  for (typename std::list<Node<Type> >::iterator it = tmp.begin();
       it != tmp.end(); ++it) {
    T *value;
    it->getValue(value);
    res.push_back(*value);
  }
  data.swap(res);
}

// #include <iostream>

// class Integer {
// private:
//   int _value;

// public:
//   static std::size_t count;
//   Integer(int value) : _value(value) {};
//   bool operator<(Integer const &rhs) const {
//     std::cout << ++count << ": " << _value << " vs " << rhs._value << std::endl;
//     return _value < rhs._value;
//   };
//   friend std::ostream &operator<<(std::ostream &os, Integer const &rhs) {
//     os << rhs._value;
//     return os;
//   };
// };

// std::size_t Integer::count = 0;

// int main() {
//   int data[] = {21,1,13,2,17,3,12,4,20,5,15,6,19,7,14,8,18,9,16,10,11};
//   std::vector<Integer> v1(data, data + sizeof(data) / sizeof(data[0]));
//   sort(v1);
//   for (std::vector<Integer>::iterator it = v1.begin(); it != v1.end(); ++it)
//     std::cout << *it << " ";
//   std::cout << std::endl;
//   return 0;
// }
