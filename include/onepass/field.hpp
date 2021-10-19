#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <ctime>
#include <map>
#include <string>

#include "onepass/fieldRecord.hpp"
#include "onepass/no_property_set_exception.hpp"
#include "trackable.hpp"
namespace onepass
{
  namespace core
  {
    typedef std::list<Trackable<FieldRecord>> FieldHistory;

  class Field
    {
     private:
      FieldHistory history_;
      friend class boost::serialization::access;
      template<typename Archive>
      void serialize(Archive &ar, const unsigned int)
      {
        ar &history_;
      }

     public:
      Field();
      Field(FieldType, std::string);
      Field(std::string, std::string);
      FieldType getFieldType() const;
      std::string getValue() const;
      std::string getName() const;
      void setValue(const std::string);
      void printChanges();
      void printBack();
      size_t getChangesCount() const;

      friend std::ostream &operator<<(std::ostream &os, const Field &);

      Field &operator=(Field &other);
    };

  }  // namespace core
}  // namespace onepass

#endif  // FIELD_HPP_