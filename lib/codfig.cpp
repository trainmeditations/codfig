/*
 * Copyright © 2009-2012, 2015-2016, 2018 Shaun Bouckaert
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

#include <algorithm>

#include "codfig.hpp"

using namespace codfig;

static const char defaultPathSep = '.';

/*
 * main Config class
 */

Config::Config(const string &applicationName,
               const string &applicationVersion,
               const string &developer):
appID(applicationName, applicationVersion, developer), defaultProfile(new ConfigProfile("default")),
currentProfile(defaultProfile), _pathSeparator(defaultPathSep){}

Config::Config(const Config & other):
appID(other.appID), defaultProfile(new ConfigProfile(*(other.defaultProfile))),
currentProfile(defaultProfile), _pathSeparator(other._pathSeparator){
    //Copy profiles and set the same currentProfile
    copyProfiles(other);
}

/*Config::Config(ConfigIO *source):appID(source->applicationID()), defaultProfile(new ConfigProfile("default")),
    currentProfile(defaultProfile), _pathSeparator(defaultPathSep), _source(source)
{
    //source->readConfig(*this);
    //TODO: Remove body
}*/

Config & Config::operator=(const Config &rhs) {
    if (this != &rhs) {
        appID = rhs.appID;

        defaultProfile = std::make_shared<ConfigProfile>(*(rhs.defaultProfile));
        currentProfile = defaultProfile;

        profiles.clear();
        copyProfiles(rhs);
    }
    return *this;
}

void Config::copyProfiles(const Config & other) {
    shared_ptr<ConfigProfile> newProfile;
    for (auto other_iter = other.profiles.begin();
      other_iter != other.profiles.end(); ++other_iter) {
        newProfile = std::make_shared<ConfigProfile>(**other_iter);
        profiles.push_back(newProfile);
        if (other.currentProfile == *other_iter) currentProfile = newProfile;
    }
}

Config::~Config(){}

/*void Config::clearSource() {
    _source = NULL;
}*/


size_t Config::addProfile(const string &name){
    profiles.push_back(std::make_shared<ConfigProfile>(name));
	return profiles.size() - 1;
}

void Config::removeProfile(const size_t index){
    profiles.erase(profiles.begin()+index);
}

void Config::selectProfile(const size_t &index){
	currentProfile = profiles[index];
}

void Config::selectDefaultProfile(){
	currentProfile = defaultProfile;
}

const vector<string> Config::getProfileList() const {
	vector<string> profileList = vector<string>();
    for (auto iter = profiles.begin(); iter != profiles.end(); ++iter) {
		profileList.push_back((*iter)->getName());
	}
	return profileList;
}

const ConfigEntry & Config::operator[](const string &path) const {
	return findEntry(path);
}

ConfigEntry & Config::operator[](const string &path) {
	return findEntry(path);
}

void Config::removeEntry(const string &name) {
	currentProfile->removeEntry(name);
}

const vector<string> Config::getEntryNames() const {
	return currentProfile->getEntryNames();
}

const ConfigEntry & Config::findEntry(string path) const
{
    shared_ptr<const EntryContainer> currentEC = currentProfile;
	string::size_type separatorPos;
	while ((separatorPos = path.find(_pathSeparator)) != string::npos) {
        currentEC = currentEC->getEntry(path.substr(0, separatorPos));
		path = path.substr(separatorPos+1);
	}
    return *(currentEC->getEntry(path));
}

ConfigEntry & Config::findEntry(string path)
{
    shared_ptr<EntryContainer> currentEC = currentProfile;
	string::size_type separatorPos;
	while ((separatorPos = path.find(_pathSeparator)) != string::npos) {
        currentEC = currentEC->getEntry(path.substr(0, separatorPos));
		path = path.substr(separatorPos+1);
	}
    return *(currentEC->getEntry(path));
}
