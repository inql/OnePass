#include "onepass/database.hpp"

#include <iostream>

using namespace onepass::core;

const std::string Database::VERSION_STR = "0.0.2";
const size_t Database::MIN_PASSWORD = sizeof(char) * 20;

bool Database::get(std::string key)
{
  for (auto e : entries_)
  {
    if (e.first == key)
      return true;
  }
  return false;
}

Database::Database()
{
}

Database::Database(std::string password)
{
  if (password.size() < MIN_PASSWORD)
    throw std::invalid_argument("The size of password is invalid!");
  password_ = password;
}

void Database::addEntry(std::string key, std::string value)
{
  if (!get(key))
  {
    Entry newEntry{ value };
    entries_[key] = newEntry;
  }
}

void Database::addEntry(std::string key, Entry entry)
{
  if (!get(key))
  {
    entries_[key] = entry;
  }
}

void Database::updateEntry(std::string key, Entry updatedEntry)
{
  if (get(key))
  {
    for (auto field : updatedEntry.getFields())
    {
      if (entries_[key].doesFieldExists(field.first))
        entries_[key].updateField(field.second.getFieldType(), field.second.getValue());
      else
        entries_[key].addField(field.second.getFieldType(), field.second.getValue());
    }
    if (entries_[key].getValue() != updatedEntry.getValue() && !updatedEntry.getValue().empty())
      entries_[key].setValue(updatedEntry.getValue());
  }
  else
    entries_[key] = updatedEntry;
}

void Database::removeEntry(std::string key)
{
  if (get(key))
  {
    entries_.erase(key);
  }
}

Entry Database::getEntry(std::string key)
{
  if (get(key))
  {
    return entries_[key];
  }
  throw std::invalid_argument("The key does not exists");
}

void Database::show(std::string key, bool history, bool pwd)
{
  for (auto entry : entries_)
  {
    if (entry.first == key)
    {
      if (pwd)
        std::cout << key << ":[" << entry.second.getValue() << "]" << std::endl;
      else
        std::cout << key << ":" << std::endl;

      if (history)
        entry.second.print_changes(pwd);
      else
        std::cout << entry.second;
    }
  }
}

void Database::list()
{
  for (auto e : entries_)
    show(e.first);
}

std::string Database::getPassword() const
{
  return password_;
}

void Database::search(std::string keyword, bool showSecure, bool history)
{
  std::cout << "Search results for keyword: " << keyword << std::endl;
  unsigned int resultsFound = 0;
  for (auto e : entries_)
  {
    std::size_t found = e.first.find(keyword);
    if (found != std::string::npos)
    {
      show(e.first, showSecure, history);
      resultsFound++;
    }
  }
  std::cout << "Total results found: " << resultsFound << std::endl;
}

size_t Database::count() const
{
  return entries_.size();
}