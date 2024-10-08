/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 04:52:53 by hshimizu          #+#    #+#             */
/*   Updated: 2024/10/08 18:06:00 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <cstdlib>
#include <istream>
#include <limits>
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

template <typename T, typename F>
static void calculate(std::stack<T> &stack, F op) {
  if (stack.empty())
    throw std::invalid_argument("invalid argument");
  T b = stack.top();
  stack.pop();
  if (stack.empty())
    throw std::invalid_argument("invalid argument");
  T a = stack.top();
  stack.pop();
  stack.push(op(a, b));
}

static long plus(long const &a, long const &b) {
  long c;
  if (__builtin_add_overflow(a, b, &c))
    throw std::overflow_error("overflow");
  return c;
}

static long minus(long const &a, long const &b) {
  long c;
  if (__builtin_sub_overflow(a, b, &c))
    throw std::overflow_error("overflow");
  return c;
}

static long multiplies(long const &a, long const &b) {
  long c;
  if (__builtin_mul_overflow(a, b, &c))
    throw std::overflow_error("overflow");
  return c;
}

static long divides(long const &a, long const &b) {
  if (b == 0)
    throw std::invalid_argument("invalid argument");
  if (a == std::numeric_limits<long>::min() && b == -1)
    throw std::overflow_error("overflow");
  return a / b;
}

long rpn(std::istream &in) {
  std::stack<long> stack;
  std::string tmp;
  while (getToken(in, tmp)) {
    if (tmp == "+")
      calculate(stack, plus);
    else if (tmp == "-")
      calculate(stack, minus);
    else if (tmp == "*")
      calculate(stack, multiplies);
    else if (tmp == "/")
      calculate(stack, divides);
    else
      stack.push(ft_stol(tmp));
  }
  if (stack.size() != 1)
    throw std::invalid_argument("invalid argument");
  return stack.top();
}
