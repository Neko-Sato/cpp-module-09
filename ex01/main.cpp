/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:13:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/10/07 21:24:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int main(int argc, char *argv[]) {
  try {
    if (argc != 2)
      throw std::runtime_error("Invalid argument");
    std::stringstream ss(argv[1]);
    std::cout << rpn(ss) << std::endl;
    return EXIT_SUCCESS;
  } catch (...) {
    std::cerr << "Error" << std::endl;
    return EXIT_FAILURE;
  }
}