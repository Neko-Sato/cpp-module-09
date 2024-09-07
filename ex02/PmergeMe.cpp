/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:54:49 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/08 04:23:37 by hshimizu         ###   ########.fr       */
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
            << std::endl
            << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::list : " << v2_end - v2_start << " us"
            << std::endl;
}

//	sort std::vector

void sort(std::vector<int> &data) {
  std::size_t k;
  for (k = 1; k * 2 < data.size(); k *= 2)
    for (std::size_t i = 2 * k - 1; i < data.size(); i += 2 * k)
      if (data[i] < data[i - k])
        std::swap_ranges(data.begin() + (i - k + 1), data.begin() + (i + 1),
                         data.begin() + (i - k - k + 1));
  for (k /= 2; 1 < k; k /= 2) {
    for (std::size_t i = 1; i < data.size(); i += 2 * k)
      if (data[i] < data[i - k]) {
      }
  }
}
/*
y1 x1 x2 x3 x4 x5 x6 x7 x8 x9
      y2 y3 y4 y5 y6 y7 y8 y9
      2  2  3  3  3
*/


//	sort std::list


