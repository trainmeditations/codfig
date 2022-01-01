/*
 * Copyright © 2009-2011, 2015-2016, 2018, 2021-2022 Shaun Bouckaert
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

#include "configentry.hpp"

using namespace codfig;

ConfigEntry::ConfigEntry(EntryContainer *parent, const string &name): _parent(parent)
{
    ConfigEntry * parentE = nullptr;
    if ((parentE = dynamic_cast<ConfigEntry *>(parent))) {
        _path = parentE->path() + '.' + name;
    } else {
        _path = name;
    }
}

ConfigEntry::ConfigEntry(const ConfigEntry & other, EntryContainer *parent):
EntryContainer(other), ConfigValue(other), _parent(parent)
{}

//copying explicitly prohibited
/*ConfigEntry & ConfigEntry::operator=(const ConfigEntry & rhs)
{
    if (this != &rhs) {
        EntryContainer::operator=(rhs);
                ConfigValue::operator=(rhs);
    }
    return *this;
}*/

ConfigEntry &codfig::operator<< (ConfigEntry &entry, const char *value){
    entry.value<string>() = value;
    return entry;
}

bool ConfigEntry::operator==(const char *other) {
        return this->value<string>() == other;
}

ConfigEntry::~ConfigEntry()
{}

