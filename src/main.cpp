#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include "iostream"

int main() {
  
  System system;
  NCursesDisplay::Display(system);
 
  /* TEST code
  std::cout << LinuxParser::MemoryUtilization() << std::endl;
  std::cout << LinuxParser::UpTime() << std::endl;
  std::cout << LinuxParser::ActiveJiffies(1030) << std::endl;
  std::cout << (LinuxParser::CpuUtilization()).at(0) << std::endl;
  std::cout << LinuxParser::IdleJiffies() << std::endl;
  std::cout << LinuxParser::IdleJiffies() << std::endl; 
  std::cout << LinuxParser::ActiveJiffies() << std::endl;
  std::cout << LinuxParser::TotalProcesses() << std::endl;
  std::cout << LinuxParser::RunningProcesses() << std::endl;
  std::cout << LinuxParser::Command(1030) << std::endl;
  std::cout << "TP3 " << std::endl;
  std::cout << LinuxParser::Ram(1030) << std::endl;
  std::cout << LinuxParser::Uid(1030) << std::endl;
  std::cout << LinuxParser::User(1030) << std::endl;
  std::cout << LinuxParser::UpTime(1030) << std::endl;
  std::cout << "TP4 " << std::endl;
  end of Test code */
}