#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory> // unique_ptr
#include <string> // to_string

#include HEADER_NAME

int
main(int argc, char *argv[])
{
  if (argc < 3)
    return EXIT_FAILURE;
  
  std::ifstream ifs(argv[1]);
  std::ofstream ofs(argv[2]);
  ofs.setf(std::ios_base::boolalpha);

  std::size_t ht_sz = 0;
  ifs >> ht_sz;

  std::unique_ptr<dsa::hash_table> ht_ptr(new dsa::TABLE_NAME(ht_sz));
  while (!ifs.eof() && !ifs.fail())
    {
      std::clock_t c_start, c_end;
      std::string cmd;
      ifs >> cmd;

      if (cmd == "min") 
        {
          c_start = std::clock();
          auto result = ht_ptr->min();
          c_end = std::clock();

          if (result)
            ofs << result->first << ' ' << result->second << std::endl;
          else
            ofs << 'null' << std::endl;
        }
      else if (cmd == "max") 
        {
          c_start = std::clock();
          auto result = ht_ptr->max();
          c_end = std::clock();

          if (result)
            ofs << result->first << ' ' << result->second << std::endl;
          else
            ofs << 'null' << std::endl;
        }
      else {
        int key;
        ifs >> key;

        if (cmd == "add")
          {
            int data;
            ifs >> data;

            c_start = std::clock();
            auto result = ht_ptr->insert(key, data);
            c_end = std::clock();

            ofs << result << std::endl;
          }
        else if (cmd == "search") 
          {
            c_start = std::clock();
            auto result = ht_ptr->search(key);
            c_end = std::clock();

            ofs << (result ? std::to_string(*result) : "null") << std::endl;
          }
        else if (cmd == "delete")
          {
            c_start = std::clock();
            auto result = ht_ptr->erase(key);
            c_end = std::clock();

            ofs << result << std::endl;
          }
      }
      if (!cmd.empty())  
        std::cerr 
          << cmd << ' ' 
          << ht_ptr->size() << ' ' 
          << (c_end-c_start)
          << std::endl;
    }

  return EXIT_SUCCESS;
}