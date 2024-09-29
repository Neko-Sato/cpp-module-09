/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:15:54 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/29 20:55:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <iostream>
#include <list>
#include <vector>

void PmergeMe(int *data, std::size_t size);
unsigned long getTime();
unsigned long jacobsthal(unsigned long);

template <typename T> void printData(const T &data) {
  typename T::const_iterator it = data.begin();
  if (it != data.end()) {
    std::cout << *it++;
    while (it != data.end())
      std::cout << " " << *it++;
  }
  std::cout << std::endl;
}

#endif
