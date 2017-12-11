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
  if ((m_size + 1 > (m_data.size() + 1) / 2) && !this->search(key))
    m_rehash();
  
  std::array<std::size_t, 2> h{ hash[0](key), hash[1](key) };
  std::experimental::optional<std::size_t> to_insert_id;

  std::size_t i = 0;
  for (; i < m_data.size(); ++i)
    {
      std::size_t j = (h[0] + i * h[1]) % m_data.size();
      if (m_data[j].first && m_data[j].first->first == key) // if key exists
        return false;

      if (!m_data[j].first || m_data[j].second) // empty slot
        {
          to_insert_id = j;
          break;
        }
    }

  if (!to_insert_id) // if slot not found
    return false;

  // check if key is in next slots
  for (; i < m_data.size(); ++i)
    {
      std::size_t j = (h[0] + i * h[1]) % m_data.size();
      if (m_data[j].first && m_data[j].first->first == key) // if key exists
          return false;
      if (!m_data[j].first && !m_data[j].second) // if empty not marked as deleted
        break;
    }

  m_data[*to_insert_id].first.reset(new data_t{ key, data });
  m_data[*to_insert_id].second = false;
  ++m_size;
  return true;
}

bool
double_hash::erase(const int key)
{ 
  std::array<std::size_t, 2> h{ hash[0](key), hash[1](key) };

  for (std::size_t i = 0; i < m_data.size(); ++i)
    {
      size_t j = (h[0] + i * h[1]) % m_data.size();

      if (m_data[j].first && m_data[j].first->first == key) // if key found
        {
          m_data[j].first.release();
          m_data[j].second = true;
          --m_size;
          return true;
        }
      
      if (!m_data[j].first && !m_data[j].second) // if empty not marked as deleted
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
      
      if (m_data[j].first && m_data[j].first->first == key) // if key found
        return std::experimental::make_optional(m_data[j].first->second);

      if (!m_data[j].first && !m_data[j].second) // if empty not marked as deleted
        return std::experimental::nullopt;
    }
  
  return std::experimental::nullopt;
}

void
double_hash::m_rehash()
{
  std::vector<std::pair<std::unique_ptr<data_t>, bool>> old_data(m_data.size() * 2);
  std::swap(m_data, old_data);

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