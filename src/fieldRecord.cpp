#include "onepass/fieldRecord.hpp"

#include <iostream>

using namespace onepass::core;

FieldRecord::FieldRecord()
{
  type_name_ = typeToString(type_);
}

FieldRecord::FieldRecord(FieldType type, std::string type_name, std::string val)
    : type_{ type },
      type_name_{ type_name },
      val_{ val }
{
  type_name_ = typeToString(type_);
}

FieldRecord::FieldRecord(FieldType type, std::string val) : type_{ type }, val_{ val }
{
  type_name_ = typeToString(type_);
}

void FieldRecord::serialize(boost::archive::text_iarchive &iar, const unsigned int)
{
  iar &type_;
  iar &val_;
  type_name_ = typeToString(type_);
}

void FieldRecord::serialize(boost::archive::text_oarchive &oar, const unsigned int)
{
  oar &type_;
  oar &val_;
}