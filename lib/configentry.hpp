/*
 * Copyright © 2009-2011, 2015-2016 Shaun Bouckaert
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

namespace codfig {

    class ConfigEntry:public EntryContainer, public ConfigValue {
    public:
        ConfigEntry(EntryContainer *parent, const string &name);
        ConfigEntry(const ConfigEntry & other, EntryContainer *parent);
        inline const string &path() const {return _path;}
        ~ConfigEntry();
    private:
        ConfigEntry(const ConfigEntry & other);
        ConfigEntry & operator=(const ConfigEntry & rhs);
        string _path;
        EntryContainer *_parent;
    };

}

#endif // TRAINMEDITATIONS_CONFIGENTRY_H
