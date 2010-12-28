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
#include "codfigmodel.h"

using std::string;

namespace codfig {

    /// Abstract IO Class
    /**
     * Declares the basic interface to be implemented by all
     * IO modules.
     */

	class ConfigIO {
    protected:

        /// Retrieve a value from the IO Source
        /**
         * Implement this function to return a ConfigEntry containing
         * the value stored as the appropriate type. Should be a
         * a ConfigValue if the path points to a node, and a
         * ConfigSection if it points to a section value.
         * @param[in] path   The path to the entry.
         * @param[out] value The ConfigEntry containing the value.
         */
        virtual void getValue(const string &path, ConfigEntry &value) = 0;

        /// Write a value to the IO Source
        /**
         * Implement this function to write a ConfigEntry containing
         * the value to be stored.
         */
        virtual void writeValue(const string &, ConfigEntry &) = 0;
	};
}

#endif
