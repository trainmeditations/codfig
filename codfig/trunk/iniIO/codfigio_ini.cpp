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

#include <iostream>
#include <fstream>
#include <algorithm>

#include "codfigio_ini.h"

using codfig::ConfigIOini;
using codfig::Config;

ConfigIOini::ConfigIOini(const string &iniFilePath, const char &sectionPathSeperator):
		_path(iniFilePath), _config(NULL),
		_sectPathSep(sectionPathSeperator),
		_currentSection(NULL)
{}

void ConfigIOini::getConfig(Config & config)
{
	_config = &config;
	std::ifstream in( _path.c_str(), std::ifstream::in);
	while (in.good()) {
		string line;
		std::getline(in, line);
		//std::cout << line << std::endl;
		processLine(line);
	}
	_config = NULL;
}

void ConfigIOini::saveConfig(const Config & config)
{
	std::ofstream out( _path.c_str(),  std::ofstream::out | std::ofstream::trunc);
	out << ";CODFIG: " << config.applicationID().applicationName()
			<< " Version: " << config.applicationID().applicationVersion()
			<< " By: " << config.applicationID().developer() << std::endl;
	vector<string> sections(config.getSectionNames());
	for (vector<string>::const_iterator iter = sections.begin(); iter != sections.end(); ++iter) {
		writeSection(config[*iter], *iter, out);
	}
}

void ConfigIOini::writeSection(const ConfigSection &section, const string &currentSectPath, std::ofstream & out)
{
	vector<string> names(section.getValueNames());
	if (names.size() > 0) {
		out << '[' << currentSectPath << ']' << std::endl;
		for (vector<string>::const_iterator iter = names.begin(); iter != names.end(); ++iter) {
			out << *iter << "=" << section.value(*iter).stringValue() << std::endl;
		}
	}
	names = section.getSectionNames();
	for (vector<string>::const_iterator iter = names.begin(); iter != names.end(); ++iter) {
		writeSection(section.getSection(*iter), currentSectPath + "." + *iter, out);
	}
}

void ConfigIOini::processLine(string line)
{
	if (line.length() > 0) {
		size_t pos;
		//trim whitespace from front
		line = line.substr((pos=line.find_first_not_of(" \t"))==std::string::npos?0:pos);
		switch (line[0]) {

			case ('[') : {
				addSections(line);
			}break;

			case (';') : {
				//ignore comment
			}break;

			default : {
				if (line.find('=')!=std::string::npos)
					addValue(line);
			}
		}
	}
}

void ConfigIOini::addSections(string line)
{
	_currentSection = NULL;
	string sectionPath = line.substr(1, line.find(']')-1);
	if (_sectPathSep == '\0') {
		_config->addSection(sectionPath);
		_currentSection = &((*_config)[sectionPath]);
	} else {
		//split string for subsections
		size_t sepLoc = std::string::npos;
		string sectionName = sectionPath.substr(0, sepLoc = sectionPath.find(_sectPathSep));
		_config->addSection(sectionName);
		_currentSection = &((*_config)[sectionName]);
		sectionPath = sepLoc==std::string::npos?"":sectionPath.substr(sepLoc+1);
		addSubSections(sectionPath);
	}
}

void ConfigIOini::addSubSections(string path)
{
	if (path != "") {
		size_t sepLoc = std::string::npos;
		string sectionName = path.substr(0, sepLoc = path.find(_sectPathSep));
		_currentSection->addSection(sectionName);
		_currentSection = &((*_currentSection).getSection(sectionName));
		path = sepLoc==std::string::npos?"":path.substr(sepLoc+1);
		addSubSections(path);
	}
}

void ConfigIOini::addValue(string line)
{
	string optionName = line.substr(0, line.find('=')); // optionName is everything before the =
	optionName = optionName.substr(0, optionName.find_last_not_of(" \t")+1); // remove any whitespace from the end
	string value = line.substr(line.find('=')+1); //value is everything after the =
	size_t firstNonWhitespace = value.find_first_not_of(" \t");
	value = firstNonWhitespace == std::string::npos?"":value.substr(firstNonWhitespace); // remove any whitespace from the front
	value = value.substr(0, value.find(';'));
	_currentSection->value(optionName).value<string>() = value;
}
