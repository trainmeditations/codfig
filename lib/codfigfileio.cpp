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
#elif defined _
#endif
    return configPath;
}
