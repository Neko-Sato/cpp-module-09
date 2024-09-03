/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:12:44 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/03 22:21:33 by hshimizu         ###   ########.fr       */
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
  if (errno || std::numeric_limits<int>::max() < i ||
      std::numeric_limits<int>::min() > i)
    throw std::runtime_error("Error: Invalid argument");
  return i;
}

int main(int argc, char **argv) {
  std::size_t size = argc - 1;
  int *data = new int[size];
  for (std::size_t i = 0; i < size; i++)
    data[i] = ft_stoi(argv[i + 1]);
  PmergeMe(data, size);
  delete[] data;
  return 0;
}
