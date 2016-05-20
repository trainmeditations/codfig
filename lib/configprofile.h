#ifndef TRAINMEDITATIONS_CONFIGPROFILE_H
#define TRAINMEDITATIONS_CONFIGPROFILE_H

#include "entrycontainer.h"
#include <string>

using std::string;

namespace codfig {
    class ConfigProfile:public EntryContainer {
    public:
        ConfigProfile(const string & profileName);
        void setName(const string &newName);
        const string &getName() const;
    private:
        string name;
    };
}

#endif // TRAINMEDITATIONS_CONFIGPROFILE_H
