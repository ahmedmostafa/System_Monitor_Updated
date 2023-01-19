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
    int hours{0}, mins{0}, rem_sec {0};

    hours = seconds / 3600;
    rem_sec = seconds % 3600;
    mins = rem_sec / 60;
    rem_sec %= 60;

    std::ostringstream myStream;
    myStream << std::setw('2') << std::setfill('0') << hours << ":" 
             << std::setw('2') << std::setfill('0') << mins << ":"
             << std::setw('2') << std::setfill('0') << rem_sec;
    
     return myStream.str(); 
        
     
}