/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:12:44 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/03 23:21:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <cerrno>
#include <cstdlib>
#include <limits>
#include <stdexcept>

int ft_stoi(char *str) {
  char *endptr;
  errno = 0;
  long i = std::strtol(str, &endptr, 10);
  if (errno || *endptr || std::numeric_limits<int>::max() < i ||
      std::numeric_limits<int>::min() > i)
    throw std::runtime_error("strtol");
  return i;
}

int main(int argc, char **argv) {
  std::size_t size = argc - 1;
  int *data = new int[size];
  try {
    for (std::size_t i = 0; i < size; i++) {
      data[i] = ft_stoi(argv[i + 1]);
      if (data[i] < 0)
        throw std::runtime_error("Invalid argument");
    }
    PmergeMe(data, size);
  } catch (const std::exception &e) {
    std::cerr << "Error" << std::endl;
  }
  delete[] data;
  return 0;
}
