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

#ifndef TRAINMEDITATIONS_CODFIGIO_H
#define TRAINMEDITATIONS_CODFIGIO_H

#include <string>
#include <vector>
#include "codfig.h"

using std::string;
using std::vector;

namespace codfig {

    /// Abstract IO Class
    /**
     * Declares the basic interface to be implemented by all
     * IO modules.
     */

    class ConfigIO {
    public:
        virtual ~ConfigIO() = 0;
        virtual ApplicationID getAppID() = 0;
        void readConfig(Config &config);
        void writeConfig(Config &config);

        //virtual void writeValue(const ConfigEntry &entry) = 0;
        //virtual void removeEntry(const string &path) = 0;

    protected:

        //READING
        void startProfile(Config &config, const string &name);
        void addPath(Config &config, const string &path);
        template <class T>
            void addEntry(Config &config, const string &path, const T& value);

        //WRITING

	};
}

/************************
 * Template Definitions *
 ************************/

#include "codfigio_t.h"

#endif
