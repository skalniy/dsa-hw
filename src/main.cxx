#include "stl_wrapper.hxx"

#include <cstdlib>

#include <iostream>
#include <memory> // unique_ptr
#include <string>

int
main()
{
  std::unique_ptr<dsa::hash_table> ht_ptr = std::make_unique<dsa::stl_wrapper>();

  while (!std::cin.eof() && !std::cin.fail())
    {
      std::string input;
      std::cin >> input;

      if (input == "add")
        try
          {
            std::string key_str, data_str;
            std::cin >> key_str >> data_str;
            int key = std::stoi(key_str);
            int data = std::stoi(data_str);
            std::cout << (ht_ptr->insert(key, data) ? "OK" : "FAIL" )<< std::endl;
          }
        catch (std::invalid_argument& e)
          { 
            std::cout << "error" << std::endl; 
            return EXIT_FAILURE;
          }
      else if (input == "search") 
        try
          {
            std::string key_str;
            std::cin >> key_str;
            auto result = ht_ptr->search(std::stoi(key_str));
            if (result)
              std::cout << *result << std::endl;
            else
            std::cout << "null" << std::endl;
          }
        catch (std::invalid_argument& e)
          { 
            std::cout << "error" << std::endl; 
            return EXIT_FAILURE;
          }
      else if (input == "delete")
        try
          {
            std::string key_str;
            std::cin >> key_str;
            std::cout << (ht_ptr->erase(std::stoi(key_str)) ? "OK" : "FAIL") << std::endl;
          }
        catch (std::invalid_argument& e)
          { 
            std::cout << "error" << std::endl; 
            return EXIT_FAILURE;
          }
      else if (!input.empty())
        { 
          std::cout << "error" << std::endl; 
          return EXIT_FAILURE;
        }
    }

  return EXIT_SUCCESS;
}