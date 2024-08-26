/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:03:58 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/27 04:36:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include <ctime>
#include <map>
#include <string>

class BitcoinExchange {
private:
  typedef std::map<time_t, float> Data;
  Data _data;
  void _load(std::string const &filename);

public:
  BitcoinExchange();
  BitcoinExchange(BitcoinExchange const &other);
  ~BitcoinExchange();
  BitcoinExchange &operator=(BitcoinExchange const &other);
  void setData(time_t time, float price);
  float getData(time_t time) const;

  void read(std::string const &filename);
};

#endif
