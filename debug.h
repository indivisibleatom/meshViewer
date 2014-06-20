#include <iostream>
#include <boost/timer/timer.hpp>

enum class DEBUG_LEVELS
{
  VERBOSE,
  LOW,
  ERROR
};

const DEBUG_LEVELS DEBUG_LEVEL = DEBUG_LEVELS::VERBOSE;

#define LOG( string, debugLevel ) \
{ \
  if ( debugLevel >= DEBUG_LEVEL ) \
  { \
    std::cout<<__FILE__<<" "<<__LINE__<<" "<<__FUNCTION__<<" "<<string<<"\n"; \
  } \
}

#define LOGPERF boost::timer::auto_cpu_timer t
