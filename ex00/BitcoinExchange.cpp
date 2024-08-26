/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:03:58 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/27 04:44:32 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

static time_t strtotime(std::string const &str) {
  std::tm tm;
  if (!strptime(str.c_str(), "%Y-%m-%d", &tm))
    throw std::invalid_argument("strptime failed");
  return std::mktime(&tm);
}

static std::string strtrim(std::string const &str) {
  std::size_t first = str.find_first_not_of(" \t");
  if (first == std::string::npos)
    return "";
  std::size_t last = str.find_last_not_of(" \t");
  return str.substr(first, last - first + 1);
}

BitcoinExchange::BitcoinExchange() {
  const char *filename = getenv("BITCOIN_DATA_CSV");
  if (!filename)
    filename = "data.csv";
  _load(filename);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
    : _data(other._data) {
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other) {
  if (this != &other) {
    _data = other._data;
  }
  return *this;
}

void BitcoinExchange::setData(time_t time, float price) {
  _data[time] = price;
}

float BitcoinExchange::getData(time_t time) const {
  Data::const_iterator it = _data.upper_bound(time);
  if (it == _data.begin())
    throw std::out_of_range("no data");
  return (--it)->second;
};

void BitcoinExchange::_load(std::string const &filename) {
  std::ifstream ifs;
  ifs.open(filename.c_str());
  if (!ifs)
    throw std::invalid_argument("database not found.");
  std::string line;
  std::getline(ifs, line);
  while (std::getline(ifs, line)) {
    std::stringstream ss(line);
    std::string s_date;
    std::string s_price;
    time_t date;
    float price;
    if (!std::getline(ss, s_date, ',') || !std::getline(ss, s_price, ','))
      throw std::runtime_error("invalid format.");
    s_date = strtrim(s_date);
    s_price = strtrim(s_price);
    try {
      date = strtotime(s_date);
    } catch (...) {
      throw std::runtime_error("invalid format.");
    }
    {
      char *endptr;
      errno = 0;
      price = std::strtof(s_price.c_str(), &endptr);
      if (errno || *endptr)
        throw std::runtime_error("invalid format.");
    }
    setData(date, price);
  }
  ifs.close();
}

void BitcoinExchange::read(std::string const &filename) {
  std::ifstream file;
  file.open(filename.c_str());
  if (!file)
    throw std::invalid_argument("could not open file.");
  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    try {
      std::stringstream ss(line);
      std::string s_date;
      std::string s_value;
      if (!std::getline(ss, s_date, '|') || !std::getline(ss, s_value, '|') ||
          !ss.eof())
        throw std::runtime_error("bad input => " + line);
      s_date = strtrim(s_date);
      s_value = strtrim(s_value);
      time_t time;
      float value;
      try {
        time = strtotime(s_date);
      } catch (...) {
        throw std::runtime_error("invalid format.");
      }
      {
        char *endptr;
        errno = 0;
        value = std::strtof(s_value.c_str(), &endptr);
        if (errno || *endptr)
          throw std::runtime_error("invalid format.");
        if (value < 0)
          throw std::runtime_error("not a positive number.");
        if (1000 < value)
          throw std::runtime_error("too large a number.");
      }
      try {
        std::cout << s_date << " => " << s_value << " = "
                  << getData(time) * value << std::endl;
      } catch (const std::exception &e) {
        throw std::runtime_error(e.what() + (" => " + s_date));
      }
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}
