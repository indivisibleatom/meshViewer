#include "precomp.h"
#include "helpers.h"
#include <cstdlib>

template<> float strtoT<float>( const char* str, char **endPtr )
{
  return (float)strtod( str, endPtr );
}

template<> double strtoT<double>( const char* str, char **endPtr )
{
  return strtod( str, endPtr );
}

template<> int strtoT<int>( const char* str, char **endPtr )
{
  return (int)strtol( str, endPtr, 10 );
}

template<> long strtoT<long>( const char* str, char **endPtr )
{
  return strtol( str, endPtr, 10 );
}

