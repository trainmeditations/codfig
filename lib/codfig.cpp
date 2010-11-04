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

static const char DefaultPathSep = '.';

using namespace codfig;

/*
 * main Config class
 */

Config::Config(const string &applicationName,
               const string &applicationVersion,
               const string &developer):
appID(applicationName, applicationVersion, developer), defaultProfile(new ConfigProfile("default")),
currentProfile(defaultProfile), _pathSeperator(DefaultPathSep){}

Config::Config(const Config & other):
appID(other.appID), defaultProfile(new ConfigProfile(*(other.defaultProfile))),
currentProfile(defaultProfile), _pathSeperator(other._pathSeperator){
    //Copy profiles and set the same currentProfile
    copyProfiles(other);
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

/*const ConfigSection & Config::operator [](const string &path) const {
	return findSection(path);
}

ConfigSection & Config::operator [](const string &path) {
	return findSection(path);
}*/

const ConfigValue & Config::operator[](const string &path) const {
	return findValue(path);
}

ConfigValue & Config::operator[](const string &path) {
	return findValue(path);
}

/*void Config::addSection(const string &name) {
	currentProfile->addSection(name);
}*/

void Config::removeSection(const string &name) {
	currentProfile->removeSection(name);
}

const vector<string> Config::getSectionNames() const {
	return currentProfile->getSectionNames();
}

ConfigSection & Config::findSection(string path) const {
	/*
	 * Starting from the top level section container
	 * select make currentSectionContainer be equal to
	 * the section with the name in path up until the
	 * first period and update path tothe rest of the
	 * string following that period.
	 */
	SectionContainer *  currentSectionContainer = currentProfile;
	string::size_type seperatorPos;
	while ((seperatorPos = path.find(_pathSeperator)) != string::npos) {
		currentSectionContainer = &(currentSectionContainer->getSection(path.substr(0, seperatorPos)));
		path = path.substr(seperatorPos+1);
	}
	/**/

	return currentSectionContainer->getSection(path);
}

ConfigValue & Config::findValue(string path) const {
	string::size_type seperatorPos = path.find_last_of(_pathSeperator);
	return findSection(path.substr(0, seperatorPos)).value(path.substr(seperatorPos+1));
}
