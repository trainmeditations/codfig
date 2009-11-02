/*
 * Copyright Shaun Bouckaert 2009
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

// File: codfigexceptions.h
// Decleration of exception classes
// Copyright (C) Shaun Bouckaert

#ifndef TRAINMEDITATIONS_CODFIGEXCEPTIONS_H
#define TRAINMEDITATIONS_CODFIGEXCEPTIONS_H

#include <stdexcept>

namespace codfig {

	class bad_path: public std::runtime_error {
		public:
			explicit bad_path(const std::string &path):std::runtime_error("Bad path to section: " + path){}
	};

	class wrong_type: public std::logic_error {
		public:
			explicit wrong_type(const std::string &name):std::logic_error("Wrong type for value " + name + "."){}
	};

	class value_not_set: public std::runtime_error {
		public:
			explicit value_not_set(const std::string &name):std::runtime_error("Value not set for value " + name + "."){}
	};

	class duplicate_name: public std::runtime_error {
		public:
			explicit duplicate_name(const std::string &type, const std::string &name):std::runtime_error("A " + type + " named \"" + name + "\" already exists."){}
	};
}

#endif
