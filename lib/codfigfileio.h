/*
 * Copyright © 2009-2011, 2015 Shaun Bouckaert
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

// File: codfigfileio.h
// decleration of the ConfigIO controller class for files

#ifndef TRAINMEDITATIONS_CODFIGFILEIO_H
#define TRAINMEDITATIONS_CODFIGFILEIO_H

#include <string>
#include <fstream>
#include "codfig.h"
#include "codfigio.h"

namespace codfig {
	class ConfigFileIO:public ConfigIO {
    protected:
        ConfigFileIO(const std::string &filename, const ApplicationID & _appID);
    public:
        static const std::string stdConfigPath();
	protected:
        std::string _filename;
	};
}

#endif
