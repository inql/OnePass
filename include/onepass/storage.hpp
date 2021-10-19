#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>

#include "onepass/database.hpp"

using namespace onepass::core;

namespace onepass
{
  namespace storage
  {
    enum class EncodeType
    {
      None,
      Url,
      Base64
    };
    enum class EncryptType
    {
      None,
      Salsa2
    };

    class Storage
    {
     public:
      static void read(
          Database &database,
          const std::string password,
          const std::string filename,
          EncodeType encodeType = EncodeType::None,
          EncryptType encryptType = EncryptType::Salsa2);
      static void save(
          const Database &database,
          const std::string filename,
          EncodeType encodeType = EncodeType::None,
          EncryptType encryptType = EncryptType::Salsa2);
      static bool doesFileExists(std::string const path);
      static std::string encode(const std::string &value, EncodeType encodeType);
      static std::string decode(const std::string &value, EncodeType encodeType);
      static std::string decode64(const std::string &value);
      static std::string encode64(const std::string &value);
      static std::string decodeUrl64(const std::string &value);
      static std::string encodeUrl64(const std::string &value);
    };

  }  // namespace storage
}  // namespace onepass

#endif
