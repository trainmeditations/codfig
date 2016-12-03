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

#ifndef TRAINMEDITATIONS_CODFIGIO_HPP
#define TRAINMEDITATIONS_CODFIGIO_HPP

#include "applicationid.hpp"

namespace codfig {

    /// Abstract IO Class
    /**
     * Declares the basic interface to be implemented by all
     * IO modules.
     */

    class ConfigIO {
    protected:
        ConfigIO(const ApplicationID &_appID);
        virtual string readRawStringValue(const string & path) = 0;
        virtual void writeRawStringValue(const string & path, const string & value) = 0;
    public:
        inline ApplicationID applicationID() const { return appID; }


        template <class T>
        void readValue(const string & path, T & outValue);

        template <class T>
        void writeValue(const string & path, const T & value);

    protected:
        ApplicationID appID;
	};

}

/************************
* Template Definitions *
************************/

#include "codfigio_t.hpp"

#endif
