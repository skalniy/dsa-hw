#pragma once

#ifndef HASH_TABLE_HXX
#define HASH_TABLE_HXX

#include <experimental/optional>


namespace dsa
{
  class hash_table
  {
  public:
    virtual
    ~hash_table() = default;

    bool virtual
    insert(const int, const int) = 0;

    bool virtual
    erase(const int) = 0;

    std::experimental::optional<int> virtual
    search(const int) = 0;
  };
} // namespace dsa


#endif // HASH_TABLE
