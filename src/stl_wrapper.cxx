#include "stl_wrapper.hxx"

#include <utility> // make_pair


using namespace dsa;

stl_wrapper::stl_wrapper(std::size_t)
{ }

bool
stl_wrapper::insert(const int key, const int data)
{ return m_data.insert(std::make_pair(key, data)).second; }

bool
stl_wrapper::erase(const int key)
{ return m_data.erase(key) > 0; }

std::experimental::optional<int>
stl_wrapper::search(const int key)
{
  auto result = m_data.find(key);
  if (result != m_data.end())
    return std::experimental::make_optional(result->second);
  else
    return std::experimental::optional<int>();
}
