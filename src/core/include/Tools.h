#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <iostream>
#include <map>
#include <vector>
#include <cstring>

char const *serialize(std::map<std::string, std::string> *);
//char const *serialize(std::map<unsigned int, Channel*> *);
std::map<std::string, std::string> *unserialize(char const *);



#endif // ! __TOOLS_H__
