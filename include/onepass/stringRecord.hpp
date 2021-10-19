#ifndef STRINGRECORD_HPP
#define STRINGRECORD_HPP

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

namespace onepass
{
  namespace core
  {
    class StringRecord
    {
     public:
      std::string val_;
      StringRecord();
      StringRecord(std::string val);
      friend class boost::serialization::access;
      void serialize(boost::archive::text_iarchive &iar, const unsigned int);
      void serialize(boost::archive::text_oarchive &oar, const unsigned int);
      friend std::ostream &operator<<(std::ostream &os, const StringRecord sr);
    };

  }  // namespace core
}  // namespace onepass

#endif  // STRINGRECORD_HPP