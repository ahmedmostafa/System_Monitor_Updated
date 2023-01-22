#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include <unistd.h>
#include <thread>

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

 auto pActiveTime = ((float)LinuxParser::ActiveJiffies(pPid) / sysconf(_SC_CLK_TCK));
    pCpuUtilization = 100*pActiveTime / UpTime();
    return pCpuUtilization;   


  /*  int numCpus=std::thread::hardware_concurrency();
    std::string line,uptime, idletime; 
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename); 
    if (stream.is_open()) { std::getline(stream, line); 
    std::istringstream linestream(line); linestream >> uptime >> idletime; 
    }
    float usageRatio=(numCpus*std::stol(uptime) - std::stol(idletime)); 
    return usageRatio/(numCpus*std::stol(uptime));*/
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