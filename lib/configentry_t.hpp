/*
 * Copyright © 2021-2022 Shaun Bouckaert
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

#ifndef TRAINMEDITATIONS_CONFIGENTRY_T_HPP
#define TRAINMEDITATIONS_CONFIGENTRY_T_HPP

#include "configentry.hpp"

#include <string>

using namespace codfig;
using std::string;

template <class T>
    ConfigEntry &codfig::operator<< (ConfigEntry &entry, const T &value) {
        entry.value<T>() = value;
        return entry;
    }

/*template < std::size_t N >
    void codfig::operator<<(ConfigEntry &entry, const char(&value)[N]) {
        entry.value<string>() = value;
    }*/

template <class T>
    void codfig::operator>> (const ConfigEntry &entry, T &value) {
        value = entry.value<T>();
    }

template <class T>
    bool ConfigEntry::operator==(const T &other) {
        return this->value<T>() == other;
    }
    
#endif //TRAINMEDITATIONS_CONFIGVALUE_T_HPP
