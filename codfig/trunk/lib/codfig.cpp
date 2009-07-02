#include "codfig.h"

using namespace codfig;

/*
 * codfig_profile sub class
 */

Codfig::codfig_profile::codfig_profile(string profile_name)
:profile_name(profile_name){}

Codfig::codfig_profile::~codfig_profile() {}

/*
 * main Codfig class
 */

Codfig::Codfig(string appname="", int version=0):
    appname(appname), version(version),
    default_profile(new codfig_profile("Default")),
    other_profiles(vector<codfig_profile *>()) {
        //current_profile = default_profile;
    }

Codfig::~Codfig() {
    delete default_profile;
    vector<codfig_profile *>::iterator iter;
    for (iter = other_profiles.begin(); iter != other_profiles.end(); iter++) {
        delete *iter;
    }
}

