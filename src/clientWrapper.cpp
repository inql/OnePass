#include <onepass/clientWrapper.hpp>

using namespace onepass::client;

ClientWrapper::ClientWrapper(int argc, char *argv[])
{
  handleProgramOptions(argc, argv);
}

bool ClientWrapper::has(ParameterType optName)
{
  return variablesMap.count(typeToString(optName)) ? true : false;
}

void ClientWrapper::printHelp()
{
  description->print(std::cout);
}

void ClientWrapper::get(ParameterType name, std::string &value)
{
  value = get(name);
}

std::string ClientWrapper::get(ParameterType name)
{
  if (has(name))
    return variablesMap[typeToString(name)].as<std::string>();
  else
  {
    return "";
  }
}

bool ClientWrapper::verifyParams(const ParameterType parameter)
{
  switch (parameter)
  {
    case ParameterType::help: return has(ParameterType::help);
    case ParameterType::version: return has(ParameterType::version);
    case ParameterType::file:
    case ParameterType::password:
      if (!(has(ParameterType::file) && has(ParameterType::password)))
        return false;
    case ParameterType::list: return has(ParameterType::list);
    case ParameterType::init: return has(ParameterType::init) && has(ParameterType::password) && has(ParameterType::file);
    case ParameterType::add:
      return has(ParameterType::add) && has(ParameterType::password) && has(ParameterType::file) &&
             has(ParameterType::key) &&
             (has(ParameterType::username) || has(ParameterType::value) || has(ParameterType::tags) ||
              has(ParameterType::url));
    case ParameterType::search:
      return has(ParameterType::search) && has(ParameterType::password) && has(ParameterType::file) &&
             has(ParameterType::keyword);

    default: throw std::invalid_argument("invalid param combination see help");
  }
}

onepass::storage::EncryptType ClientWrapper::getEncryptType()
{
  if (has(ParameterType::encrypt))
  {
    std::string encryptStr = get(ParameterType::encrypt);
    if (encryptStr == "none")
      return onepass::storage::EncryptType::None;
    return onepass::storage::EncryptType::Salsa2;
  }
  return onepass::storage::EncryptType::Salsa2;
}

onepass::storage::EncodeType ClientWrapper::getEncodeType()
{
  if (has(ParameterType::encoding))
  {
    std::string encodingStr = get(ParameterType::encoding);
    if (encodingStr == "none")
      return onepass::storage::EncodeType::None;
    if (encodingStr == "url")
      return onepass::storage::EncodeType::Url;
    if (encodingStr == "base64")
      return onepass::storage::EncodeType::Base64;
    return onepass::storage::EncodeType::None;
  }
  return onepass::storage::EncodeType::None;
}

void ClientWrapper::handleProgramOptions(int argc, char *argv[])
{
  description = new po::options_description("All options provided for this program");
  description->add_options()
    (typeToString(ParameterType::help), "Print this message ")
    (typeToString(ParameterType::init), "Initialize a database")
    (typeToString(ParameterType::search), "search for entries")
    (typeToString(ParameterType::add), "Add or update an entry in the database")
    (typeToString(ParameterType::list),"shows the lists of passwords -keys- stored in the database")
    (typeToString(ParameterType::version),"shows OnePass version")
    (typeToString(ParameterType::encrypt), po::value<std::string>()->default_value(defEncrypt), "Encryption algorithm, posible values: none, salsa2")    
    (typeToString(ParameterType::encoding), po::value<std::string>()->default_value(defEncode), "Encoding, posible values: none, base64, url")    
    (typeToString(ParameterType::password), po::value<std::string>(), "Password for database")
    (typeToString(ParameterType::file), po::value<std::string>()->default_value(defDatabaseName), "File name and path for the database")
    (typeToString(ParameterType::key), po::value<std::string>(), "A unique name for an entry in the database")
    (typeToString(ParameterType::value), po::value<std::string>(), "A strong password")
    (typeToString(ParameterType::username), po::value<std::string>(), "The user name associated with the password, example: user@domain.com")
    (typeToString(ParameterType::tags), po::value<std::string>(), "comma separated tags, example: personal, email")
    (typeToString(ParameterType::url), po::value<std::string>(), "an url, example: https://www.domain.com")
    (typeToString(ParameterType::email), po::value<std::string>(), "set the email of the account")
    (typeToString(ParameterType::keyword), po::value<std::string>(), "a text to find inside database")    
    (typeToString(ParameterType::show), "show the actual password")
    (typeToString(ParameterType::history), "shows modification history");
  po::store(po::parse_command_line(argc, argv, *description), variablesMap);
  po::notify(variablesMap);
}