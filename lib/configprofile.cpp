/*
 * Copyright © 2009-2011, 2015-2016 Shaun Bouckaert
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

#include "configprofile.hpp"

using namespace codfig;

ConfigProfile::ConfigProfile(const string & profileName):name(profileName)
{}

const string & ConfigProfile::getName() const
{
    return name;
}

void ConfigProfile::setName(const string &newName)
{
    name = newName;
}
