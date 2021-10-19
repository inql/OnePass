#include "onepass/entry.hpp"

#include <iostream>

namespace onepass
{
  namespace core
  {
    std::ostream &operator<<(std::ostream &os, const Entry &entry)
    {
      for (auto f : entry.fields_)
        os << "\t" << f.second << std::endl;
      os << std::endl;
      return os;
    }
  }  // namespace core
}  // namespace onepass

using namespace onepass::core;

Entry::Entry()
{
}

Entry::Entry(std::string val)
{
  val_.push_back({ 0, { val } });
}

void Entry::print_changes(bool show)
{
  std::cout << "Entry contents:" << std::endl;
  for (auto f : fields_)
  {
    std::cout << "\t\t";
    f.second.printChanges();
  }
  if (show)
  {
    std::cout << "\t"
              << "Changes recorded:" << std::endl;
    for (auto v : val_)
    {
      std::cout << "\t\tId: " << v.getId() << " Accessed: " << v.toString(v.getAccessed())
                << " Created: " << v.toString(v.getCreated()) << " Value: " << v.val_.val_ << std::endl;
    }
  }
}

std::string Entry::getValue() const
{
  if (!val_.empty())
    return std::string{ val_.back().val_.val_ };
  return std::string{ "" };
}

void Entry::setValue(const std::string newValue)
{
  unsigned id = static_cast<unsigned>(val_.size());
  val_.push_back({ id, std::string{ newValue } });
}

void Entry::addField(const FieldType fieldType, const std::string value)
{
  Field newField{ fieldType, value };
  addField(newField);
}

void Entry::addField(const std::string name, const std::string value)
{
  Field newField{ name, value };
  addField(newField);
}

void Entry::addField(const Field &field)
{
  if (field.getValue().empty())
    throw std::invalid_argument("Added data cannot be empty");
  if (!doesFieldExists(field.getFieldType()))
    fields_.emplace(field.getName(), field);
  else
    throw std::invalid_argument("Field already exists in given entry");
}

void Entry::updateField(const FieldType fieldType, const std::string value)
{
  Field field{ fieldType, value };
  updateField(field);
}

void Entry::updateField(const std::string name, const std::string value)
{
  Field field{ name, value };
  updateField(field);
}

void Entry::updateField(const Field &field)
{
  if (doesFieldExists(field.getName()))
    fields_[field.getName()].setValue(field.getValue());
  else
    throw std::invalid_argument("Field doesn't exist in given entry");
}

bool Entry::doesFieldExists(const FieldType fieldType)
{
  return (fields_.find(typeToString(fieldType)) != fields_.end());
}

bool Entry::doesFieldExists(const std::string name)
{
  return (fields_.find(name) != fields_.end());
}

std::map<std::string, Field> Entry::getFields()
{
  return fields_;
}

Entry &Entry::operator=(Entry &other)
{
  fields_ = other.fields_;
  val_ = other.val_;
  return *this;
}