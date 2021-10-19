#ifndef PARAMETERTYPE_HPP
#define PARAMETERTYPE_HPP

#include <boost/preprocessor.hpp>
#include <string>

#define PT_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem) \
  case elem:                                                               \
    return BOOST_PP_STRINGIZE(elem);

#define PT_DEFINE_ENUM_WITH_STRING_CONVERSIONS_FROMSTRING_CASE(r, data, elem) \
  if (str == BOOST_PP_STRINGIZE(elem))                                       \
    return elem;

#define PT_DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)                                                      \
  enum name                                                                                                         \
  {                                                                                                                 \
    invalid,                                                                                                        \
    BOOST_PP_SEQ_ENUM(enumerators)                                                                                  \
  };                                                                                                                \
                                                                                                                    \
  inline const char* typeToString(name v)                                                                           \
  {                                                                                                                 \
    switch (v)                                                                                                      \
    {                                                                                                               \
      BOOST_PP_SEQ_FOR_EACH(PT_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE, name, enumerators)                 \
      default: return "";                                                                                           \
    }                                                                                                               \
  }                                                                                                                 \
                                                                                                                    \
  inline name typeFromString(std::string& str)                                                                      \
  {                                                                                                                 \
    BOOST_PP_SEQ_FOR_EACH(PT_DEFINE_ENUM_WITH_STRING_CONVERSIONS_FROMSTRING_CASE, name, enumerators) return invalid; \
  }

namespace onepass
{
  namespace client
  {
    PT_DEFINE_ENUM_WITH_STRING_CONVERSIONS(
        ParameterType,
        (help)(init)(add)(search)(password)(file)(key)(value)(username)(tags)(url)(keyword)(email)(show)(history)(list)(version)(encrypt)(encoding))
  }  // namespace client
}  // namespace onepass

#endif  // PARAMETERTYPE_HPP