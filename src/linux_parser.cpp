#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  filestream.close();
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  stream.close();
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

#define TOTAL_MEMORY 0
#define FREE_MEMORY 1
// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  float memory[2]{0.0};
  string line;
  string strTmp;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) 
  {
    for(int i=0; i < 2; i++ )
    {
      std::getline(filestream, line);
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> strTmp >> memory[i];
    }
  filestream.close();
  //std::cout << memory[TOTAL_MEMORY] << "     " << memory[FREE_MEMORY] << "     " << std::endl;
  }
  return ((memory[TOTAL_MEMORY] - memory[FREE_MEMORY]) /memory[TOTAL_MEMORY]) ;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  long uptime{0};
  string line;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> uptime;
    }
  filestream.close();
  return uptime ;
  
}

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return (ActiveJiffies() - IdleJiffies()); 
}


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{ 

    std::string filename = kProcDirectory + to_string(pid) + kStatFilename;
  
    std::vector<std::string> vec;
    std::string val;
    std::string line;
    std::ifstream stream(filename);

  	if (stream.is_open()) 
    {
    	std::getline(stream, line);

    	std::istringstream linestream(line);
    	while (linestream >> val) 
          vec.push_back(val);
        stream.close();
  	}
 // TEST CODE    //std::cout << vec.at(9) << std::endl;
  	
  return stol(vec.at(13)) + stol(vec.at(14)) + stol(vec.at(15)) + stol(vec.at(16)) ;

}


long LinuxParser::ActiveJiffies()
{ 
  const vector<string> cpu = LinuxParser::CpuUtilization();
  const long luser = stol(cpu[LinuxParser::kUser_]);
  const long lnice = stol(cpu[LinuxParser::kNice_]);
  const long lsystem = stol(cpu[LinuxParser::kSystem_]);
  const long lidle = stol(cpu[LinuxParser::kIdle_]);
  const long liowait = stol(cpu[LinuxParser::kIOwait_]);
  const long lirq = stol(cpu[LinuxParser::kIRQ_]);
  const long lsoftirq = stol(cpu[LinuxParser::kSoftIRQ_]);
  const long lsteal = stol(cpu[LinuxParser::kSteal_]);

  return (luser + lnice + lsystem + lidle + liowait + lirq + lsoftirq + lsteal);
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{   
  const vector<string> cpu = LinuxParser::CpuUtilization();
  const long lidle = stol(cpu[LinuxParser::kIdle_]);
  const long liowait = stol(cpu[LinuxParser::kIOwait_]);

  return ( lidle + liowait );
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 

  std::vector<string> cpuUtil;
  std::string line, val;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) 
  {
    getline(stream, line);

    std::istringstream linestream(line);
   
     // Test code //std::cout << "TP2" << std::endl;
     // Test code //std::cout << line << std::endl;
    linestream >> val;  // to get rid of the cpu string at the start of the line

    for (int i = 0; i < CPUStates::kGuestNice_; i++) 
    {
      linestream >> val;
      cpuUtil.push_back(val);
    }
  }
  stream.close();
  return cpuUtil;
}


// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string value;
  string line;
  int nPrcs=0;
  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> value;
      if(!value.compare("processes"))
      {
        linestream >> value;
        nPrcs = stoi(value);
        break;
      }
    }
    stream.close();
  }
  return nPrcs; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string value;
  string line;
  int nRunnngPrcs=0;
  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> value;  
      if(!value.compare("procs_running"))
      {
        linestream >> value;
        nRunnngPrcs = stoi(value);
        break;
      }
    }
    stream.close();
  }
  return nRunnngPrcs; 


}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Command(int pid) {
  std::string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream) getline(filestream, line);
  filestream.close();
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// Read and return the memory used by a process
string LinuxParser::Ram(int pid) 
{ 
  string value;
  string line;
  long prcMem=0;
  
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> value;
      // TEST Code //std::cout << "TP5 " << value << std::endl;
      if(!value.compare("VmSize:"))
      {
        linestream >> value;
        prcMem = stol(value);
        // TEST Code //std::cout << prcMem << std::endl;
        break;
      }
    }
    stream.close();
  }
  return to_string(prcMem/1024); 
}


// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) 
{ 
  string value;
  string line;
  std::string prcUid;
  
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> value;
      // TEST Code //std::cout << "TP5 " << value << std::endl;
      if(!value.compare("Uid:"))
      {
        linestream >> prcUid;
      // TEST Code //std::cout << prcUid << std::endl;
        break;
      }
    }
    stream.close();
  }
  return prcUid; 
}


// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{ 
  
  std::string refUid = LinuxParser::Uid(pid);
  std::string line, uid, user, skip;
  // Test Code refUid = "13";
  std::ifstream stream(kPasswordPath);

  if (stream.is_open()) {
    while (getline(stream, line)) {
      //std::replace(line.begin(), line.end(), ' ', '_');
      //std::replace(line.begin(), line.end(), 'x', ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> skip >> uid  ;

        if (!uid.compare(refUid)) 
          break;
    }
  }
  stream.close();
  return user;
  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) 
{ 
   std::vector<string> vec;
   std::string line, value;
   std::ifstream stream(kProcDirectory + to_string(pid) +  kStatFilename);

  if (stream.is_open()) 
  {
    getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) 
      vec.push_back(value);
  }

  stream.close();

    auto pTicks = stol(vec.at(21));
    //std::cout << pTicks << std::endl;
    return UpTime() - (pTicks / sysconf(_SC_CLK_TCK));

}

