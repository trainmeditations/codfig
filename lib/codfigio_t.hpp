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

#ifndef TRAINMEDITATIONS_CODFIGIO_T_HPP
#define TRAINMEDITATIONS_CODFIGIO_T_HPP

#include "codfigio.hpp"

#include <sstream>

using std::stringstream;

using namespace codfig;

template <class T>
void ConfigIO::writeValue(const string &path, const T & value) {
    stringstream tempval;
    tempval << value;
    writeRawStringValue(path, tempval.str());
}

template <class T>
T ConfigIO::readValue(const string &path) {
    stringstream tempval(readRawStringValue(path));
    T val;
    tempval >> val;
    return val;
}

#endif //TRAINMEDITATIONS_CODFIGIO_T_H
