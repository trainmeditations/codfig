#include <algorithm>

#include "codfig.h"

using namespace codfig;

/*
 * main Config class
 */

Config::Config(const ApplicationID &applicationID):
appID(applicationID), defaultProfile(new ConfigProfile("default")),
currentProfile(defaultProfile){}

Config::~Config(){
	currentProfile = NULL;
	delete defaultProfile;
	for (vector<ConfigProfile *>::iterator iter = profiles.begin(); iter != profiles.end(); ++iter) {
		delete *iter;
		*iter = 0;
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

const ConfigSection & Config::operator [](const string &path) const {
	return findSection(path);
}

ConfigSection & Config::operator [](const string &path) {
	return findSection(path);
}

const ConfigValue & Config::operator ()(const string &path) const {
	return findValue(path);
}

ConfigValue & Config::operator ()(const string &path) {
	return findValue(path);
}

void Config::addSection(const string &name) {
	currentProfile->addSection(name);
}

void Config::removeSection(const string &name) {
	currentProfile->removeSection(name);
}

ConfigSection & Config::findSection(string path) const {
	SectionContainer *  currentSectionContainer = currentProfile;
	string::size_type seperatorPos;
	while (seperatorPos = path.find('.') != string::npos) {
		currentSectionContainer = &(currentSectionContainer->getSection(path.substr(0, seperatorPos)));
		path = path.substr(seperatorPos+1);
	}
	return currentSectionContainer->getSection(path);
}

ConfigValue & Config::findValue(string path) const {
	string::size_type seperatorPos = path.find_last_of('.');
	return findSection(path.substr(0, seperatorPos)).value(path.substr(seperatorPos+1));
}
