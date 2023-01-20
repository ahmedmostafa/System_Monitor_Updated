#include <string>
#include "format.h"
#include <sstream>
#include <iomanip>

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = (seconds % 3600) % 60;

    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ':'
       << std::setfill('0') << std::setw(2) << minutes << ':'
       << std::setfill('0') << std::setw(2) << secs;
    return ss.str();      
     
}