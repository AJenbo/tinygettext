//  $Id$
//
//  TinyGetText
//  Copyright (C) 2006 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_DICTIONARY_MANAGER_HPP
#define HEADER_DICTIONARY_MANAGER_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

#include "directory.hpp"
#include "dictionary.hpp"

namespace tinygettext {

/** Manager class for dictionaries, you give it a bunch of directories
    with .po files and it will then automatically load the right file
    on demand depending on which language was set. */
class DictionaryManager
{
private:
  typedef std::map<std::string, Dictionary> Dictionaries;
  Dictionaries dictionaries;
  typedef std::vector<std::string> SearchPath;
  SearchPath search_path;
  typedef std::map<std::string, std::string> Aliases;
  Aliases language_aliases;
  std::string charset;
  std::string language;
  Dictionary* current_dict;
  Dictionary empty_dict;

  DirOp dir_op;

public:
  DictionaryManager();

  /** Return the currently active dictionary, if none is set, an empty
      dictionary is returned. */
  Dictionary& get_dictionary()
  { return *current_dict; }

  /** Get dictionary for lang */
  Dictionary& get_dictionary(const std::string& langspec);

  /** Set a language based on a four? letter country code */
  void set_language(const std::string& langspec);

  /** returns the (normalized) country code of the currently used language */
  const std::string& get_language() const;

  /** Set a charset that will be set on the returned dictionaries */
  void set_charset(const std::string& charset);

  /** Define an alias for a language */
  void set_language_alias(const std::string& alias, const std::string& lang);

  /** Add a directory to the search path for dictionaries */
  void add_directory(const std::string& pathname);

  /** Return a set of the available languages in their country code */
  std::set<std::string> get_languages();

  void set_dir_op(const DirOp& dir_op);

private:
  void parseLocaleAliases();
  /// returns the language part in a language spec (like de_DE.UTF-8 -> de)
  std::string get_language_from_spec(const std::string& spec);
};

} // namespace tinygettext

#endif

/* EOF */
