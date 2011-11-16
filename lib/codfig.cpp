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

#include <algorithm>

#include "codfig.h"
#include "codfigio.h"

using namespace codfig;

/*
 * main Config class
 */

Config::Config(const string &applicationName,
               const string &applicationVersion,
               const string &developer):
appID(applicationName, applicationVersion, developer), defaultProfile(new ConfigProfile("default")),
currentProfile(defaultProfile), _pathSeparator('.'){}

Config::Config(const Config & other):
appID(other.appID), defaultProfile(new ConfigProfile(*(other.defaultProfile))),
currentProfile(defaultProfile), _pathSeparator(other._pathSeparator){
    //Copy profiles and set the same currentProfile
    copyProfiles(other);
}

Config::Config(ConfigIO *source):appID(source->getAppID()), _source(source)
{
}

Config & Config::operator=(const Config &rhs) {
    if (this != &rhs) {
        appID = rhs.appID;

        delete defaultProfile;
        defaultProfile = new ConfigProfile(*(rhs.defaultProfile));
        currentProfile = defaultProfile;

        for (vector<ConfigProfile *>::iterator iter = profiles.begin(); iter != profiles.end(); ++iter) {
            delete *iter;
            *iter = NULL;
        }
        profiles.clear();
        copyProfiles(rhs);
    }
    return *this;
}

void Config::copyProfiles(const Config & other) {
    ConfigProfile * newProfile = NULL;
    for (vector<ConfigProfile *>::const_iterator other_iter = other.profiles.begin();
      other_iter != other.profiles.end(); ++other_iter) {
        newProfile = new ConfigProfile(*(*other_iter));
        profiles.push_back(newProfile);
        if (other.currentProfile == *other_iter) currentProfile = newProfile;
    }
}

Config::~Config(){
	currentProfile = NULL;
	delete defaultProfile;
	for (vector<ConfigProfile *>::iterator iter = profiles.begin(); iter != profiles.end(); ++iter) {
		delete *iter;
		*iter = NULL;
	}
}


int Config::addProfile(const string &name){
	profiles.push_back(new ConfigProfile(name));
	return profiles.size() - 1;
}

void Config::removeProfile(const int &index){
	ConfigProfile * profile = profiles[index];
	vector<ConfigProfile *>::iterator iter = std::find((profiles.begin()+index), profiles.end(), profile);
	profiles.erase(iter);
	delete profile;
}

void Config::selectProfile(const int &index){
	currentProfile = profiles[index];
}

void Config::selectDefaultProfile(){
	currentProfile = defaultProfile;
}

const vector<string> Config::getProfileList() const {
	vector<string> profileList = vector<string>();
	for (vector<ConfigProfile *>::const_iterator iter = profiles.begin(); iter != profiles.end(); ++iter) {
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
	const EntryContainer *currentEC = currentProfile;
	string::size_type separatorPos;
	while ((separatorPos = path.find(_pathSeparator)) != string::npos) {
		currentEC = &(currentEC->getEntry(path.substr(0, separatorPos)));
		path = path.substr(separatorPos+1);
	}
	return currentEC->getEntry(path);
    /*string::size_type seperatorPos = path.find_last_of(_pathSeparator);
    const ConfigEntry &entry = findEntry(path.substr(0, seperatorPos));
    return seperatorPos == string::npos?entry:entry.getEntry(path.substr(seperatorPos+1));*/
}

ConfigEntry & Config::findEntry(string path)
{
	EntryContainer *currentEC = currentProfile;
	string::size_type separatorPos;
	while ((separatorPos = path.find(_pathSeparator)) != string::npos) {
		currentEC = &(currentEC->getEntry(path.substr(0, separatorPos)));
		path = path.substr(separatorPos+1);
	}
	return currentEC->getEntry(path);
    /*string::size_type seperatorPos = path.find_last_of(_pathSeparator);
    ConfigEntry &section = findEntry(path.substr(0, seperatorPos));
    return seperatorPos == string::npos?section:section.getEntry(path.substr(seperatorPos+1));*/
}
