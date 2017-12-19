#include "chain.hxx"

using namespace dsa;

chain::chain(std::size_t sz)
: m_data(sz)
{
  // p is next prime after 2147483647 (RAND_MAX = 2^32)
  static constexpr std::uint64_t p = 2147483659; 
  const std::uint64_t a = std::rand() % (p - 1) + 1;
  const std::uint64_t b = std::rand() % p;

  hash = [a, b, this](const int key) -> std::size_t {
    return ((a * key + b) % p) % m_data.size();
  };
}

bool
chain::insert(const int key, const int data)
{ 
  std::size_t h = hash(key);

  // check if key exists
  for (const auto& el : m_data[h])
    if (el.first == key)
      return false;

  m_data[h].emplace_front(key, data);
  ++m_size;
  return true;
}

bool
chain::erase(const int key)
{ 
  std::size_t h = hash(key);

  for (auto it = m_data[h].begin(); it != m_data[h].end(); ++it)
    if (it->first == key)
      {
        m_data[h].erase(it);
        --m_size;
        return true;
      }

  return false;
}

std::experimental::optional<int>
chain::search(const int key)
{
  std::size_t h = hash(key);
  
  for (const auto& el : m_data[h])
    if (el.first == key)
      return std::experimental::make_optional(el.second);
  
  return std::experimental::nullopt;
}

std::experimental::optional<chain::data_t> 
chain::min() const
{
  if (!m_size)
    return std::experimental::nullopt;

  std::experimental::optional<data_t> result = std::experimental::nullopt;
  for (const auto& bucket : m_data)
    if (!bucket.empty())
      for (const auto& el : bucket)
        if (!result || el.second < result->second)
          result = el;

  return result;
}

std::experimental::optional<chain::data_t>
chain::max() const
{
  if (!m_size)
    return std::experimental::nullopt;

  std::experimental::optional<data_t> result = std::experimental::nullopt;
  for (const auto& bucket : m_data)
    if (!bucket.empty())
      for (auto el : bucket)
        if (!result || el.second > result->second)
          result = el;

  return result;
}

std::ostream&
dsa::operator<<(std::ostream& os, const chain& obj)
{
  for (size_t i = 0; i < obj.m_data.size(); ++i)
    {
      os << '[' << i << ']';
      for (const auto& el : obj.m_data[i])
        os << "->" <<el.first << ' ' << el.second;
      os << std::endl;
    }
  return os ;
}
