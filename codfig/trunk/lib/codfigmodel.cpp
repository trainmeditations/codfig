#include "codfigmodel.h"

using namespace codfig;

ApplicationID::ApplicationID(const string &applicationName, const string &applicationVersion, const string &developer):
appName(applicationName), appVer(applicationVersion), developer(developer){}

const string &ApplicationID::getApplicationName() const {
	return appName;
}

const string &ApplicationID::getApplicationVersion() const {
	return appVer;
}

const string &ApplicationID::getDeveloper() const {
	return developer;
}

ConfigValue::ConfigValue():value(NULL){}

ConfigValue::~ConfigValue() {
	if (value) delete value;
}

SectionContainer::~SectionContainer() {
	for (map<string, ConfigSection *>::iterator iter = subSections.begin(); iter != subSections.end(); ++iter) {
		delete iter->second;
		iter->second = NULL;
	}
}

void SectionContainer::addSection(const string &name) {
	if (!subSections.count(name)) {
		subSections.insert(map<string, ConfigSection *>::value_type(name, new ConfigSection()));
	} else {
		throw duplicate_name("section", name);
	}
}

void SectionContainer::removeSection(const string &name) {
	if (subSections.count(name)) {
		subSections.erase(name);
	} //should I throw an exception on else?
}

ConfigSection & SectionContainer::getSection(const std::string &name) {
	if (subSections.count(name)) {
		return *subSections[name];
	} else {
		throw bad_path(name);
	}
}

const vector<string> SectionContainer::getSectionNames() const {
	vector<string> names;
	for (map<string, ConfigSection *>::const_iterator iter = subSections.begin();
		 iter != subSections.end(); ++iter) {
			 names.push_back(iter->first);
	}
	return names;
}

ConfigSection::~ConfigSection() {
	for (map<string, ConfigValue *>::iterator iter = values.begin(); iter != values.end(); ++iter) {
		delete iter->second;
		iter->second = NULL;
	}
}

const vector<string> ConfigSection::getValueNames() const {
	vector<string> names;
	for (map<string, ConfigValue *>::const_iterator iter = values.begin();
		 iter != values.end(); ++iter) {
			 names.push_back(iter->first);
	}
	return names;
}

ConfigValue & ConfigSection::value(const string &name) {
	if (values.count(name)) {
		return *values[name];
	} else {
		throw bad_path(name);
	}
}

ConfigProfile::ConfigProfile(const string & profileName):name(profileName){}

const string & ConfigProfile::getName() const {
	return name;
}

void ConfigProfile::setName(const string &newName) {
	name = newName;
}
