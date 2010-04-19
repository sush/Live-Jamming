#include <Syslog.h>

Syslog::Syslog() {}

Syslog::~Syslog() {}

void Syslog::AddLine(int level, std::string const & log) {
  syslog(level, "%s", log.c_str());
}
