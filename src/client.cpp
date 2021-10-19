#include <onepass/client.hpp>

using namespace onepass::client;

onepass::core::FieldType Client::parameterToFieldType(ParameterType parameterType)
{
  std::string ptStr = typeToString(parameterType);
  return onepass::core::typeFromString(ptStr);
}

void Client::printElapsed(std::chrono::time_point<std::chrono::system_clock> start)
{
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

int Client::handle(ClientWrapper &cw)
{
  auto start = std::chrono::system_clock::now();

  if (cw.verifyParams(ParameterType::help))
  {
    cw.printHelp();
    return 0;
  }
  if (cw.verifyParams(ParameterType::init))
  {
    onepass::core::Database db{ cw.get(ParameterType::password) };
    onepass::storage::Storage::save(db, cw.get(ParameterType::file), cw.getEncodeType(), cw.getEncryptType());
    printElapsed(start);
    return 0;
  }
  if (cw.verifyParams(ParameterType::add))
  {
    onepass::core::Entry entry;

    if (cw.has(ParameterType::value))
    {
      std::string value = cw.get(ParameterType::value);
      entry.setValue(value);
    }
    for (auto parameter : valuesList)
    {
      std::string val = cw.get(parameter);
      if (!val.empty())
        entry.addField(parameterToFieldType(parameter), val);
    }

    onepass::core::Database db;
    onepass::storage::Storage::read(
        db, cw.get(ParameterType::password), cw.get(ParameterType::file), cw.getEncodeType(), cw.getEncryptType());
    db.updateEntry(cw.get(ParameterType::key), entry);
    onepass::storage::Storage::save(db, cw.get(ParameterType::file), cw.getEncodeType(), cw.getEncryptType());
    printElapsed(start);
    return 0;
  }
  if (cw.verifyParams(ParameterType::search))
  {
    onepass::core::Database db;
    onepass::storage::Storage::read(
        db, cw.get(ParameterType::password), cw.get(ParameterType::file), cw.getEncodeType(), cw.getEncryptType());
    db.search(cw.get(ParameterType::keyword), cw.has(ParameterType::show), cw.has(ParameterType::history));
    printElapsed(start);
    return 0;
  }
  if (cw.verifyParams(ParameterType::list))
  {
    onepass::core::Database db;
    onepass::storage::Storage::read(
        db, cw.get(ParameterType::password), cw.get(ParameterType::file), cw.getEncodeType(), cw.getEncryptType());
    std::cout << "Database contents:\n\tNumber of entries: " << db.count() << std::endl;
    db.list();
    printElapsed(start);
    return 0;
  }
  if (cw.verifyParams(ParameterType::version))
  {
    std::cout << "OnePass version: " << onepass::core::Database::VERSION_STR << std::endl;
    return 0;
  }
  cw.printHelp();
  return 1;
}