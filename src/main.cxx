// #include "stl_wrapper.hxx"

#include <cstdlib>

#include <fstream>
#include <iostream>
#include <memory> // unique_ptr
#include <string>

#include HEADER_NAME

int
main(int argc, char *argv[])
{
  if (argc < 3)
    return EXIT_FAILURE;
  std::ifstream ifs(argv[1]);
  std::ofstream ofs(argv[2]);

  std::unique_ptr<dsa::hash_table> ht_ptr = std::make_unique<dsa::TABLE_NAME>();

  while (!ifs.eof() && !ifs.fail())
    {
      std::string input;
      ifs >> input;

      if (input == "add")
        try
          {
            std::string key_str, data_str;
            ifs >> key_str >> data_str;
            int key = std::stoi(key_str);
            int data = std::stoi(data_str);
            ofs << (ht_ptr->insert(key, data) ? "OK" : "FAIL" ) << std::endl;
          }
        catch (std::invalid_argument& e)
          { 
            ofs << "error" << std::endl; 
            return EXIT_FAILURE;
          }
      else if (input == "search") 
        try
          {
            std::string key_str;
            ifs >> key_str;
            auto result = ht_ptr->search(std::stoi(key_str));
            if (result)
              ofs << *result << std::endl;
            else
            ofs << "null" << std::endl;
          }
        catch (std::invalid_argument& e)
          { 
            ofs << "error" << std::endl; 
            return EXIT_FAILURE;
          }
      else if (input == "delete")
        try
          {
            std::string key_str;
            ifs >> key_str;
            ofs << (ht_ptr->erase(std::stoi(key_str)) ? "OK" : "FAIL") << std::endl;
          }
        catch (std::invalid_argument& e)
          { 
            ofs << "error" << std::endl; 
            return EXIT_FAILURE;
          }
      else if (!input.empty())
        { 
          ofs << "error" << std::endl; 
          return EXIT_FAILURE;
        }
    }

  return EXIT_SUCCESS;
}