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

#include "entrycontainer.hpp"
#include "configentry.hpp"
#include "codfigexceptions.hpp"

using namespace codfig;

EntryContainer::EntryContainer()
{}

EntryContainer::EntryContainer(const EntryContainer & other)
{
    copyEntries(other);
}

EntryContainer & EntryContainer::operator=(const EntryContainer & rhs)
{
    if (this != &rhs) {
        subEntries.clear();
        copyEntries(rhs);
    }
    return *this;
}

void EntryContainer::copyEntries(const EntryContainer & other)
{
    for (auto other_iter = other.subEntries.begin(); other_iter != other.subEntries.end(); other_iter++) {
        subEntries[other_iter->first] = std::make_shared<ConfigEntry>(*(other_iter->second), this);
    }
}

EntryContainer::~EntryContainer()
{}

shared_ptr<ConfigEntry> EntryContainer::addEntry(const string &name)
{
    if (!subEntries.count(name)) {
        shared_ptr<ConfigEntry> newCE = std::make_shared<ConfigEntry>(this, name);
        subEntries[name] = newCE;
        return newCE;
    } else {
        //this should never happen as entries are only added if they don't already exist
        throw duplicate_name("entry", name);
    }
}

void EntryContainer::removeEntry(const string &name)
{
    if (subEntries.count(name)) {
        subEntries.erase(name);
    } //should I throw an exception on else? strict mode?
}

shared_ptr<ConfigEntry> EntryContainer::getEntry(const string &name)
{
    if (subEntries.count(name)) {
        return subEntries[name];
    } else {
        return addEntry(name);
    }
}

const shared_ptr<ConfigEntry> EntryContainer::getEntry(const string &name) const
{
    if (subEntries.count(name)) {
        return (*subEntries.find(name)).second;
    } else {
        throw bad_path(name);
    }
}

bool EntryContainer::hasEntry(const string &name) const
{
    return subEntries.count(name)?true:false;
}

const vector<string> EntryContainer::getEntryNames() const
{
    vector<string> names;
    for (auto iter = subEntries.begin(); iter != subEntries.end(); ++iter) {
        names.push_back(iter->first);
    }
    return names;
}
