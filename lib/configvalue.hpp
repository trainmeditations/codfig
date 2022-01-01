/*
 * Copyright © 2009-2011, 2015-2016, 2021-2022 Shaun Bouckaert
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

#ifndef TRAINMEDITATIONS_CONFIGVALUE_HPP
#define TRAINMEDITATIONS_CONFIGVALUE_HPP

#include <string>

using std::string;

namespace codfig {
    class ConfigValue {
    protected:
        class AbstractValueBox {
        public:
            virtual AbstractValueBox * cloneValue() const = 0;
            virtual ~AbstractValueBox() = 0;
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
        //make value() private?
        template <class T>
            const T &value() const;
        template <class T>
            T &value();
        int intValue();
    private:
        AbstractValueBox * _value;
    };
}

/************************
* Template Definitions *
************************/

#include "configvalue_t.hpp"

#endif // TRAINMEDITATIONS_CONFIGVALUE_H
