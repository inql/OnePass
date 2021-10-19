#ifndef PROPERTYTYPE_HPP
#define PROPERTYTYPE_HPP

#include <boost/preprocessor.hpp>
#include <string>

#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem) \
  case elem:                                                               \
    return BOOST_PP_STRINGIZE(elem);

#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_FROMSTRING_CASE(r, data, elem) \
  if (str == BOOST_PP_STRINGIZE(elem))                                       \
    return elem;

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)                                                    \
  enum name                                                                                                       \
  {                                                                                                               \
    other,                                                                                                        \
    BOOST_PP_SEQ_ENUM(enumerators)                                                                                \
  };                                                                                                              \
                                                                                                                  \
  inline const char* typeToString(name v)                                                                         \
  {                                                                                                               \
    switch (v)                                                                                                    \
    {                                                                                                             \
      BOOST_PP_SEQ_FOR_EACH(X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE, name, enumerators)               \
      default: return "other";                                                                                    \
    }                                                                                                             \
  }                                                                                                               \
                                                                                                                  \
  inline name typeFromString(std::string& str)                                                                    \
  {                                                                                                               \
    BOOST_PP_SEQ_FOR_EACH(X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_FROMSTRING_CASE, name, enumerators) return other; \
  }

namespace onepass
{
  namespace core
  {
    DEFINE_ENUM_WITH_STRING_CONVERSIONS(FieldType, (username)(email)(url)(pin)(code)(tags))
  }  // namespace core
}  // namespace onepass

#endif  // PROPERTYTYPE_HPP