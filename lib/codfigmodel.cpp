/*
 * Copyright © Shaun Bouckaert 2009
 *
 * This file is part of Codfig.
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

#include "codfigmodel.h"

using namespace codfig;

ApplicationID::ApplicationID(const string &applicationName, const string &applicationVersion, const string &developer):
        _appName(applicationName), _appVer(applicationVersion), _developer(developer)
{}

ConfigValue::AbstractValueBox::~AbstractValueBox()
{}

ConfigValue::ConfigValue():_value(NULL)
{}

ConfigValue::ConfigValue(const ConfigValue & other):_value(NULL)
{
    if (other._value) _value = other._value->cloneValue();
}

ConfigValue & ConfigValue::operator=(const ConfigValue & other)
{
    if (this != &other) {
        delete _value;
        if (other._value) {
            _value = other._value->cloneValue();
        } else {
            _value = NULL;
        }
    }
    return *this;
}

string ConfigValue::stringValue() const
{
    return _value->getStringValue();
}

ConfigValue::~ConfigValue()
{
    if (_value) delete _value;
}

EntryContainer::EntryContainer()
{}

EntryContainer::EntryContainer(const EntryContainer & other)
{
    copyEntries(other);
}

EntryContainer & EntryContainer::operator=(const EntryContainer & rhs)
{
    if (this != &rhs) {
        for (map<string, ConfigEntry *>::iterator iter = subEntries.begin(); iter != subEntries.end(); iter++) {
            delete iter->second;
        }
        subEntries.clear();
        copyEntries(rhs);
    }
    return *this;
}

void EntryContainer::copyEntries(const EntryContainer & other)
{
    for (map<string, ConfigEntry *>::const_iterator other_iter = other.subEntries.begin(); other_iter != other.subEntries.end(); other_iter++) {
        subEntries[other_iter->first] = new ConfigEntry(*(other_iter->second), this);
    }
}

EntryContainer::~EntryContainer()
{
    for (map<string, ConfigEntry *>::iterator iter = subEntries.begin(); iter != subEntries.end(); ++iter) {
        delete iter->second;
        iter->second = NULL;
    }
}

ConfigEntry * EntryContainer::addEntry(const string &name)
{
    /*
     * TODO: check if value exists and replace it with a section
     *
     */
    if (!subEntries.count(name)) {
        //subSections.insert(map<string, ConfigSection *>::value_type(name, new ConfigSection()));
        ConfigEntry * newCE = new ConfigEntry(this, name);
        subEntries[name] = newCE;
        return newCE;
    } else {
        throw duplicate_name("section", name);
    }
}

void EntryContainer::removeEntry(const string &name)
{
    if (subEntries.count(name)) {
        delete subEntries[name];
        subEntries.erase(name);
    } //should I throw an exception on else? strict mode?
}

ConfigEntry & EntryContainer::getEntry(const std::string &name)
{
    if (subEntries.count(name)) {
        return *subEntries[name];
    } else {
        return *(addEntry(name));
    }
}

const ConfigEntry & EntryContainer::getEntry(const string &name) const
{
    if (subEntries.count(name)) {
        return *(*subEntries.find(name)).second;
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
    for (map<string, ConfigEntry *>::const_iterator iter = subEntries.begin(); iter != subEntries.end(); ++iter) {
        names.push_back(iter->first);
    }
    return names;
}

ConfigEntry::ConfigEntry(EntryContainer *parent, const string &name): _parent(parent)
{
    ConfigEntry * parentE = NULL;
    if (parentE = dynamic_cast<ConfigEntry *>(parent)) {
        _path = parentE->path() + '.' + name;
    } else {
        _path = name;
    }
}

/*ConfigSection::ConfigSection(const ConfigValue &value):
        ConfigEntry(value)
{}*/

ConfigEntry::ConfigEntry(const ConfigEntry & other, EntryContainer *parent):
EntryContainer(other), ConfigValue(other), _parent(parent)
{}

/*ConfigEntry & ConfigEntry::operator=(const ConfigEntry & rhs)
{
    if (this != &rhs) {
        EntryContainer::operator=(rhs);
		ConfigValue::operator=(rhs);
    }
    return *this;
}*/

ConfigEntry::~ConfigEntry()
{}

int ConfigValue::intValue()
{
    return value<int>();
}

ConfigProfile::ConfigProfile(const string & profileName):name(profileName)
{}

const string & ConfigProfile::getName() const
{
    return name;
}

void ConfigProfile::setName(const string &newName)
{
    name = newName;
}