#include "onepass/field.hpp"

#include <iostream>

#include "onepass/no_property_set_exception.hpp"

namespace onepass
{
  namespace core
  {
    std::ostream &operator<<(std::ostream &os, const Field &field)
    {
      if (field.history_.empty())
        throw no_property_set_exception();
      os << field.history_.back().val_.type_name_ << ":" << field.history_.back().val_.val_;
      return os;
    }
  }  // namespace core
}  // namespace onepass

using namespace onepass::core;

Field::Field()
{
}

Field::Field(FieldType fieldType, std::string value)
{
  if (fieldType == FieldType::other)
    throw std::invalid_argument("Property type cannot be \"other\" without a name");
  history_.push_back({ 0, { fieldType, "", value } });
}

Field::Field(std::string name, std::string value)
{
  history_.push_back({ 0, { typeFromString(name), name, value } });
}

FieldType Field::getFieldType() const
{
  if (history_.empty())
    throw no_property_set_exception();
  const_cast<Field *>(this)->history_.back().seen();
  return history_.back().val_.type_;
}

std::string Field::getValue() const
{
  if (history_.empty())
    throw no_property_set_exception();
  const_cast<Field *>(this)->history_.back().seen();
  return history_.back().val_.val_;
}

std::string Field::getName() const
{
  if (history_.empty())
    throw no_property_set_exception();
  const_cast<Field *>(this)->history_.back().seen();
  return history_.back().val_.type_name_;
}

void Field::setValue(const std::string newValue)
{
  if (history_.empty())
    throw no_property_set_exception();
  // if newValue == old, skip setting the value
  if (newValue == history_.back().val_.val_)
    return;
  if (history_.size() >= UINT_MAX)
    throw std::out_of_range("Max limit reached");
  unsigned id = static_cast<unsigned>(history_.size());
  Trackable<FieldRecord> newRecord{ id };
  newRecord.val_.type_ = history_.back().val_.type_;
  newRecord.val_.type_name_.assign(history_.back().val_.type_name_);
  newRecord.val_.val_.assign(newValue);

  history_.push_back(newRecord);
}

void Field::printChanges()
{
  for (auto value : history_)
  {
    std::cout << "\t\tId: " << value.getId() << " Accessed: " << value.toString(value.getAccessed())
              << " Created: " << value.toString(value.getCreated()) << " Name: " << value.val_.type_name_
              << " Value: " << value.val_.val_ << std::endl;
  }
}

void Field::printBack()
{
  if (history_.empty())
    throw no_property_set_exception();
  std::cout << "Name: " << history_.back().val_.val_ << " Type: " << history_.back().val_.type_name_ << std::endl;
}

size_t Field::getChangesCount() const
{
  return history_.size();
}

bool operator==(const Field &first, const Field &second)
{
  return (
      first.getFieldType() == second.getFieldType() && first.getValue() == second.getValue() &&
      first.getName() == second.getName());
}

bool operator!=(const Field &first, const Field &second)
{
  return !(first == second);
}

Field &Field::operator=(Field &other)
{
  history_ = other.history_;
  return *this;
}