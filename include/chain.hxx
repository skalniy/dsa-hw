#pragma once

#ifndef CHAIN_HXX
#define CHAIN_HXX

#include "hash_table.hxx"

#include <list>
#include <vector>


namespace dsa
{
  class chain : public hash_table
  {
  private:
    class universal_hash
    {
    public:
      explicit
      universal_hash(std::size_t);

      std::size_t
      operator()(const int);

    private:
      std::size_t sz;

      std::uint64_t a, b;
    };

  public:
    explicit
    chain(std::size_t);

    bool virtual
    insert(const int, const int);

    bool virtual
    erase(const int);

    std::experimental::optional<int> virtual
    search(const int);

  private:
    std::vector<std::list<data_t>> m_data;
    universal_hash  hash;
  };
} // namespace dsa


#endif // CHAIN_HXX
