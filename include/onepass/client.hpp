#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <chrono>
#include <ctime>
#include <onepass/clientWrapper.hpp>
#include <vector>
namespace onepass
{
  namespace client
  {
    class Client
    {
     public:
      static const inline std::vector<ParameterType> valuesList = { ParameterType::username,
                                                                    ParameterType::tags,
                                                                    ParameterType::url,
                                                                    ParameterType::email };
      static void printElapsed(std::chrono::time_point<std::chrono::system_clock>);
      static int handle(ClientWrapper &);
    private:
    static onepass::core::FieldType parameterToFieldType(ParameterType);
    };
  }  // namespace client
}  // namespace onepass

#endif  // CLIENT_HPP_