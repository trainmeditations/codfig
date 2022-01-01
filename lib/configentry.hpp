/*
 * Copyright © 2009-2011, 2015-2016, 2021-2022 Shaun Bouckaert
 *
 *  This file is part of Codfig.
 *
 *  Codfig is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Codfig is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Codfig.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TRAINMEDITATIONS_CONFIGENTRY_HPP
#define TRAINMEDITATIONS_CONFIGENTRY_HPP

#include "entrycontainer.hpp"
#include "configvalue.hpp"

#include <string>
using std::string;

namespace codfig {

    class ConfigEntry:public EntryContainer, public ConfigValue {
    public:
        ConfigEntry(EntryContainer *parent, const string &name);
        ConfigEntry(const ConfigEntry & other, EntryContainer *parent);
        inline const string &path() const {return _path;}
        template <class T>
            bool operator==(const T& other);
        bool operator==(const char *other);
        ~ConfigEntry();
    private:
        //explicit copy prohibition with delete
        ConfigEntry(const ConfigEntry & other) = delete;
        ConfigEntry & operator=(const ConfigEntry & rhs) = delete;
        string _path;
        EntryContainer *_parent;
        friend ConfigEntry &operator<< (ConfigEntry &entry, const char value[]);
        template <class T>
            friend ConfigEntry &operator<< (ConfigEntry &entry, const T &value);
        template <class T>
            friend const ConfigEntry &operator>> (const ConfigEntry &entry, T &value);
    };

    ConfigEntry &operator<< (ConfigEntry &entry, const char *value);
    
    template <class T>
        ConfigEntry &operator<< (ConfigEntry &entry, const T &value);

    //Array input?
    //template < std::size_t N >
    //    void operator<<(ConfigEntry &entry, const char(&value)[N]);
    
    template <class T>
        const ConfigEntry &operator>> (const ConfigEntry &entry, T &value);
}

/************************
* Template Definitions *
************************/

#include "configentry_t.hpp"

#endif // TRAINMEDITATIONS_CONFIGENTRY_H
