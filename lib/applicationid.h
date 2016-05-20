/*
 * Copyright © 2016 Shaun Bouckaert
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

#ifndef TRAINMEDITATIONS_APPLICATIONID_H
#define TRAINMEDITATIONS_APPLICATIONID_H

#include <string>

using std::string;

namespace codfig {
    class ApplicationID {
    public:
        ApplicationID(const string &applicationName,
                        const string &applicationVersion,
                        const string &developer);
        inline const string &applicationName() const { return _appName;}
        inline const string &applicationVersion() const {return _appVer;}
        inline const string &developer() const {return _developer;}
    private:
        string _appName;
        string _appVer;
        string _developer;
    };
}

#endif // TRAINMEDITATIONS_APPLICATIONID_H
