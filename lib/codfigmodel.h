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

    class ConfigValue {
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
        ConfigValue();
        ConfigValue(const ConfigValue & other);
        ConfigValue & operator=(const ConfigValue & rhs);
        virtual ~ConfigValue();
        string stringValue() const;
        template <class T>
            const T &value() const;
        template <class T>
            T &value();
        int intValue();
    private:
        AbstractValueBox * _value;
    };

    class ConfigEntry;

    class EntryContainer {
    public:
        EntryContainer();
        EntryContainer(const EntryContainer & other);
        EntryContainer & operator=(const EntryContainer & rhs);
        virtual ~EntryContainer();
        ConfigEntry * addEntry(const string &name);
        void removeEntry(const string &name);
        ConfigEntry & getEntry(const string &name);
        const ConfigEntry & getEntry(const string &name) const;
        const vector<string> getEntryNames() const;
        bool hasEntry(const string &name) const;
    private:
        void copyEntries(const EntryContainer & other);
        map<string, ConfigEntry *> subEntries;
    };

    class ConfigEntry:public EntryContainer, public ConfigValue {
    public:
        ConfigEntry(EntryContainer *parent, const string &name);
        ConfigEntry(const ConfigEntry & other, EntryContainer *parent);
        inline const string &path() const {return _path;}
        ~ConfigEntry();
    private:
        ConfigEntry(const ConfigEntry & other);
        ConfigEntry & operator=(const ConfigEntry & rhs);
        string _path;
        EntryContainer *_parent;
    };

    class ConfigProfile:public EntryContainer {
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
