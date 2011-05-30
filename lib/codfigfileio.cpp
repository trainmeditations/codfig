#include "codfigfileio.h"

#include <iostream>
#include <fstream>
using std::string;
using std::fstream;
using namespace codfig;

ConfigFileIO::ConfigFileIO(const string &filename):
_filename(filename)
{
    fstream file(filename.c_str());
    file.close();
}
