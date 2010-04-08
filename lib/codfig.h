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

// File: codfig.h
// decleration of the Config controller class

#ifndef TRAINMEDITATIONS_CODFIG_H
#define TRAINMEDITATIONS_CODFIG_H

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "codfigexceptions.h"
#include "codfigmodel.h"

namespace codfig {

    class Config {
		public:
			Config(const ApplicationID &applicationID);
			Config(const Config &other);
			Config & operator=(const Config &rhs);
			~Config();

			inline const ApplicationID & applicationID() const { return appID; }

			inline void setPathSeperator(char pathSeperator)
			{ _pathSeperator=pathSeperator; }

			int addProfile(const string &name);
			void removeProfile(const int &index);
			void selectProfile(const int &index);
			void selectDefaultProfile();
			const vector<string> getProfileList() const;

			void addSection(const string &name);
			void removeSection(const string &name);
			const vector<string> getSectionNames() const;

			const ConfigSection &operator[](const string &path) const;
			ConfigSection &operator[](const string &path);

			const ConfigValue &operator()(const string &path) const;
			ConfigValue &operator()(const string &path);

		private:
			ConfigSection &findSection(string path) const;
			ConfigValue &findValue(string path) const;
			void copyProfiles(const Config &other);

			ApplicationID appID;
			ConfigProfile * defaultProfile;
			ConfigProfile * currentProfile;
			vector<ConfigProfile *> profiles;
			char _pathSeperator;
    };
}

#endif
