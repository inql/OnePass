#ifndef NO_PROPERTY_SET_EXCEPTION_HPP
#define NO_PROPERTY_SET_EXCEPTION_HPP
#include <exception>

namespace onepass
{
  namespace core
  {
    struct no_property_set_exception : public std::exception
    {
      const char* what() const throw()
      {
        return "No property set";
      }
    };
  }  // namespace core
}  // namespace onepass
#endif  // NO_PROPERTY_SET_EXCEPTION_HPP