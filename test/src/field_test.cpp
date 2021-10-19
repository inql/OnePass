#include "onepass/field.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

using namespace onepass::core;

TEST(FieldTest, field_creation_fieldtype)
{
  Field f = { FieldType::username, "inql" };

  ASSERT_EQ(f.getName(), typeToString(FieldType::username));
  ASSERT_EQ(f.getValue(), "inql");
  ASSERT_EQ(f.getFieldType(), FieldType::username);
  ASSERT_EQ(f.getChangesCount(), 1);
}

TEST(FieldTest, field_creation_name_type)
{
  Field f = { "username", "inql" };

  ASSERT_EQ(f.getName(), typeToString(FieldType::username));
  ASSERT_EQ(f.getValue(), "inql");
  ASSERT_EQ(f.getFieldType(), FieldType::username);
  ASSERT_EQ(f.getChangesCount(), 1);
}

TEST(FieldTest, field_creation_name_other_type)
{
  Field f = { "totally_custom", "some_data" };

  ASSERT_EQ(f.getName(), "other");
  ASSERT_EQ(f.getValue(), "some_data");
  ASSERT_EQ(f.getFieldType(), FieldType::other);
  ASSERT_EQ(f.getChangesCount(), 1);
}

TEST(FieldTest, field_creation_wrong_type)
{
  try
  {
    Field f = { FieldType::other, "inql" };
    FAIL() << "Expected std::invalid_argument";
  }
  catch (std::invalid_argument const& err)
  {
    EXPECT_EQ(err.what(), std::string("Property type cannot be \"other\" without a name"));
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(FieldTest, field_update)
{
  Field f = { "username", "inql" };

  ASSERT_EQ(f.getName(), typeToString(FieldType::username));
  ASSERT_EQ(f.getValue(), "inql");
  ASSERT_EQ(f.getFieldType(), FieldType::username);
  ASSERT_EQ(f.getChangesCount(), 1);

  f.setValue("new_username");
  ASSERT_EQ(f.getValue(), "new_username");
  ASSERT_EQ(f.getChangesCount(), 2);
}

TEST(FieldTest, field_update_no_change)
{
  Field f = { "username", "inql" };

  ASSERT_EQ(f.getName(), typeToString(FieldType::username));
  ASSERT_EQ(f.getValue(), "inql");
  ASSERT_EQ(f.getFieldType(), FieldType::username);
  ASSERT_EQ(f.getChangesCount(), 1);

  f.setValue("inql");
  ASSERT_EQ(f.getValue(), "inql");
  ASSERT_EQ(f.getChangesCount(), 1);
}

TEST(FieldTest, field_printChangesTest)
{
  Field f = { "username", "inql" };
  testing::internal::CaptureStdout();
  f.printChanges();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_THAT(output, testing::HasSubstr("Id: 0"));
  EXPECT_THAT(output, testing::HasSubstr("Accessed:"));
  EXPECT_THAT(output, testing::HasSubstr("Created:"));
  EXPECT_THAT(output, testing::HasSubstr("Name: username"));
  EXPECT_THAT(output, testing::HasSubstr("Value: inql"));
}

TEST(FieldTest, field_printBackTest)
{
  Field f = { "username", "inql" };
  testing::internal::CaptureStdout();
  f.printBack();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_THAT(output, testing::HasSubstr("Name: inql Type: username"));
}

TEST(FieldTest, field_no_property_set_get_value)
{
  Field f;
  try
  {
    f.getValue();
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
  catch (no_property_set_exception const& err)
  {
    EXPECT_EQ(err.what(), std::string("No property set"));
  }
  catch (...)
  {
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
}

TEST(FieldTest, field_no_property_set_print)
{
  Field f;
  try
  {
    std::cout << f;
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
  catch (no_property_set_exception const& err)
  {
    EXPECT_EQ(err.what(), std::string("No property set"));
  }
  catch (...)
  {
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
}

TEST(FieldTest, field_no_property_set_get_field_type)
{
  Field f;
  try
  {
    f.getFieldType();
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
  catch (no_property_set_exception const& err)
  {
    EXPECT_EQ(err.what(), std::string("No property set"));
  }
  catch (...)
  {
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
}

TEST(FieldTest, field_no_property_set_get_name)
{
  Field f;
  try
  {
    f.getName();
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
  catch (no_property_set_exception const& err)
  {
    EXPECT_EQ(err.what(), std::string("No property set"));
  }
  catch (...)
  {
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
}

TEST(FieldTest, field_no_property_set_set_value)
{
  Field f;
  try
  {
    f.setValue("foo");
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
  catch (no_property_set_exception const& err)
  {
    EXPECT_EQ(err.what(), std::string("No property set"));
  }
  catch (...)
  {
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
}

TEST(FieldTest, field_no_property_set_print_back)
{
  Field f;
  try
  {
    f.printBack();
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
  catch (no_property_set_exception const& err)
  {
    EXPECT_EQ(err.what(), std::string("No property set"));
  }
  catch (...)
  {
    FAIL() << "Expected onepass::core::no_property_set_exception";
  }
}