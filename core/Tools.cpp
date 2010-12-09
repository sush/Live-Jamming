#include <Tools.h>

char const *serialize(m_userinfo const *m_profil)
{
  std::string	profilList;
  char const	*tmp;

  m_userinfo::const_iterator it, end = m_profil->end();
  for (it = m_profil->begin(); it != end; ++it)
    {
      tmp = it->first.c_str();
      for (std::size_t i = 0; i < it->first.length(); ++i)
      	{
      	  if (tmp[i] == '\\' || tmp[i] == '#')
      	    profilList += "\\";
      	  profilList += tmp[i];
      	}
      profilList += '#';
      tmp = it->second.c_str();
      for (std::size_t i = 0; i < it->second.length(); ++i)
      	{
      	  if (tmp[i] == '\\' || tmp[i] == '#')
      	    profilList += "\\";
      	  profilList += tmp[i];
      	}
      if (it->second.length() == 0)
	profilList += '#';
      profilList += '#';
    }
  return profilList.c_str();
}

m_userinfo const *unserialize(char const *userInfos)
{
  std::string	infos = userInfos;
  std::string	tmp;
  std::vector<std::string>		*v_tmp = new std::vector<std::string>();

  m_userinfo	*m_userInfos = new m_userinfo;

  for (std::size_t i = 0; i < infos.length(); ++i)
    {
      if (infos[i] == '\0')
      	break;
      if (infos[i] == '\\')
	{
	  tmp += infos[i+1];
	  ++i;
	}
      else if (infos[i] == '#' && infos[i-1] != '\\')
	{
	  v_tmp->push_back(tmp);
	  tmp.clear();
	}
      else
	tmp += infos[i];
    }

  for (std::size_t j = 0; j < v_tmp->size(); ++j)
    {
      if (j == v_tmp->size())
	break;
      m_userInfos->insert(std::pair<std::string, std::string>(v_tmp->at(j), v_tmp->at(j+1)));
      j++;
    }
  return m_userInfos;
}

// platform dependent                                                                                                                                                 
// implement for other platform mac osx, *bsd, ...                                                                                     
int             compute_Ncores()
{
#ifdef __linux__
  return sysconf( _SC_NPROCESSORS_ONLN );
#elif defined(_WIN32)
  SYSTEM_INFO sysinfo;

  GetSystemInfo( &sysinfo );
  return sysinfo.dwNumberOfProcessors;
#else
        #error "count_cores uninplemented for this sytem => implement"
#endif
}
