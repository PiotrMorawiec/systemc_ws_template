
#ifndef _LOGGER_H_
#define _LOGGER_H_

class Logger {
private:
  std::ofstream log_file;

public:
  Logger(const std::string& file_name);
  ~Logger();
  void log(const std::string& level, const std::string& message);
};

#endif
