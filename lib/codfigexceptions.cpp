/*
 * Copyright © 2009-2010, 2015 Shaun Bouckaert
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

// File: codfigexceptions.cpp
// Definition of exception classes

#include "codfigexceptions.hpp"

using namespace codfig;

bad_path::bad_path(const std::string &path):std::runtime_error("Bad path to section: " + path){}

wrong_type::wrong_type(const std::string &name):std::logic_error("Wrong type for value " + name + "."){}

value_not_set::value_not_set(const std::string &name):std::runtime_error("Value not set for value " + name + "."){}

duplicate_name::duplicate_name(const std::string &type, const std::string &name):std::runtime_error("An " + type + " named \"" + name + "\" already exists."){}
