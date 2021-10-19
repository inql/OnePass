#include "onepass/database.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace onepass::core;

class DatabaseTest : public ::testing::Test
{
 protected:
  Entry createEntry(std::string name)
  {
    Entry en{ name };
    en.addField(FieldType::username, "inql");
    en.addField(FieldType::email, "user@domain.com");
    en.addField(FieldType::url, "https://www.domain.com");

    return en;
  }
};

TEST_F(DatabaseTest, database_creation_empty)
{
  Database* db = new Database;

  EXPECT_TRUE(db != nullptr);
}

TEST_F(DatabaseTest, database_creation_password)
{
  Database db{ "mylongpasswordnameneededfortesting" };

  EXPECT_THAT(db.getPassword(), "mylongpasswordnameneededfortesting");
}

TEST_F(DatabaseTest, database_creation_size_too_short)
{
  try
  {
    Database db{ "tooshortpassword" };
    FAIL() << "Expected std::invalid_argument";
  }
  catch (std::invalid_argument const& err)
  {
    EXPECT_EQ(err.what(), std::string("The size of password is invalid!"));
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST_F(DatabaseTest, database_addEntry_by_string)
{
  Database db{ "mylongpasswordnameneededfortesting" };

  db.addEntry("example_entry", "example_entry");

  EXPECT_EQ(db.count(), 1);
}

TEST_F(DatabaseTest, database_addEntry_by_entry)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry{ "example_entry" };

  db.addEntry("example_entry", entry);

  EXPECT_EQ(db.count(), 1);
}

TEST_F(DatabaseTest, database_updateEntry)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");

  db.addEntry("example_entry", entry);
  entry.updateField(FieldType::username, "new_username");

  // verify that entry in db contains old record
  Entry dbEntry = db.getEntry("example_entry");
  EXPECT_EQ(dbEntry.getFields()["username"].getValue(), "inql");

  // update entry
  db.updateEntry("example_entry", entry);

  // verify if value has changed
  Entry dbUpdatedEntry = db.getEntry("example_entry");
  EXPECT_EQ(dbUpdatedEntry.getFields()["username"].getValue(), "new_username");
}

TEST_F(DatabaseTest, database_updateEntry_extra_field_included)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");

  db.addEntry("example_entry", entry);
  entry.addField(FieldType::tags, "example_tag");

  // verify that entry in db contains old record
  Entry dbEntry = db.getEntry("example_entry");
  EXPECT_FALSE(dbEntry.doesFieldExists(FieldType::tags));

  // update entry
  db.updateEntry("example_entry", entry);

  // verify if value has changed
  Entry dbUpdatedEntry = db.getEntry("example_entry");
  EXPECT_TRUE(dbUpdatedEntry.doesFieldExists(FieldType::tags));
  EXPECT_EQ(dbUpdatedEntry.getFields()["tags"].getValue(), "example_tag");
}

TEST_F(DatabaseTest, database_updateEntry_entry_name_changed)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");

  db.addEntry("example_entry", entry);
  entry.setValue("new_entry");

  // verify that entry in db contains old record
  Entry dbEntry = db.getEntry("example_entry");
  EXPECT_EQ(dbEntry.getValue(), "example_entry");

  // update entry
  db.updateEntry("example_entry", entry);

  // verify if value has changed
  Entry dbUpdatedEntry = db.getEntry("example_entry");
  EXPECT_EQ(dbUpdatedEntry.getValue(), "new_entry");
}

TEST_F(DatabaseTest, database_updateEntry_no_entry_with_given_key)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");

  db.updateEntry("example_entry", entry);

  // verify that entry in db is present when updating
  Entry dbEntry = db.getEntry("example_entry");
  EXPECT_EQ(dbEntry.getValue(), "example_entry");
}

TEST_F(DatabaseTest, database_removeEntry_test)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");

  db.updateEntry("example_entry", entry);
  EXPECT_EQ(db.count(), 1);

  // remove entry then check if count is 0
  db.removeEntry("example_entry");
  EXPECT_EQ(db.count(), 0);
}

TEST_F(DatabaseTest, database_getEntry_test)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");

  db.addEntry("example_entry", entry);

  Entry dbEntry = db.getEntry("example_entry");
  EXPECT_EQ(dbEntry.getValue(), "example_entry");
}

TEST_F(DatabaseTest, database_getEntry_test_no_key_found)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");

  db.addEntry("example_entry", entry);

  try
  {
    Entry dbEntry = db.getEntry("example_entry1");

    FAIL() << "Expected std::invalid_argument";
  }
  catch (std::invalid_argument const& err)
  {
    EXPECT_EQ(err.what(), std::string("The key does not exists"));
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST_F(DatabaseTest, database_search_test)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");
  entry.setValue("mypassword");

  db.addEntry("example_entry", entry);
  testing::internal::CaptureStdout();
  db.search("entry");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_THAT(output, testing::HasSubstr("username:inql"));
  EXPECT_THAT(output, testing::HasSubstr("email:user@domain.com"));
  EXPECT_THAT(output, testing::HasSubstr("url:https://www.domain.com"));
  EXPECT_THAT(output, testing::Not(testing::HasSubstr("mypassword")));
  EXPECT_THAT(output, testing::HasSubstr("Total results found: 1"));
}

TEST_F(DatabaseTest, database_search_test_show_all)
{
  Database db{ "mylongpasswordnameneededfortesting" };
  Entry entry = createEntry("example_entry");
  entry.setValue("mypassword");

  db.addEntry("example_entry", entry);
  testing::internal::CaptureStdout();
  db.show("example_entry", true, true);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_THAT(output, testing::HasSubstr("example_entry"));
  EXPECT_THAT(output, testing::HasSubstr("user@domain.com"));
  EXPECT_THAT(output, testing::HasSubstr("https://www.domain.com"));
  EXPECT_THAT(output, testing::HasSubstr("[mypassword]"));
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}