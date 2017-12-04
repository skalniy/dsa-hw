#include "cuckoo.hxx"

#include <cassert>
#include <ctime>
#include <cmath>
#include <unordered_set>

using namespace dsa;


cuckoo::universal_hash::universal_hash(std::size_t _sz)
: sz(_sz)
{
  a = std::rand() % (RAND_MAX - 1) + 1;
  b = std::rand();
  std::cerr << a << ' ' << b <<std::endl;
}

cuckoo::cuckoo(std::size_t sz)
: m_table
    { 
      std::vector<std::unique_ptr<data_t>>(sz), 
      std::vector<std::unique_ptr<data_t>>(sz) 
    },
  m_size(0),
  m_hash{ universal_hash(sz), universal_hash(sz) }
{
  std::srand(std::time(0));
}

std::size_t
cuckoo::universal_hash::operator()(const int x)
{ 
  static constexpr std::uint64_t prime = 2147483659;
  return ((a*x + b) % prime) % sz; 
}

bool
cuckoo::insert(const int key, const int data)
{ 
  if (this->search(key))
    return false;

  if ((m_table[0].size() + 1) / 2 < (m_size + 1))
    m_rehash(m_table[0].size() * 2);

  for (std::size_t i = 0; i < m_table.size(); ++i)
    {
      const std::size_t h = m_hash[i](key);
      if (m_table[i][h])
        continue;
      
      m_table[i][h].reset(new data_t(key, data));
      ++m_size;
      return true;
    }

  // choose hashing index
  const std::size_t to_insert_idx = std::rand() % 2;
  const std::size_t to_insert_hash = m_hash[to_insert_idx](key);

  // put to chosen place
  std::unique_ptr<data_t> extracted_ptr(m_table[to_insert_idx][to_insert_hash].release());
  m_table[to_insert_idx][to_insert_hash].reset(new data_t(key, data));

  std::size_t idx = to_insert_idx ^ 1;
  std::size_t h = m_hash[idx](extracted_ptr->first);
  while (to_insert_idx != idx && to_insert_hash != h)
    {
      std::unique_ptr<data_t> tmp_ptr(m_table[idx][h].release());
      m_table[idx][h].reset(extracted_ptr.release());
      if (!tmp_ptr)
        {
          ++m_size;
          return true;
        }
      
      extracted_ptr.reset(tmp_ptr.release());
      idx ^= 1;
      std::size_t h = m_hash[idx](extracted_ptr->first);
    }

  // if cycle - rehash
  m_rehash(m_table[0].size());
  return this->insert(extracted_ptr->first, extracted_ptr->second);
}

bool
cuckoo::erase(const int key)
{ 
  for (std::size_t idx = 0; idx < m_table.size(); ++idx)
    {
      const std::size_t h = m_hash[idx](key);
      if (m_table[idx][h] && m_table[idx][h]->first == key)
        {
          m_table[idx][h].release();
          --m_size;
          return true;
        }
    }
  
  return false;
}

std::experimental::optional<int>
cuckoo::search(const int key)
{
  for (std::size_t idx = 0; idx < m_table.size(); ++idx)
    {
      const std::size_t h = m_hash[idx](key);
      if (m_table[idx][h] && m_table[idx][h]->first == key)
          return std::experimental::make_optional(m_table[idx][h]->second);
    }

  return std::experimental::optional<int>();
}

void
cuckoo::m_rehash(const std::size_t new_sz)
{
  std::array<std::vector<std::unique_ptr<data_t>>, 2> old_table
    {
      std::vector<std::unique_ptr<data_t>>(new_sz), 
      std::vector<std::unique_ptr<data_t>>(new_sz)
    };
  std::swap(old_table, m_table);

  m_size = 0;

  for (std::size_t i = 0; i < m_hash.size(); ++i)
    m_hash[i] = std::move(universal_hash(new_sz));
  
  for (std::size_t i = 0; i < old_table.size(); ++i)
    for (std::size_t j = 0; j < old_table[i].size(); ++j)
      if (old_table[i][j])
        {
          this->insert(old_table[i][j]->first, old_table[i][j]->second);
          assert(this->search(old_table[i][j]->first) == old_table[i][j]->second);
        }
}

std::ostream&
dsa::operator<<(std::ostream& os, const dsa::cuckoo& obj)
{
  for (std::size_t i = 0; i < obj.m_table[0].size(); ++i)
    {
      os << '[' << i << ']';
      if (obj.m_table[0][i])
        os << obj.m_table[0][i]->first << ' ' << obj.m_table[0][i]->second;
      else
        os << "\t\t";
      if (obj.m_table[1][i])
        os << '\t' << obj.m_table[1][i]->first << ' ' << obj.m_table[1][i]->second;
      os << '\n';
    }
  return os ;
}
