#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <Manager.h>

#ifdef __linux__
 #include <unistd.h>
#elif defined(_WIN32)
 #include <windows.h>
#endif

char const		*serialize(m_userinfo const *);
m_userinfo const	*unserialize(char const *);
int			compute_Ncores();

#endif // ! __TOOLS_H__
