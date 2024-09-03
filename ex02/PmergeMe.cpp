/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:54:49 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/03 23:15:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iomanip>
#include <iostream>
#include <sys/time.h>

unsigned long getTime() {
  timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000 + t.tv_usec;
}

void PmergeMe(int *data, std::size_t size) {
  std::vector<int> v1(data, data + size);
  std::list<int> v2(data, data + size);
  std::cout << "Before:\t";
  printData(v1);
  unsigned long v1_start = getTime();
  sort(v1);
  unsigned long v1_end = getTime();
  unsigned long v2_start = getTime();
  //   sort(v2);
  unsigned long v2_end = getTime();
  std::cout << "After:\t";
  printData(v1);
  std::cout << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::vector : " << v1_end - v1_start << " us"
            << std::endl;
  std::cout << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::list : " << v2_end - v2_start << " us"
            << std::endl;
}

//	sort std::vector

// data[i - k]とdata[i]を前方k個にわたって入れ替える
void blockSwap(std::vector<int> &data, std::size_t a, std::size_t b,
               std::size_t n) {
  for (std::size_t i = 0; i < n; i++)
    std::swap(data[a - i], data[b - i]);
}

void sort(std::vector<int> &data) {
  std::size_t k = 1;
  for (; k * 2 < data.size(); k *= 2)
    for (std::size_t i = 2 * k - 1; i < data.size(); i += 2 * k)
      if (data[i] < data[i - k])
        blockSwap(data, i, i - k, k);
  k /= 2;
  std::cout << k << std::endl;
}

//	sort std::list
