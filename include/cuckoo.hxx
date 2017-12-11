#pragma once

#ifndef CUCKOO_HASH_HXX
#define CUCKOO_HASH_HXX

#include "hash_table.hxx"

#include <array>
#include <iostream>
#include <memory>   // unique_ptr
#include <utility>  // pair
#include <vector>


namespace dsa
{
  class cuckoo : public hash_table
  {
  private:
    using hash_func_t = std::function<std::size_t(const int key)>;

  public:
    cuckoo(std::size_t = 8);

    virtual
    ~cuckoo() = default;

    bool virtual
    insert(const int, const int);

    bool virtual
    erase(const int);

    std::experimental::optional<int> virtual
    search(const int);

    friend std::ostream&
    operator<<(std::ostream&, const cuckoo&);
    
  private:
    void
    m_rehash(const std::size_t);

  protected:
    std::array<std::vector<std::unique_ptr<data_t>>, 2> m_table;
    std::size_t m_size;

    // std::array<universal_hash, 2> m_hash;
    std::array<hash_func_t, 2> m_hash;
  };

  std::ostream&
  operator<<(std::ostream&, const dsa::cuckoo&);
} // namespace dsa


#endif // CUCKOO_HASH_HXX
