#include "double_hash.hxx"

#include <iostream>

namespace {
  std::size_t
  hash1(const int key, const std::size_t m)
  { return key % m; }

  std::size_t
  hash2(const int key, const std::size_t m)
  { return (key % (m - 1)) + 1; }
} //namespace

using namespace dsa;

double_hash::double_hash(std::size_t sz)
: m_data(sz), m_size(0)
{ }

bool
double_hash::insert(const int key, const int data)
{ 
  if ((m_data.size() + 1) / 2 < (m_size + 1))
    m_rehash();
  const std::size_t j1 = hash1(key, m_data.size());
  const std::size_t j2 = hash2(key, m_data.size());
  for (size_t i = 0; i < m_data.size(); ++i)
    {
      size_t j = (j1 + i * j2) % m_data.size();
      if (!m_data[j].first || m_data[j].second)
        {
          m_data[j].first.reset(new std::pair<int, int>(key, data));
          ++m_size;
          return true;
        }
      else if (m_data[j].first->first == key)
        return false;
    }
  return false;
}

bool
double_hash::erase(const int key)
{ 
  std::size_t j1 = hash1(key, m_data.size());
  std::size_t j2 = hash2(key, m_data.size());
  for (size_t i = 0; i < m_data.size(); ++i)
    {
      size_t j = (j1 + i * j2) % m_data.size();
      if (!m_data[j].first) 
        return false;
      if (m_data[j].first->first == key)
        {
          m_data[j].first.release();
          m_data[j].second = true;
          --m_size;
          return true;
        }
    }
  return false;
}

std::experimental::optional<int>
double_hash::search(const int key)
{
  std::size_t j1 = hash1(key, m_data.size());
  std::size_t j2 = hash2(key, m_data.size());
  for (size_t i = 0; i < m_data.size(); ++i)
    {
      size_t j = (j1 + i * j2) % m_data.size();
      if (!m_data[j].first) 
        return std::experimental::optional<int>();
      if (m_data[j].first->first == key)
        return std::experimental::make_optional(m_data[j].first->second);
    }
  return std::experimental::optional<int>();
}

void
double_hash::m_rehash()
{
  std::vector<std::pair<std::unique_ptr<std::pair<int, int>>, bool>> new_data(m_data.size() * 2);
  for (auto& el : m_data)
    {
      if (!el.first || el.second)
        continue;
      std::size_t j1 = hash1(el.first->first, new_data.size());
      std::size_t j2 = hash2(el.first->first, new_data.size());
      for (size_t i = 0; i < m_data.size(); ++i)
        {
          size_t j = (j1 + i * j2) % new_data.size();
          if (!new_data[j].first || new_data[j].second)
            {
              new_data[j].first.reset(el.first.release());
              continue;
            }
        }
    }
  m_data = std::move(new_data);
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