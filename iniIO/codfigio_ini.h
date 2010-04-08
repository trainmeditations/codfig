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

// File: codfigio_ini.h
// decleration of the ConfigIO controller class for INI files

#ifndef TRAINMEDITATIONS_CODFIGIO_INI_H
#define TRAINMEDITATIONS_CODFIGIO_INI_H

#include "codfigfileio.h"

#include <string>
using std::string;

namespace codfig {
	class ConfigIOini:public ConfigFileIO {
	public:
		ConfigIOini(const string & iniFilePath, const char &sectionPathSeperator = '.');
		void getConfig(Config &);
		void saveConfig(const Config &);
	private:
		void processLine(string line);
		void addSections(string line);
		void addSubSections(string path);
		void addValue(string line);

		void writeSection(const ConfigSection & section, const string & currentSectPath, std::ofstream & out);
		string _path;
		Config * _config;
		char _sectPathSep;
		ConfigSection * _currentSection;
	};
}

#endif
