#include "onepass/storage.hpp"

#include <cryptopp/base64.h>

#include <boost/algorithm/string.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <fstream>
#include <sstream>

#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/salsa.h"
#include "cryptopp/secblock.h"
#include "onepass/database.hpp"

using namespace onepass::storage;

void Storage::read(
    Database &database,
    const std::string password,
    const std::string filename,
    EncodeType encodeType,
    EncryptType encryptType)
{
  if (encryptType == EncryptType::Salsa2)
  {
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::Salsa20::Decryption decryption;
    CryptoPP::SecByteBlock sbb(8);
    memset(sbb, 0x10101110, sbb.size());
    CryptoPP::SHA256().CalculateDigest(
        digest, reinterpret_cast<const CryptoPP::byte *>(password.c_str()), password.length());
    decryption.SetKeyWithIV(digest, CryptoPP::SHA256::DIGESTSIZE, sbb, sbb.size());

    if (encodeType == EncodeType::None)
    {
      std::string decrypted;
      CryptoPP::FileSource database2(
          filename.c_str(), true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(decrypted)));
      std::istringstream iss(decrypted);
      boost::archive::text_iarchive iar(iss);
      iar >> database;
    }
    if (encodeType == EncodeType::Url || encodeType == EncodeType::Base64)
    {
      std::ifstream ifs(filename);
      if (ifs.is_open())
      {
        std::stringstream ss;
        ss << ifs.rdbuf();
        ss.str(decode(ss.str(), encodeType));
        std::string decrypted;
        CryptoPP::StringSource stringSource(
            ss.str(), true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(decrypted)));
        std::istringstream iss(decrypted);
        boost::archive::text_iarchive iar(iss);
        iar >> database;
      }
    }
  }
  if (encryptType == EncryptType::None)
  {
    std::ifstream ifs(filename);
    if (ifs.is_open())
    {
      std::stringstream ss;
      ss << ifs.rdbuf();
      ss.str(decode(ss.str(), encodeType));
      boost::archive::text_iarchive iar(ss);
      iar >> database;
    }
  }
}

void Storage::save(const Database &database, const std::string filename, EncodeType encodeType, EncryptType encryptType)
{
  if (encryptType == EncryptType::Salsa2)
  {
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SecByteBlock sbb(8);
    CryptoPP::Salsa20::Encryption encryption;

    memset(sbb, 0x10101110, sbb.size());
    CryptoPP::SHA256().CalculateDigest(
        digest, reinterpret_cast<const CryptoPP::byte *>(database.getPassword().c_str()), database.getPassword().length());
    encryption.SetKeyWithIV(digest, CryptoPP::SHA256::DIGESTSIZE, sbb, sbb.size());

    std::ostringstream oss;
    boost::archive::text_oarchive oar{ oss };
    oar << database;

    if (encodeType == EncodeType::None)
    {
      CryptoPP::StringSource stringSource(
          oss.str(), true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::FileSink(filename.c_str())));
    }
    if (encodeType == EncodeType::Base64 || encodeType == EncodeType::Url)
    {
      std::string encrypted;
      CryptoPP::StringSource stringSource(
          oss.str(), true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::StringSink(encrypted)));

      std::ofstream ofs;
      ofs.open(filename.c_str(), std::ios::out);
      if (ofs.is_open())
      {
        ofs << encode(encrypted, encodeType);
        ofs.close();
      }
    }
  }
  if (encryptType == EncryptType::None)
  {
    std::stringstream ss;
    std::ofstream ofs;
    ofs.open(filename.c_str(), std::ios::out);
    if (ofs.is_open())
    {
      boost::archive::text_oarchive oar{ ss };
      oar << database;
      ofs << encode(ss.str(), encodeType);
      ofs.close();
    }
    else
      throw "Error opening file";
  }
}

bool Storage::doesFileExists(std::string const path)
{
  std::ifstream file(path.c_str());
  return file.good();
}

std::string Storage::encode(const std::string &value, EncodeType encodeType)
{
  switch (encodeType)
  {
    case EncodeType::Url: return encodeUrl64(value);
    case EncodeType::Base64: return encode64(value);
    case EncodeType::None: return value;
    default: return encode64(value);
  }
}

std::string Storage::decode(const std::string &value, EncodeType encodeType)
{
  switch (encodeType)
  {
    case EncodeType::Url: return decodeUrl64(value);
    case EncodeType::Base64: return decode64(value);
    case EncodeType::None: return value;
    default: return decode64(value);
  }
}

std::string Storage::decode64(const std::string &value)
{
  std::string decoded;
  using namespace CryptoPP;
  StringSource ss(value, true, new Base64Decoder(new StringSink(decoded)));
  return decoded;
}

std::string Storage::encode64(const std::string &value)
{
  std::string encoded;
  using namespace CryptoPP;
  StringSource ss(
      reinterpret_cast<const byte *>(value.c_str()), value.size(), true, new Base64Encoder(new StringSink(encoded)));
  return encoded;
}

std::string Storage::decodeUrl64(const std::string &value)
{
  std::string decoded;
  using namespace CryptoPP;
  StringSource ss(value, true, new Base64URLDecoder(new StringSink(decoded)));
  return decoded;
}

std::string Storage::encodeUrl64(const std::string &value)
{
  std::string encoded;
  using namespace CryptoPP;
  StringSource ss(
      reinterpret_cast<const byte *>(value.c_str()), value.size(), true, new Base64URLEncoder(new StringSink(encoded)));
  return encoded;
}