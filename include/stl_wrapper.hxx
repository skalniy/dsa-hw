#pragma once

#ifndef STL_WRAPPER_HXX
#define STL_WRAPPER_HXX

#include "hash_table.hxx"

#include <unordered_map>


namespace dsa
{
  class stl_wrapper : public hash_table
  {
  public:
    explicit
    stl_wrapper(std::size_t);

    virtual
    ~stl_wrapper() = default;

    bool virtual
    insert(const int, const int);

    bool virtual
    erase(const int);

    std::experimental::optional<int> virtual
    search(const int);

    std::experimental::optional<data_t> virtual
    min() const;

    std::experimental::optional<data_t> virtual
    max() const;

    std::size_t virtual inline
    size() const
    { return m_data.size(); }

  protected:
    std::unordered_map<int, int> m_data;
  };
} // namespace dsa


#endif // STL_WRAPPER_HXX
