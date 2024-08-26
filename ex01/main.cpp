/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:13:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/27 05:57:12 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

#include <sstream>

int main(int argc, char *argv[]) {
  try {
    if (argc == 2) {
      std::stringstream ss(argv[1]);
      std::cout << rpn(ss) << std::endl;
    }
  } catch (...) {
    std::cerr << "Error" << std::endl;
    return 1;
  }
  return 0;
}