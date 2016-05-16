/*
 * Copyright © 2009-2012, 2015 Shaun Bouckaert
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

#ifndef TRAINMEDITATIONS_CODFIGIO_H
#define TRAINMEDITATIONS_CODFIGIO_H

#include "codfig.h"

namespace codfig {

    /// Abstract IO Class
    /**
     * Declares the basic interface to be implemented by all
     * IO modules.
     */

    class ConfigIO {
    protected:
        ConfigIO(const ApplicationID &_appID);
    public:
        //force abstract with pure virtual destructor
        virtual ~ConfigIO() = 0;

        inline ApplicationID applicationID() const { return appID; }

        /*
         * config will be empty except for an empty default profile which is also current profile
         */
        virtual void readConfig(Config &config) = 0;

        virtual void writeConfig(Config &config) = 0;

    protected:
        ApplicationID appID;
	};

}

#endif
