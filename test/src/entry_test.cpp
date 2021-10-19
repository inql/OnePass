#include "onepass/entry.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace onepass::core;

TEST(EntryTest, entry_creation_empty)
{
  Entry* en = new Entry;

  EXPECT_TRUE(en != nullptr);
}

TEST(EntryTest, entry_creation_initial_value)
{
  Entry en{ "test" };

  EXPECT_THAT(en.getValue(), testing::HasSubstr("test"));
}

TEST(EntryTest, entry_getValue_empty)
{
  Entry en;

  ASSERT_EQ(en.getValue(), "");
}

TEST(EntryTest, entry_setValue)
{
  Entry en{ "test" };

  ASSERT_EQ(en.getValue(), "test");

  en.setValue("newTest");

  ASSERT_EQ(en.getValue(), "newTest");
}

TEST(EntryTest, entryAddField)
{
  Entry en{ "test" };

  en.addField("username", "inql");

  ASSERT_TRUE(en.doesFieldExists("username"));
  ASSERT_TRUE(en.doesFieldExists(FieldType::username));
  ASSERT_EQ(en.getFields()["username"].getValue(), "inql");
}

TEST(EntryTest, entryAddFieldByType)
{
  Entry en{ "test" };

  en.addField(FieldType::username, "inql");

  ASSERT_TRUE(en.doesFieldExists("username"));
  ASSERT_TRUE(en.doesFieldExists(FieldType::username));
  ASSERT_EQ(en.getFields()["username"].getValue(), "inql");
}

TEST(EntryTest, entryAddField_empty_value)
{
  Entry en{ "test" };

  try
  {
    en.addField(FieldType::username, "");
    FAIL() << "Expected std::invalid_argument";
  }
  catch (std::invalid_argument const& err)
  {
    EXPECT_EQ(err.what(), std::string("Added data cannot be empty"));
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(EntryTest, entryAddField_existing_field)
{
  Entry en{ "test" };

  en.addField(FieldType::username, "inql");

  try
  {
    en.addField(FieldType::username, "inql");
    FAIL() << "Expected std::invalid_argument";
  }
  catch (std::invalid_argument const& err)
  {
    EXPECT_EQ(err.what(), std::string("Field already exists in given entry"));
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(EntryTest, entryUpdateField)
{
  Entry en{ "test" };

  en.addField("username", "inql");
  ASSERT_TRUE(en.doesFieldExists("username"));
  ASSERT_TRUE(en.doesFieldExists(FieldType::username));
  ASSERT_EQ(en.getFields()["username"].getValue(), "inql");
  en.updateField("username", "new_username");

  ASSERT_TRUE(en.doesFieldExists("username"));
  ASSERT_TRUE(en.doesFieldExists(FieldType::username));
  ASSERT_EQ(en.getFields()["username"].getValue(), "new_username");
}

TEST(EntryTest, entryUpdateFieldByType)
{
  Entry en{ "test" };

  en.addField(FieldType::username, "inql");
  ASSERT_TRUE(en.doesFieldExists("username"));
  ASSERT_TRUE(en.doesFieldExists(FieldType::username));
  ASSERT_EQ(en.getFields()["username"].getValue(), "inql");
  en.updateField(FieldType::username, "new_username");

  ASSERT_TRUE(en.doesFieldExists("username"));
  ASSERT_TRUE(en.doesFieldExists(FieldType::username));
  ASSERT_EQ(en.getFields()["username"].getValue(), "new_username");
}

TEST(EntryTest, entryUpdateField_doesnt_exist)
{
  Entry en{ "test" };

  try
  {
    en.updateField(FieldType::username, "new_username");
    FAIL() << "Expected std::invalid_argument";
  }
  catch (std::invalid_argument const& err)
  {
    EXPECT_EQ(err.what(), std::string("Field doesn't exist in given entry"));
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(EntryTest, entryPrint)
{
  Entry en{ "test" };
  en.addField(FieldType::username, "inql");
  testing::internal::CaptureStdout();
  std::cout << en << std::endl;
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_THAT(output, testing::HasSubstr("username:inql"));
}

TEST(EntryTest, entryPrintChanges)
{
  Entry en{ "test" };
  en.addField(FieldType::username, "inql");
  en.updateField(FieldType::username, "new_username");
  testing::internal::CaptureStdout();
  en.print_changes();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_THAT(output, testing::HasSubstr("inql"));
  EXPECT_THAT(output, testing::HasSubstr("new_username"));
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}