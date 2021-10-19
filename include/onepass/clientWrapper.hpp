#ifndef CLIENTWRAPPER_HPP_
#define CLIENTWRAPPER_HPP_

#include <boost/program_options.hpp>
#include <iostream>
#include <onepass/parameterType.hpp>
#include <onepass/storage.hpp>
#include <stdexcept>
#include <string>

using namespace boost;
namespace po = boost::program_options;

namespace onepass
{
  namespace client
  {
    class ClientWrapper
    {
     public:
      ClientWrapper(int, char *[]);
      bool has(ParameterType);
      void printHelp();
      void get(ParameterType, std::string &);
      std::string get(ParameterType);
      bool verifyParams(const ParameterType);
      onepass::storage::EncryptType getEncryptType();
      onepass::storage::EncodeType getEncodeType();

     private:
      const std::string defDatabaseName = ".db";
      const std::string defEncrypt = "salsa2";
      const std::string defEncode = "none";
      po::options_description *description;
      po::variables_map variablesMap;
      void handleProgramOptions(int, char *[]);
    };
  }  // namespace client
}  // namespace onepass

#endif  // CLIENTWRAPPER_HPP_