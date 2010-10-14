#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <Manager.h>

char const *serialize(m_userinfo const *);
m_userinfo const *unserialize(char const *);

#endif // ! __TOOLS_H__
