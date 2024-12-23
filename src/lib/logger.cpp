
#include <systemc.h>
#include <fstream>
#include <iomanip> // For std::setw and std::setfill
#include <logger.hpp>


Logger::Logger(const std::string& file_name) {
  log_file.open(file_name, std::ios::out);
  if (!log_file) {
    std::cerr << "Failed to open log file!" << std::endl;
    exit(1);
  }
}

Logger::~Logger() {
  if (log_file.is_open()) {
    log_file.close();
  }
}

void Logger::log(const std::string& level, const std::string& message) {
  log_file << "[" << std::setw(10) << std::setfill(' ') << sc_time_stamp() << "] "
	   << "[" << level << "] " << message << std::endl;
}
