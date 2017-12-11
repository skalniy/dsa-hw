#include "double_hash.hxx"

using namespace dsa;

double_hash::double_hash(std::size_t sz)
: m_data(sz), m_size(0)
{
  hash[0] = [this](const int key) -> std::size_t {
    return key % m_data.size();
  };

  hash[1] = [this](const int key) -> std::size_t {
    std::size_t res = key % m_data.size();
    return res + (1 ^ res % 2);
  };
}

bool
double_hash::insert(const int key, const int data)
{
  if (static_cast<bool>(this->search(key)))
    return false;

  if (m_size + 1 > (m_data.size() + 1) / 2)
    m_rehash();

  std::array<std::size_t, 2> h{ hash[0](key), hash[1](key) };
  for (std::size_t i = 0; i < m_data.size(); ++i)
    {
      std::size_t j = (h[0] + i * h[1]) % m_data.size();

      if (!m_data[j].first) // if not exists
        {
          m_data[j].first.reset(new data_t(key, data));
          m_data[j].second = false;
          ++m_size;

          return true;
        }
    }
  return false;
}

bool
double_hash::erase(const int key)
{ 
  std::array<std::size_t, 2> h{ hash[0](key), hash[1](key) };

  for (std::size_t i = 0; i < m_data.size(); ++i)
    {
      size_t j = (h[0] + i * h[1]) % m_data.size();

      if (m_data[j].first) // if exists
        {
          if (m_data[j].first->first == key) // check key eq
            {
              m_data[j].first.release();
              m_data[j].second = true;
              --m_size;
              return true;
            }
        }
      else if (!m_data[j].second) // if not marked as deleted
        return false;
    }
  return false;
}

std::experimental::optional<int>
double_hash::search(const int key)
{
  std::array<std::size_t, 2> h{ hash[0](key), hash[1](key) };

  for (std::size_t i = 0; i < m_data.size(); ++i)
    {
      size_t j = (h[0] + i * h[1]) % m_data.size();

      if (m_data[j].first) // if exists
        {
          if (m_data[j].first->first == key) // check key eq
            return std::experimental::make_optional(m_data[j].first->second);
        }
      else if (!m_data[j].second) // if not marked as deleted
        return std::experimental::optional<int>();
    }
  return std::experimental::optional<int>();
}

void
double_hash::m_rehash()
{
  std::vector<std::pair<std::unique_ptr<data_t>, bool>> old_data(m_data.size() * 2);
  std::swap(m_data, old_data);

  hash[0] = [this](const int key) -> std::size_t {
    return key % this->m_data.size();
  };
  hash[1] = [this](const int key) -> std::size_t {
    std::size_t res = key % this->m_data.size();
    return res + (1 ^ res % 2);
  };

  m_size = 0;
  for (std::size_t i = 0; i < old_data.size(); ++i)
    if (old_data[i].first)
      this->insert(old_data[i].first->first, old_data[i].first->second);
}

std::ostream&
dsa::operator<<(std::ostream& os, const dsa::double_hash& obj)
{
  for (size_t i = 0; i < obj.m_data.size(); ++i)
    {
      os << '[' << i << ']';
      if (obj.m_data[i].first)
        os << obj.m_data[i].first->first << ' ' << obj.m_data[i].first->second;
      else if (obj.m_data[i].second)
        os << "DELETED";
      os << std::endl;
    }
  return os ;
}