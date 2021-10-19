#include "onepass/stringRecord.hpp"

#include <iostream>

namespace onepass
{
  namespace core
  {
    std::ostream &operator<<(std::ostream &os, const StringRecord sr)
    {
      os << sr.val_;
      return os;
    }
  }  // namespace core
}  // namespace onepass

using namespace onepass::core;

StringRecord::StringRecord()
{
}

StringRecord::StringRecord(std::string val) : val_{ val }
{
}

void StringRecord::serialize(boost::archive::text_iarchive &iar, const unsigned int)
{
  iar &val_;
}
void StringRecord::serialize(boost::archive::text_oarchive &oar, const unsigned int)
{
  oar &val_;
}