// File: codfig.h
// decleration of the codfig class and subclasses
// Copyright (C) 2006 Shaun Bouckaert

#ifndef NAGCHAMPA_CODFIG_H
#define NAGCHAMPA_CODFIG_H

#include <string>
         using std::string;
#include <vector>
         using std::vector;
#include "codexception.h"

namespace codfig {

    class codfig {
        private:
            class conf_data_int: public conf_data{
                public:
                    void stringValue() const;
                    void value(int & int_value) const; //accessor
                    void value(const int & int_value); //mutator
                private:
                    int value;
            };
            class conf_data_bool: public conf_data{
                public:
                    void stringValue() const;
                    void value(bool & bool_value) const; //accessor
                    void value(const bool & bool_value); //mutator
                private:
                    bool value;
            };
            class conf_data_string: public conf_data{
                public:
                    void stringValue() const;
                    void value(string & string_value) const; //accessor
                    void value(const string & string_value); //mutator
                private:
                    string value;
            };
            class conf_data_double: public conf_data{
                public:
                    void stringValue() const;
                    void value(double & double_value) const; //accessor
                    void value(const double & double_value); //mutator
                private:
                    double value;
            };
            class conf_data{
                /*public:
                    conf_data();
                    conf_data(const conf_data &);
                    const conf_data & operator=(const conf_data &);
                    ~conf_data();

                    //type parsing
                    void value(int & int_value) const;
                    void value(const int & int_value);
                    void value(float & float_value) const;
                    void value(const float & float_value);
                    void value(string & string_value) const;
                    void value(const string & string_value);
                    void value(bool & bool_value) const;
                    void value(const bool & bool_value);

                    //type checking
                    template <class bad_t>
                            void value(bad_t & bad_t_value) const;
                    template <class bad_t>
                            void value(const bad_t & bad_t_value) const;
                private:
                    enum types{INT, FLOAT, STRING, BOOL};
                    types type;
                    union {int intValue; float floatValue;
                        string * stringValue; bool boolValue;} conf_value;*/
                public:
                    virtual void stringValue() const = 0;
            };
            class codfig_node{
                public:
                    codfig_node(string node_id);
                    codfig_node(const codfig_node &);
                    const codfig_node & operator=(const codfig_node &);
                    ~codfig_node();
                    //insert specialised methods for allowed data types which cast
                    //down to the correct conf_data object, if the accessor can't
                    //cast the type, then throw an exception
                    void setValue(string name="", const int & value);
                    void getValue(string name="", int & value) const;

                    void setValue(string name="", const bool & value);
                    void getValue(string name="", bool & value) const;

                    void setValue(string name="", const double & value);
                    void getValue(string name="", double & value) const;

                    void setValue(string name="", const string & value);
                    void getValue(string name="", string & value) const;

                    template <class bad_data_t>
                            void setValue(string name="", const bad_data_t & value);
                    template <class bad_data_t>
                            void getValue(string name="", bad_data_t & value) const;
                private:
                    vector<codfig_node *> nodes;
                    conf_data * value;
                    string name;
            };
            class codfig_section{
                public:
                    codfig_section(string section_name);
                    codfig_section(const codfig_section &);
                    const codfig_section & operator=(const codfig_section &);
                    ~codfig_section();

                    void addSection(string name);
                    codfig_section & section(string name);
                    void removeSection(string name);

                    template <class conf_data_t>
                            void setValue(string name, const conf_data_t & value);
                    template <class conf_data_t>
                            void getValue(string name, conf_data_t & value) const;

                private:
                    string name;
                    vector<codfig_section *> sections;
                    vector<codfig_node *> nodes;
            };
            class codfig_profile{
                public:
                    codfig_profile(string profile_name);
                    codfig_profile(const codfig_profile &);
                    const codfig_profile & operator=(const codfig_profile &);
                    ~codfig_profile();

                    void addSection(string name);
                    codfig_section & section(string name);
                    void removeSection(string name);

                private:
                    vector<codfig_section *> * sections;
                    string profile_name;
            };
            string appname;
            int version;
            codfig_profile * main_profile;
            vector<codfig_profile *> * other_profiles;
            codfig_profile * current_profile;
        public:
            codfig(string appname="", int version=0);

            codfig(const codfig &);
            const codfig & operator=(const codfig &);
            ~codfig();

            //for accessing and setting values
            template <class conf_data_t>
                const conf_data_t & operator[] (string path) const;
            template <class conf_data_t>
                conf_data_t & operator[] (string path);

            //for setting up the config layout
            void removeValue(string path);
            void addSection(string path);
            void removeSection(string path);

            const vector<string> & sections(string path="") const;
            const vector<string> & config_values(string path="") const;

            //profile stuff
            void addProfile(string name);
            void selectProfile(string name);
            void removeProfile(string name);
            void copyProfile(string oldProfile, string newProfile);
    };
}

#endif
