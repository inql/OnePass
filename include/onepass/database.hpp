#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include "onepass/entry.hpp"

namespace onepass
{
  namespace core
  {
    class Database
    {
      int version_;
      std::string password_;
      std::map<std::string, Entry> entries_;
      friend class boost::serialization::access;

      template<typename Archive>
      void serialize(Archive &ar, const unsigned int version)
      {
        ar &version_;
        ar &password_;
        ar &entries_;
      }

      bool get(std::string);

     public:
      Database();
      Database(std::string);
      void addEntry(std::string, std::string);
      void addEntry(std::string, Entry);
      void updateEntry(std::string, Entry);
      void removeEntry(std::string);
      Entry getEntry(std::string);
      void show(std::string, bool history = false, bool pwd = false);
      void list();
      std::string getPassword() const;
      void search(std::string, bool showSecure = false, bool history = false);
      size_t count() const;
      static const size_t MIN_PASSWORD;
      static const std::string VERSION_STR;
    };

  }  // namespace core
}  // namespace onepass
#endif  // DATABASE_HPP_
