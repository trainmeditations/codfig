// File: codfig.h
// decleration of the Config controller class
// Copyright (C) 2006 Shaun Bouckaert

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
			~Config();

			int addProfile(const string &name);
			void removeProfile(const int &index);
			void selectProfile(const int &index);
			void selectDefaultProfile();
			const vector<string> getProfileList() const;

			const ConfigSection &operator[](const string &path) const;
			ConfigSection &operator[](const string &path);

			const ConfigValue &operator()(const string &path) const;
			ConfigValue &operator()(const string &path);

		private:
			ConfigSection &findSection(string path) const;
			ConfigValue &findValue(string path) const;

			ApplicationID appID;
			ConfigProfile * defaultProfile;
			ConfigProfile * currentProfile;
			vector<ConfigProfile *> profiles;
    };
}

#endif
