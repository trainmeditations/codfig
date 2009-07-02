// File: codfig.h
// decleration of the codfig class and subclasses
// Copyright (C) 2006 Shaun Bouckaert

#ifndef TRAINMEDITATIONS_CODFIG_H
#define TRAINMEDITATIONS_CODFIG_H

#include <string>
using std::string;
#include <vector>
using std::vector;
#include "codexception.h"
#include "codtype.h"

namespace codfig {

    class Codfig {
        private:
            class codfig_node{
                public:
                    codfig_node(string node_id);
                    codfig_node(const codfig_node &);
                    const codfig_node & operator=(const codfig_node &);
                    ~codfig_node();

                    template <class data_t>
                        void setValue(string name, const data_t & value);
                    template <class data_t>
                        void getValue(string name, data_t & value) const;

                private:
                    string name;
                    AbstractCodType * value;
            };
        public:
            class codfig_section{
                public:
                    void addSection(string name);
                    codfig_section & section(string name);
                    void removeSection(string name);

                    template <class T>
                        void addValue(string path, T value);
                    void removeValue(string path);

                    const AbstractCodType & operator[] (const char * path) const;
                    AbstractCodType & operator[] (const char * path);

                private:
                    friend class Codfig;

                    codfig_section(string section_name);
                    codfig_section(const codfig_section &);
                    const codfig_section & operator=(const codfig_section &);
                    ~codfig_section();

                    string name;
                    vector<codfig_section *> sections;
                    vector<codfig_node *> nodes;
            };
        private:
            class codfig_profile{
                public:
                    codfig_profile(string profile_name);
                    codfig_profile(const codfig_profile &);
                    const codfig_profile & operator=(const codfig_profile &);
                    ~codfig_profile();

                    /* void addSection(string name);
                       codfig_section & section(string name);
                       void removeSection(string name);*/

                private:
                    vector<codfig_section *> * sections;
                    string profile_name;
            };

            //Codfig Fields
            string appname;
            int version;
            codfig_profile * default_profile;
            vector<codfig_profile *> other_profiles;
            codfig_profile * current_profile;

            //Codfig Private Methods
        public:
            Codfig(string, int);

            //the big 3
            Codfig(const Codfig &);
            const Codfig & operator=(const Codfig &);
            ~Codfig();

            //for setting up the config layout
            void addSection(string path);
            void removeSection(string path);

            //for looking at config layout
            const vector<string> & sections(string path="") const;
            const vector<string> & config_values(string path="") const;

            //profile stuff
            void addProfile(string name);
            void selectProfile(string name);
            void removeProfile(string name);
            void copyProfile(string oldProfile, string newProfile);
            /*
             * develop as cheap copies, only copy data if the profile
             * copied from or copied to changes it
             */
    };
}

#endif
