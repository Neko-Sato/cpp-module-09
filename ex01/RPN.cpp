/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 04:52:53 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/27 06:08:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <cstdlib>
#include <istream>
#include <sstream>
#include <stack>
#include <string>

static bool getToken(std::istream &in, std::string &tmp) {
  std::stringstream ss;
  int c;
  while ((c = in.peek()) != -1) {
    if (!std::isspace(c))
      break;
    in.ignore();
  }
  if (c == -1)
    return false;
  while ((c = in.peek()) != -1) {
    if (std::isspace(c))
      break;
    ss << (char)c;
    in.ignore();
  }
  tmp = ss.str();
  return true;
}

long ft_stol(const std::string &str) {
  char *endptr;
  errno = 0;
  long ret = std::strtol(str.c_str(), &endptr, 10);
  if (errno || *endptr)
    throw std::invalid_argument("invalid argument");
  return ret;
}

#define CALCULATE(op)                                                          \
  do {                                                                         \
    long a = stack.top();                                                      \
    stack.pop();                                                               \
    long b = stack.top();                                                      \
    stack.pop();                                                               \
    stack.push(b op a);                                                        \
  } while (0);

long rpn(std::istream &in) {
  std::stack<long> stack;
  std::string tmp;
  while (getToken(in, tmp)) {
    if (tmp == "+") {
      CALCULATE(+)
    } else if (tmp == "-") {
      CALCULATE(-)
    } else if (tmp == "*") {
      CALCULATE(*)
    } else if (tmp == "/") {
      CALCULATE(/)
    } else {
      stack.push(ft_stol(tmp));
    }
  }
  if (stack.size() != 1)
    throw std::invalid_argument("invalid argument");
  return stack.top();
}
