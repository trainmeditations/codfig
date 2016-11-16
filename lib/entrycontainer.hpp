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

#ifndef TRAINMEDITATIONS_ENTRYCONTAINER_HPP
#define TRAINMEDITATIONS_ENTRYCONTAINER_HPP

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;

namespace codfig {

    class ConfigEntry;

    class EntryContainer {
    public:
        EntryContainer();
        EntryContainer(const EntryContainer & other);
        EntryContainer & operator=(const EntryContainer & rhs);
        virtual ~EntryContainer();
        ConfigEntry * addEntry(const string &name);
        void removeEntry(const string &name);
        ConfigEntry & getEntry(const string &name);
        const ConfigEntry & getEntry(const string &name) const;
        const vector<string> getEntryNames() const;
        bool hasEntry(const string &name) const;
    private:
        void copyEntries(const EntryContainer & other);
        map<string, ConfigEntry *> subEntries;
    };

}

#endif // TRAINMEDITATIONS_ENTRYCONTAINER_H
