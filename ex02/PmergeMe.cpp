/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:54:49 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/16 23:12:29 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iomanip>
#include <iostream>
#include <sys/time.h>

template <typename T> static void sort(std::vector<T> &data);
template <typename T> static void sort(std::list<T> &data);

void PmergeMe(int *data, std::size_t size) {
  std::vector<int> v1(data, data + size);
  std::list<int> v2(data, data + size);
  std::cout << "Before:\t";
  printData(v1);
  unsigned long v1_start = getTime();
  //   sort(v1);
  unsigned long v1_end = getTime();
  unsigned long v2_start = getTime();
  //   sort(v2);
  unsigned long v2_end = getTime();
  std::cout << "After:\t";
  printData(v1);
  std::cout << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::vector : " << v1_end - v1_start << " us"
            << std::endl
            << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::list : " << v2_end - v2_start << " us"
            << std::endl;
}

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
