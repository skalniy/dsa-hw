#pragma once

#ifndef DOUBLE_HASH_HXX
#define DOUBLE_HASH_HXX

#include "hash_table.hxx"

#include <iostream>
#include <memory>   // unique_ptr
#include <utility>  // pair
#include <vector>


namespace dsa
{
  class double_hash : public hash_table
  {
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

    std::size_t m_size;
  };

  std::ostream&
  operator<<(std::ostream&, const dsa::double_hash&);
} // namespace dsa


#endif // DOUBLE_HASH_HXX
