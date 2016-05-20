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
#include "codfigfileio.h"

#include <iostream>
#include <fstream>
#include <assert.h>

#ifdef _WIN32
#include <shlobj.h>
#endif

using std::string;
using std::fstream;
using namespace codfig;

ConfigFileIO::ConfigFileIO(const string &filename, const ApplicationID & _appID):
_filename(filename), ConfigIO(_appID)
{
    fstream file(filename.c_str());
    file.close();
}

const string ConfigFileIO::stdConfigPath() {
    string configPath;
#ifdef _WIN32
    TCHAR _confPath[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, _confPath);
    assert(result == S_OK);
    configPath = _confPath;
//#elif defined _
#else
    configPath = "./";
#endif
    return configPath;
}
