#include "chain.hxx"

#include <utility> // make_pair


using namespace dsa;

chain::universal_hash::universal_hash(std::size_t _sz)
: sz(_sz)
{
  a = std::rand() % (RAND_MAX - 1) + 1;
  b = std::rand();
}

std::size_t
chain::universal_hash::operator()(const int x)
{ 
  static constexpr std::uint64_t prime = 2147483659;
  return ((a * x + b) % prime) % sz; 
}

chain::chain(std::size_t sz)
: m_data(sz), hash(sz)
{ }

bool
chain::insert(const int key, const int data)
{ 
  std::size_t h = hash(key);
  for (const auto& el : m_data[h])
    if (el.first == key)
      return false;
  m_data[h].emplace_front(key, data);
  return true;
}

bool
chain::erase(const int key)
{ 
  std::size_t h = hash(key);
  for (auto it = m_data[h].begin(); it != m_data[h].end(); )
    if (it->first == key)
      {
        m_data[h].erase(it);
        return true;
      }
    else
      ++it;
  return false;
}

std::experimental::optional<int>
chain::search(const int key)
{
  std::size_t h = hash(key);
  for (const auto& el : m_data[h])
    if (el.first == key)
      return std::experimental::make_optional(el.second);
  return std::experimental::optional<int>();
}
