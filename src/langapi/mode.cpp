/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@cs.cmu.edu

\*******************************************************************/

#include "mode.h"

#include <list>
#include <memory>
#include <set>

#ifdef _WIN32
#include <cstring>
#endif

#include "language.h"

struct language_entryt
{
  language_factoryt factory;
  std::set<std::string> extensions;
  irep_idt mode;
};

typedef std::list<language_entryt> languagest;
languagest languages;

void register_language(language_factoryt factory)
{
  languages.push_back(language_entryt());
  std::unique_ptr<languaget> l(factory());
  languages.back().factory=factory;
  languages.back().extensions=l->extensions();
  languages.back().mode=l->id();
}

std::unique_ptr<languaget> get_language_from_mode(const irep_idt &mode)
{
  for(languagest::const_iterator it=languages.begin();
      it!=languages.end();
      it++)
    if(mode==it->mode)
      return it->factory();

  return nullptr;
}

std::unique_ptr<languaget> get_language_from_filename(
  const std::string &filename)
{
  std::size_t ext_pos=filename.rfind('.');

  if(ext_pos==std::string::npos)
    return nullptr;

  std::string extension=
    std::string(filename, ext_pos+1, std::string::npos);

  if(extension=="")
    return nullptr;

  for(languagest::const_iterator
      l_it=languages.begin();
      l_it!=languages.end();
      l_it++)
  {
    #ifdef _WIN32
    for(std::set<std::string>::const_iterator
        e_it=l_it->extensions.begin();
        e_it!=l_it->extensions.end();
        e_it++)
      if(_stricmp(extension.c_str(), e_it->c_str())==0)
        return l_it->factory();
    #else
    if(l_it->extensions.find(extension)!=l_it->extensions.end())
      return l_it->factory();
    #endif
  }

  return nullptr;
}

std::unique_ptr<languaget> get_default_language()
{
  assert(!languages.empty());
  return languages.front().factory();
}
