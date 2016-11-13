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
#include <sstream>
#include <assert.h>

#ifdef _WIN32
#include <shlobj.h>
const char _pathSep = '\\';
#endif

using std::string;
using std::fstream;
using std::stringstream;
using namespace codfig;

ConfigFileIO::ConfigFileIO(const string &filename, const ApplicationID & _appID):
_filename(filename), ConfigIO(_appID)
{
    fstream file(filename.c_str());
    file.close();
}

string ConfigFileIO::stdConfigPath(){
    stringstream cfgPath;
    //Windows first, then *nixes
#ifdef WIN32
    //using ansi windows for now
    //assume appdata directory exists
    char _confPath[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, _confPath))) {
        throw std::runtime_error("Unable to get standard config path from system");
    }
    cfgPath<< _confPath;
    cfgPath<< _pathSep;
#elif defined(__unix__)
    //Follow XDG Specification
    //Assume $XDG_CONFIG_HOME exists if it's set
    //Assume $HOME exists if it's set
    const char * _confHome = getenv("XDG_CONFIG_HOME");
    if (!_confHome) {
        //XDG_CONFIG_HOME isn't set. USE $HOME/.config
        _confHome = getenv("HOME");
        if (!_confHome) throw std::runtime_error("Unable to find home directory");
        cfgPath << _confHome;
        cfgPath << _pathSep;
        cfgPath << ".config";
        if (!createDirectoryIfNotExist(cfgPath.str()))
            throw std::runtime_error("Unable to create .config in user home");
    } else {
        cfgPath << _confHome;
    }
    cfgPath << _pathSep;
#else
    throw std::logic_error("Incompatible OS");
#endif
    return cfgPath.str();
}
