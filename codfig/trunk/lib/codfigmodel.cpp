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

ConfigValue::AbstractValueBox::~AbstractValueBox(){}

ConfigValue::ConfigValue():value(NULL){}

ConfigValue::ConfigValue(const ConfigValue & other):value(NULL){
    if (other.value) value = other.value->cloneValue();
}

ConfigValue & ConfigValue::operator=(const ConfigValue & other){
    if (this != &other) {
        delete value;
        if (other.value) {
            value = other.value->cloneValue();
        } else {
            value = NULL;
        }
    }
    return *this;
}

ConfigValue::~ConfigValue() {
	if (value) delete value;
}

SectionContainer::SectionContainer(){}

SectionContainer::SectionContainer(const SectionContainer & other){
    copySections(other);
}

SectionContainer & SectionContainer::operator=(const SectionContainer & rhs){
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

void SectionContainer::copySections(const SectionContainer & other){
    for (map<string, ConfigSection *>::const_iterator other_iter = other.subSections.begin();
      other_iter != other.subSections.end(); other_iter++){
        subSections[other_iter->first] = new ConfigSection(*(other_iter->second));
    }
}

SectionContainer::~SectionContainer() {
	for (map<string, ConfigSection *>::iterator iter = subSections.begin(); iter != subSections.end(); ++iter) {
		delete iter->second;
		iter->second = NULL;
	}
}

void SectionContainer::addSection(const string &name) {
	if (!subSections.count(name)) {
		//subSections.insert(map<string, ConfigSection *>::value_type(name, new ConfigSection()));
		subSections[name] = new ConfigSection();
	} else {
		throw duplicate_name("section", name);
	}
}

void SectionContainer::removeSection(const string &name) {
	if (subSections.count(name)) {
	    delete subSections[name];
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

ConfigSection::ConfigSection(){}

ConfigSection::ConfigSection(const ConfigSection & other):SectionContainer(other){
    copyValues(other);
}

ConfigSection & ConfigSection::operator=(const ConfigSection & rhs) {
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

void ConfigSection::copyValues(const ConfigSection & other){
    for (map<string, ConfigValue *>::const_iterator other_iter = other.values.begin();
      other_iter != other.values.end(); ++other_iter){
        values[other_iter->first] = new ConfigValue(*(other_iter->second));
    }
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
		ConfigValue * newValue = new ConfigValue();
		values.insert(map<string, ConfigValue *>::value_type(name, newValue));
		return *newValue;
	}
}

ConfigProfile::ConfigProfile(const string & profileName):name(profileName){}

const string & ConfigProfile::getName() const {
	return name;
}

void ConfigProfile::setName(const string &newName) {
	name = newName;
}
