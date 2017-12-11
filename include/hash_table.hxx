#pragma once

#ifndef HASH_TABLE_HXX
#define HASH_TABLE_HXX

#include <cstddef> // size_t
#include <experimental/optional>


namespace dsa
{
  class hash_table
  {
  protected:
    using data_t = std::pair<int, int>;
    
  public:
    virtual
    ~hash_table() = default;

    bool virtual
    insert(const int, const int) = 0;

    bool virtual
    erase(const int) = 0;

    std::experimental::optional<int> virtual
    search(const int) = 0;

    std::size_t virtual inline
    size() const
    { return m_size; }
  
  protected:
    std::size_t m_size = 0;
  };
} // namespace dsa


#endif // HASH_TABLE
