/*
 * Copyright © 2009, 2015 Shaun Bouckaert
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

// File: codfigexceptions.hpp
// Decleration of exception classes

#ifndef TRAINMEDITATIONS_CODFIGEXCEPTIONS_HPP
#define TRAINMEDITATIONS_CODFIGEXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace codfig {

	class bad_path: public std::runtime_error {
		public:
			explicit bad_path(const std::string &path);
	};

	class wrong_type: public std::logic_error {
		public:
			explicit wrong_type(const std::string &name);
	};

	class value_not_set: public std::runtime_error {
		public:
			explicit value_not_set(const std::string &name);
	};

	class duplicate_name: public std::runtime_error {
		public:
			explicit duplicate_name(const std::string &type, const std::string &name);
	};
}

#endif
