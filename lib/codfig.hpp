/*
 * Copyright © 2006, 2009-2012, 2015-2016, 2018 Shaun Bouckaert
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

// File: codfig.h
// decleration of the Config controller class

#ifndef TRAINMEDITATIONS_CODFIG_HPP
#define TRAINMEDITATIONS_CODFIG_HPP

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <memory>
using std::shared_ptr;

#include "codfigexceptions.hpp"
#include "configentry.hpp"
#include "configprofile.hpp"
#include "codfigio.hpp"

namespace codfig {

    class Config {
    public:
        Config(const string &applicationName,
                const string &applicationVersion,
                const string &developer);
        /*Config(ConfigIO *source);/*create config from source object*/
        Config(const Config &other);
        Config & operator=(const Config &rhs);
        ~Config();

        inline ApplicationID applicationID() const { return appID; }

        inline void setSource(ConfigIO *source)
                { _source=source; }
        //void reload(); //clear the cache or reset time
        //void clearSource();
        
        inline void setPathSeperator(char pathSeparator)
               { _pathSeparator=pathSeparator; }

        size_t addProfile(const string &name);
        void removeProfile(const size_t index);
        void selectProfile(const size_t &index);
        void selectDefaultProfile();
        const vector<string> getProfileList() const;

        void removeEntry(const string &name);
        const vector<string> getEntryNames() const;

        const ConfigEntry &operator[](const string &path) const;
        ConfigEntry &operator[](const string &path);

    private:
        ConfigEntry &findEntry(string path);
        const ConfigEntry &findEntry(string path) const;
        void copyProfiles(const Config &other);

        ApplicationID appID;
        shared_ptr<ConfigProfile> defaultProfile;
        shared_ptr<ConfigProfile> currentProfile;
        vector<shared_ptr<ConfigProfile>> profiles;
        char _pathSeparator;
        ConfigIO * _source;
    };
}

#endif
