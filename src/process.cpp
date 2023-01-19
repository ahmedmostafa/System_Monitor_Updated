#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include <unistd.h>

using std::string;
using std::to_string;
using std::vector;


// constructor
Process::Process(int pid) { pPid=pid;}

// TODO: Return this process's ID
int Process::Pid() { return pPid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{

    auto pActiveTime = (LinuxParser::ActiveJiffies(pPid) / sysconf(_SC_CLK_TCK));
    pCpuUtilization = pActiveTime / UpTime();
    return pCpuUtilization;    
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pPid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pPid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pPid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pPid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& pRef) const 
{ 
    return this->pCpuUtilization > pRef.pCpuUtilization;
}