#pragma once

#ifndef CHAIN_HXX
#define CHAIN_HXX

#include "hash_table.hxx"

#include <functional>
#include <list>
#include <vector>


namespace dsa
{
  class chain : public hash_table
  {
  private:
    using hash_func_t = std::function<std::size_t(const int key)>;

  public:
    explicit
    chain(std::size_t = 8);

    bool virtual
    insert(const int, const int);

    bool virtual
    erase(const int);

    std::experimental::optional<int> virtual
    search(const int);

  private:
    std::vector<std::list<data_t>> m_data;
    hash_func_t hash;
  };
} // namespace dsa


#endif // CHAIN_HXX
