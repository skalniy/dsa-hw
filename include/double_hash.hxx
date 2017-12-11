#pragma once

#ifndef DOUBLE_HASH_HXX
#define DOUBLE_HASH_HXX

#include "hash_table.hxx"
 
#include <array>
#include <functional>
#include <iostream>
#include <memory>   // unique_ptr
#include <utility>  // pair
#include <vector>

namespace dsa
{
  class double_hash : public hash_table
  {
  private:
    using hash_func_t = std::function<std::size_t(const int key)>;

  public:
    explicit
    double_hash(std::size_t = 8);

    virtual
    ~double_hash() = default;

    bool virtual
    insert(const int, const int);

    bool virtual
    erase(const int);

    std::experimental::optional<int> virtual
    search(const int);

    friend std::ostream&
    operator<<(std::ostream&, const double_hash&);

  private:
    void
    m_rehash();

  protected:
    // bool means is deleted
    std::vector<std::pair<std::unique_ptr<data_t>, bool>> m_data;

    std::array<hash_func_t, 2> hash;
  };

  std::ostream&
  operator<<(std::ostream&, const dsa::double_hash&);
} // namespace dsa


#endif // DOUBLE_HASH_HXX
