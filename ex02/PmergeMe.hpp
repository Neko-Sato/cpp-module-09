/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:15:54 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/29 23:29:06 by hshimizu         ###   ########.fr       */
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

template <typename ConstIterator>
void printData(ConstIterator begin, ConstIterator end) {
  if (begin != end) {
    std::cout << *begin;
    while (++begin != end)
      std::cout << " " << *begin;
  }
  std::cout << std::endl;
}

#endif
