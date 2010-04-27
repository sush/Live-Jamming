#include <LoggerModule_syslog.h>

LoggerModule_syslog::LoggerModule_syslog() {}

LoggerModule_syslog::~LoggerModule_syslog() {}

void LoggerModule_syslog::AddLine(int level, std::string const & log) {
  syslog(level, "%s", log.c_str());
}
