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

ConfigEntry::AbstractValueBox::~AbstractValueBox()
{}

ConfigEntry::ConfigEntry():_value(NULL),changed(false)
{}

ConfigEntry::ConfigEntry(const ConfigEntry & other):_value(NULL), changed(other.changed)
{
	if (other._value) _value = other._value->cloneValue();
}

ConfigEntry & ConfigEntry::operator=(const ConfigEntry & other)
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

string ConfigEntry::stringValue() const
{
	return _value->getStringValue();
}

bool ConfigEntry::hasChanged() const
{
	return changed;
}

void ConfigEntry::setChanged(bool isChanged)
{
	changed = isChanged;
}

ConfigEntry::~ConfigEntry()
{
	if (_value) delete _value;
}

SectionContainer::SectionContainer()
{}

SectionContainer::SectionContainer(const SectionContainer & other)
{
    copySections(other);
}

SectionContainer & SectionContainer::operator=(const SectionContainer & rhs)
{
    if (this != &rhs) {
        for (map<string, ConfigSection *>::iterator iter = subSections.begin();
          iter != subSections.end(); iter++){
            delete iter->second;
        }
        subSections.clear();
        copySections(rhs);
    }
    return *this;
}

void SectionContainer::copySections(const SectionContainer & other)
{
    for (map<string, ConfigSection *>::const_iterator other_iter = other.subSections.begin();
      other_iter != other.subSections.end(); other_iter++){
        subSections[other_iter->first] = new ConfigSection(*(other_iter->second));
    }
}

SectionContainer::~SectionContainer()
{
	for (map<string, ConfigSection *>::iterator iter = subSections.begin(); iter != subSections.end(); ++iter) {
		delete iter->second;
		iter->second = NULL;
	}
}

ConfigSection * SectionContainer::addSection(const string &name)
{
    /*
     * TODO: check if value exists and replace it with a section
     *
     */
	if (!subSections.count(name)) {
		//subSections.insert(map<string, ConfigSection *>::value_type(name, new ConfigSection()));
        ConfigSection * newCS = new ConfigSection();
		subSections[name] = newCS;
        return newCS;
	} else {
		throw duplicate_name("section", name);
	}
}

void SectionContainer::removeSection(const string &name)
{
	if (subSections.count(name)) {
	    delete subSections[name];
		subSections.erase(name);
	} //should I throw an exception on else? strict mode?
}

ConfigSection & SectionContainer::getSection(const std::string &name)
{
	if (subSections.count(name)) {
		return *subSections[name];
	} else {
		return *(addSection(name));
	}
}

const ConfigSection & SectionContainer::getSection(const string &name) const
{
	if (subSections.count(name)) {
		return *(*subSections.find(name)).second;
	} else {
		throw bad_path(name);
	}
}

bool SectionContainer::hasSection(const string &name) const
{
    return subSections.count(name)?true:false;
}

const vector<string> SectionContainer::getSectionNames() const
{
	vector<string> names;
	for (map<string, ConfigSection *>::const_iterator iter = subSections.begin();
		 iter != subSections.end(); ++iter) {
			 names.push_back(iter->first);
	}
	return names;
}

ConfigSection::ConfigSection()
{}

ConfigSection::ConfigSection(const ConfigSection & other):SectionContainer(other)
{
    copyValues(other);
}

ConfigSection & ConfigSection::operator=(const ConfigSection & rhs)
{
    if (this != &rhs) {
        for (map<string, ConfigValue *>::iterator iter = values.begin(); iter != values.end(); ++iter){
            delete iter->second;
        }
        values.clear();
        copyValues(rhs);
        SectionContainer::operator=(rhs);
    }
    return *this;
}

void ConfigSection::copyValues(const ConfigSection & other)
{
    for (map<string, ConfigValue *>::const_iterator other_iter = other.values.begin();
      other_iter != other.values.end(); ++other_iter){
        values[other_iter->first] = new ConfigValue(*(other_iter->second));
    }
}

ConfigSection::~ConfigSection()
{
	for (map<string, ConfigValue *>::iterator iter = values.begin(); iter != values.end(); ++iter) {
		delete iter->second;
		iter->second = NULL;
	}
}

const vector<string> ConfigSection::getValueNames() const
{
	vector<string> names;
	for (map<string, ConfigValue *>::const_iterator iter = values.begin();
		 iter != values.end(); ++iter) {
			 names.push_back(iter->first);
	}
	return names;
}

ConfigValue & ConfigSection::value(const string &name)
{
	if (values.count(name)) {
		return *values[name];
	} else {
		ConfigValue * newValue = new ConfigValue();
		values.insert(map<string, ConfigValue *>::value_type(name, newValue));
		return *newValue;
	}
}

const ConfigValue & ConfigSection::value(const string &name) const
{
	if (values.count(name)) {
		return *(*values.find(name)).second;
	} else {
		//ConfigValue * newValue = new ConfigValue();
		//values.insert(map<string, ConfigValue *>::value_type(name, newValue));
		//return *newValue;
		//TODO: THROW ERROR
		throw value_not_set("name");
	}
}

bool ConfigSection::hasValue(const string &name) const
{
    return values.count(name)?true:false;
}

ConfigEntry & ConfigSection::entry(const string &name)
{
    if (hasSection(name)) {
        return getSection(name);
    } else {
        return value(name);
    }
}

const ConfigEntry & ConfigSection::entry(const string &name) const
{
    if (hasSection(name)) {
        return getSection(name);
    } else {
        return value(name);
    }
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
