#include "onepass/storage.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
using namespace onepass::storage;

class StorageTest : public ::testing::Test
{
 protected:
  std::string save_file_name = "db_file";
  std::string load_file_name = "ldb_file";
  std::string db_password = "mylongpasswordnameneededfortesting";
  virtual void TearDown()
  {
    try
    {
      std::filesystem::remove(save_file_name);
      std::filesystem::remove(load_file_name);
    }
    catch (const std::filesystem::filesystem_error& err)
    {
      std::cerr << err.what() << '\n';
    }
  }
};

TEST_F(StorageTest, storage_saveTest_none_salsa2)
{
  Database db{ db_password };
  Storage::save(db, save_file_name);
  EXPECT_TRUE(Storage::doesFileExists(save_file_name));
}

TEST_F(StorageTest, storage_saveTest_base64_salsa2)
{
  Database db{ db_password };
  Storage::save(db, save_file_name, EncodeType::Base64, EncryptType::Salsa2);
  EXPECT_TRUE(Storage::doesFileExists(save_file_name));
}

TEST_F(StorageTest, storage_saveTest_base64_none)
{
  Database db{ db_password };
  Storage::save(db, save_file_name, EncodeType::Base64, EncryptType::None);
  EXPECT_TRUE(Storage::doesFileExists(save_file_name));
}

TEST_F(StorageTest, storage_saveTest_url_none)
{
  Database db{ db_password };
  Storage::save(db, save_file_name, EncodeType::Url, EncryptType::None);
  EXPECT_TRUE(Storage::doesFileExists(save_file_name));
}

TEST_F(StorageTest, storage_saveTest_url_salsa2)
{
  Database db{ db_password };
  Storage::save(db, save_file_name, EncodeType::Url, EncryptType::Salsa2);
  EXPECT_TRUE(Storage::doesFileExists(save_file_name));
}

TEST_F(StorageTest, storage_saveTest_none_none)
{
  Database db{ db_password };
  Storage::save(db, save_file_name, EncodeType::None, EncryptType::None);
  EXPECT_TRUE(Storage::doesFileExists(save_file_name));
}

TEST_F(StorageTest, storage_loadTest_none_salsa2)
{
  Database db{ db_password };
  db.addEntry("test_entry", "test_entry");
  Storage::save(db, load_file_name);
  EXPECT_TRUE(Storage::doesFileExists(load_file_name));
  Database loaded;
  Storage::read(loaded, db_password, load_file_name);

  Entry testEntry = loaded.getEntry("test_entry");

  EXPECT_EQ(testEntry.getValue(), "test_entry");
}

TEST_F(StorageTest, storage_loadTest_base64_salsa2)
{
  Database db{ db_password };
  db.addEntry("test_entry", "test_entry");
  Storage::save(db, load_file_name, EncodeType::Base64, EncryptType::Salsa2);
  EXPECT_TRUE(Storage::doesFileExists(load_file_name));
  Database loaded;
  Storage::read(loaded, db_password, load_file_name, EncodeType::Base64, EncryptType::Salsa2);

  Entry testEntry = loaded.getEntry("test_entry");

  EXPECT_EQ(testEntry.getValue(), "test_entry");
}

TEST_F(StorageTest, storage_loadTest_base64_none)
{
  Database db{ db_password };
  db.addEntry("test_entry", "test_entry");
  Storage::save(db, load_file_name, EncodeType::Base64, EncryptType::None);
  EXPECT_TRUE(Storage::doesFileExists(load_file_name));
  Database loaded;
  Storage::read(loaded, db_password, load_file_name, EncodeType::Base64, EncryptType::None);

  Entry testEntry = loaded.getEntry("test_entry");

  EXPECT_EQ(testEntry.getValue(), "test_entry");
}

TEST_F(StorageTest, storage_loadTest_url_none)
{
  Database db{ db_password };
  db.addEntry("test_entry", "test_entry");
  Storage::save(db, load_file_name, EncodeType::Url, EncryptType::None);
  EXPECT_TRUE(Storage::doesFileExists(load_file_name));
  Database loaded;
  Storage::read(loaded, db_password, load_file_name, EncodeType::Url, EncryptType::None);

  Entry testEntry = loaded.getEntry("test_entry");

  EXPECT_EQ(testEntry.getValue(), "test_entry");
}

TEST_F(StorageTest, storage_loadTest_url_salsa2)
{
  Database db{ db_password };
  db.addEntry("test_entry", "test_entry");
  Storage::save(db, load_file_name, EncodeType::Url, EncryptType::Salsa2);
  EXPECT_TRUE(Storage::doesFileExists(load_file_name));
  Database loaded;
  Storage::read(loaded, db_password, load_file_name, EncodeType::Url, EncryptType::Salsa2);

  Entry testEntry = loaded.getEntry("test_entry");

  EXPECT_EQ(testEntry.getValue(), "test_entry");
}

TEST_F(StorageTest, storage_loadTest_none_none)
{
  Database db{ db_password };
  db.addEntry("test_entry", "test_entry");
  Storage::save(db, load_file_name, EncodeType::None, EncryptType::None);
  EXPECT_TRUE(Storage::doesFileExists(load_file_name));
  Database loaded;
  Storage::read(loaded, db_password, load_file_name, EncodeType::None, EncryptType::None);

  Entry testEntry = loaded.getEntry("test_entry");

  EXPECT_EQ(testEntry.getValue(), "test_entry");
}

TEST_F(StorageTest, storage_encode_decode_test_base64)
{
  std::string test = "this is a example\n s\ttr__ing";
  auto encoded = Storage::encode64(test);
  auto decoded = Storage::decode64(encoded);
  EXPECT_EQ(test, decoded);
}

TEST_F(StorageTest, storage_encode_decode_test_url)
{
  std::string test = "this is a example\n s\ttr__ing";
  auto encoded = Storage::encodeUrl64(test);
  auto decoded = Storage::decodeUrl64(encoded);
  EXPECT_EQ(test, decoded);  
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}