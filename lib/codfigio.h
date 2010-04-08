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

// File: codfigio.h
// decleration of the ConfigIO controller class

#ifndef TRAINMEDITATIONS_CODFIGIO_H
#define TRAINMEDITATIONS_CODFIGIO_H

#include "codfig.h"

namespace codfig {

	class Config;

	class ConfigIO {
	public:
		virtual void getConfig(Config &) = 0;
		virtual void saveConfig(const Config &) = 0;
	private:
	};
}

#endif
