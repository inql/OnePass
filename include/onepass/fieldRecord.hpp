#ifndef FIELDRECORD_HPP
#define FIELDRECORD_HPP

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

#include "onepass/fieldType.hpp"

namespace onepass
{
  namespace core
  {
    class FieldRecord
    {
     public:
      FieldType type_;
      std::string type_name_;
      std::string val_;
      FieldRecord();
      FieldRecord(FieldType type, std::string type_name, std::string val);
      FieldRecord(FieldType type, std::string val);

     private:
      friend class boost::serialization::access;
      void serialize(boost::archive::text_iarchive &iar, const unsigned int);
      void serialize(boost::archive::text_oarchive &oar, const unsigned int);
    };

  }  // namespace core
}  // namespace onepass

#endif  // FIELDRECORD_HPP