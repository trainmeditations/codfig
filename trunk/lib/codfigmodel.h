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

// File: codfigmodel.h
// model of configuration data

#ifndef TRAINMEDITATION_CODFIGMODEL_H
#define TRAINMEDITATION_CODFIGMODEL_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

namespace codfig{
    class ApplicationID {
    public:
        ApplicationID(const string &applicationName,
                        const string &applicationVersion,
                        const string &developer);
        inline const string &applicationName() const { return _appName;}
        inline const string &applicationVersion() const {return _appVer;}
        inline const string &developer() const {return _developer;}
    private:
        string _appName;
        string _appVer;
        string _developer;
    };

    class ConfigEntry {
    protected:
        class AbstractValueBox {
        public:
            virtual AbstractValueBox * cloneValue() const = 0;
            virtual ~AbstractValueBox();
            virtual string getStringValue() const = 0;
        };

        template <class T> class ValueBox:public AbstractValueBox {
        public:
            ValueBox();
            ValueBox(T value);
            ~ValueBox();
            ValueBox<T> * cloneValue() const;
            inline const T &value() const {return _value;}
            inline T &value() { return _value;}
            string getStringValue() const;
            void setValueByString(const string &stringValue);
        private:
            T _value;
        };

    public:
        ConfigEntry();
        ConfigEntry(const ConfigEntry & other);
        ConfigEntry & operator=(const ConfigEntry & rhs);
        virtual ~ConfigEntry();
        string stringValue() const;
        enum EntryType {
            Section,
            Value
        };
        virtual EntryType entryType() const = 0;
        template <class T>
            const T &value() const;
        template <class T>
            T &value();
        int intValue();
        bool hasChanged() const;
        void setChanged(bool);
    private:
        AbstractValueBox * _value;
        bool changed;
    };

    class ConfigValue: public ConfigEntry {
    public:
        inline EntryType entryType() const {return Value;}
    };

    class ConfigSection;

    class SectionContainer { //should this protected inherit from map<string, ConfigSection *> ?
    public:
        SectionContainer();
        SectionContainer(const SectionContainer & other);
        SectionContainer & operator=(const SectionContainer & rhs);
        virtual ~SectionContainer();
        ConfigSection * addSection(const string &name);
        void removeSection(const string &name);
        ConfigSection & getSection(const string &name);
        const ConfigSection & getSection(const string &name) const;
        const vector<string> getSectionNames() const;
        bool hasSection(const string &name) const;
    private:
        void copySections(const SectionContainer & other);
        map<string, ConfigSection *> subSections;
    };

    class ConfigSection:public SectionContainer, public ConfigEntry {
    public:
        ConfigSection();
        ConfigSection(const ConfigSection & other);
        ConfigSection & operator=(const ConfigSection & rhs);
        ConfigSection(const ConfigValue &value);
        ~ConfigSection();
        inline EntryType entryType() const {return Section;}
        const vector<string> getValueNames() const;
        ConfigValue & value(const string &name);
        const ConfigValue & value(const string &name) const;
        ConfigEntry & entry(const string &name);
        const ConfigEntry & entry(const string &name) const;
        bool hasValue(const string &name) const;
        void removeValue(const string &name);
    private:
        void copyValues(const ConfigSection & other);
        map<string, ConfigValue *> values;
    };

    class ConfigProfile:public SectionContainer {
    public:
        ConfigProfile(const string & profileName);
        void setName(const string &newName);
        const string &getName() const;
    private:
        string name;
    };
}

/************************
* Template Definitions *
************************/

#include "codfigmodel_t.h"

#endif
