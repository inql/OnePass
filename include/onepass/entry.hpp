#ifndef ENTRY_HPP_
#define ENTRY_HPP_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <ctime>
#include <map>
#include <string>

#include "onepass/field.hpp"
#include "onepass/fieldRecord.hpp"
#include "onepass/fieldType.hpp"
#include "onepass/stringRecord.hpp"
#include "trackable.hpp"
namespace onepass
{
  namespace core
  {
    typedef std::list<Trackable<StringRecord>> StringHistory;

    class Entry
    {
     private:
      friend class boost::serialization::access;
      StringHistory val_;
      std::map<std::string, Field> fields_;
      void addField(const Field &field);
      void updateField(const Field &field);

     public:
      Entry();
      Entry(std::string val);
      template<typename Archive>
      void serialize(Archive &ar, const unsigned int version)
      {
        ar &val_;
        ar &fields_;
      }
      void print_changes(bool show = false);
      std::string getValue() const;
      void setValue(const std::string);

      friend std::ostream &operator<<(std::ostream &os, const Entry &);

      void addField(const FieldType, const std::string);
      void addField(const std::string, const std::string);

      void updateField(const FieldType, const std::string);
      void updateField(const std::string name, const std::string value);

      bool doesFieldExists(const FieldType);
      bool doesFieldExists(const std::string);
      std::map<std::string, Field> getFields();

      Entry &operator=(Entry &other);
    };

  }  // namespace core
}  // namespace onepass

#endif  // ENTRY_HPP_