#include <gtest/gtest.h>

#include "onepass/fieldRecord.hpp"

using namespace onepass::core;

TEST(FieldRecordTest, field_record_creation_empty)
{
  FieldRecord fr;

  ASSERT_EQ(fr.type_name_, "other");
}

TEST(FieldRecordTest, field_record_creation_filled)
{
  FieldRecord fr{ FieldType::username, "username", "inql" };

  ASSERT_EQ(fr.type_name_, "username");
  ASSERT_EQ(fr.val_, "inql");
}

TEST(FieldRecordTest, field_record_creation_type_provided){
  FieldRecord fr {FieldType::username, "inql"};

  ASSERT_EQ(fr.type_, FieldType::username);
  ASSERT_EQ(fr.type_name_, "username");
  ASSERT_EQ(fr.val_, "inql");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}