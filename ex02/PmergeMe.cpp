/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:54:49 by hshimizu          #+#    #+#             */
/*   Updated: 2024/09/30 00:38:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iomanip>
#include <iostream>
#include <list>
#include <sys/time.h>
#include <vector>

struct Node {
  struct Pair {
    Node const *large;
    Node const *small;
    Pair() : large(NULL), small(NULL) {};
    Pair(Node const &large, Node const &small)
        : large(&large), small(&small) {};
    ~Pair() {};
    Pair(Pair const &other) : large(other.large), small(other.small) {};
    Pair &operator=(Pair const &other) {
      if (this != &other) {
        large = other.large;
        small = other.small;
      }
      return *this;
    };
  };
  Pair pair;
  int number;
  Node(int number = 0) : number(number) {};
  Node(Node const &large, Node const &small) : pair(large, small), number(0) {};
  Node(Node const &other) : pair(other.pair), number(other.number) {};
  ~Node() {};
  Node &operator=(Node const &other) {
    if (this != &other) {
      pair = other.pair;
      number = other.number;
    }
    return *this;
  };
  int getTypical() const {
    if (pair.large)
      return pair.large->getTypical();
    return number;
  }
  bool operator<(Node const other) const {
    return getTypical() < other.getTypical();
  }
};

std::ostream &operator<<(std::ostream &out, Node const node) {
  if (node.pair.large)
    return out << "<" << *node.pair.large << " " << *node.pair.small << ">";
  else
    return out << node.number;
}

static void sort(std::vector<Node> &data);
static void sort(std::list<Node> &data);

void PmergeMe(int *data, std::size_t size) {
  unsigned long start = getTime();
  std::vector<Node> v1(data, data + size);
  sort(v1);
  unsigned long middle = getTime();
  std::list<Node> v2(data, data + size);
  sort(v2);
  unsigned long end = getTime();
  std::cout << "Before:\t";
  printData(data, data + size);
  std::cout << "After:\t";
  printData(v1.begin(), v1.end());
  std::cout << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::vector : " << middle - start << " us"
            << std::endl
            << "Time to process a range of " << std::setw(3)
            << std::setfill(' ') << size
            << " elements with std::list : " << end - middle << " us"
            << std::endl;
}

unsigned long getTime() {
  timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000 + t.tv_usec;
}

unsigned long jacobsthal(unsigned long i) {
  static std::vector<unsigned long> buf;
  for (std::size_t k; (k = buf.size()) <= i;) {
    if (k == 0)
      buf.push_back(0);
    else if (k == 1)
      buf.push_back(1);
    else {
      unsigned long tmp;
      if (__builtin_mul_overflow(2, buf[k - 2], &tmp) ||
          __builtin_add_overflow(tmp, buf[k - 1], &tmp))
        throw std::overflow_error("jacobsthal");
      buf.push_back(tmp);
    }
  }
  return buf[i];
}

static void sort(std::vector<Node> &data) {
  if (data.size() < 2)
    return;
  std::vector<Node> pairs;
  for (std::size_t i = 1; i < data.size(); i += 2)
    if (data[i] < data[i - 1])
      pairs.push_back(Node(data[i - 1], data[i]));
    else
      pairs.push_back(Node(data[i], data[i - 1]));
  sort(pairs);
  std::vector<Node> res, tmp;
  for (std::size_t n = 2, i = 0; i < pairs.size(); n++) {
    for (std::size_t j = jacobsthal(n); 0 < j && i < pairs.size(); j--, i++) {
      res.push_back(*pairs[i].pair.large);
      tmp.push_back(*pairs[i].pair.small);
    }
    while (!tmp.empty()) {
      Node &n = tmp.back();
      res.insert(std::lower_bound(res.begin(), res.end(), n), n);
      tmp.pop_back();
    }
  }
  if (data.size() % 2) {
    Node &n = data.back();
    res.insert(std::lower_bound(res.begin(), res.end(), n), n);
  }
  data = res;
}

static void sort(std::list<Node> &data) {
  if (data.size() < 2)
    return;
  std::list<Node> pairs;
  for (std::list<Node>::iterator it = data.begin(); it != data.end(); ++it) {
    std::list<Node>::iterator pre = it++;
    if (it == data.end())
      break;
    if (*it < *pre)
      pairs.push_back(Node(*pre, *it));
    else
      pairs.push_back(Node(*it, *pre));
  }
  sort(pairs);
  std::list<Node> res, tmp;
  for (std::size_t n = 2; !pairs.empty(); n++) {
    for (std::size_t j = jacobsthal(n); 0 < j && !pairs.empty(); j--) {
      Node &n = pairs.front();
      res.push_back(*n.pair.large);
      tmp.push_back(*n.pair.small);
      pairs.pop_front();
    }
    while (!tmp.empty()) {
      Node &n = tmp.back();
      res.insert(std::lower_bound(res.begin(), res.end(), n), n);
      tmp.pop_back();
    }
  }
  if (data.size() % 2) {
    Node &n = data.back();
    res.insert(std::lower_bound(res.begin(), res.end(), n), n);
  }
  data = res;
}
