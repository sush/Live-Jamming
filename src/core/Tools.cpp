#include "Tools.h"

char const *serialize(std::map<std::string, std::string> *m_profil)
{
  std::string	profilList;
  char const	*tmp;

  std::map<std::string, std::string>::iterator it, end = m_profil->end();
  for (it = m_profil->begin(); it != end; ++it)
    {
      tmp = it->first.c_str();
      for (unsigned int i = 0; i < it->first.length(); ++i)
      	{
      	  if (tmp[i] == '\\' || tmp[i] == '#')
      	    profilList += "\\";
      	  profilList += tmp[i];
      	}
      profilList += '#';
      tmp = it->second.c_str();
      for (unsigned int i = 0; i < it->second.length(); ++i)
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

std::map<std::string, std::string> *unserialize(char const *userInfos)
{
  std::string	infos = userInfos;
  std::string	tmp;
  bool		escape = false;
  std::vector<std::string>		*v_tmp = new std::vector<std::string>();

  std::map<std::string, std::string>	*m_userInfos = new std::map<std::string, std::string>();

  for (unsigned int i = 0; i < infos.length(); ++i)
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

  for (int j = 0; j < v_tmp->size(); ++j)
    {
      if (j == v_tmp->size())
	break;
      m_userInfos->insert(std::pair<std::string, std::string>(v_tmp->at(j), v_tmp->at(j+1)));
      j++;
    }
  return m_userInfos;
}
