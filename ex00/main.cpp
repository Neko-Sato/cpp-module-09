/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:51:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/10/07 21:44:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/*
	Damn the challenges!
	The Cpp module refuses to reproduce faithfully and beyond that,
	no beautiful work can be created.
	I can't do it. The finished code is crap.
*/

int main(int argc, char *argv[]) {
  try {
    BitcoinExchange btc;
    btc.read(1 < argc ? argv[1] : "");
    return EXIT_SUCCESS;
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
