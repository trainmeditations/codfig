/*
 * Copyright © 2009-2011 Shaun Bouckaert
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

// File: codfigmodel_t.h
// codfig model template definitions

#ifndef TRAINMEDITATION_CODFIGMODEL_T_H
#define TRAINMEDITATION_CODFIGMODEL_T_H

#include "codfigmodel.h"
#include "codfigexceptions.h"
#include <sstream>

using namespace codfig;
using std::ostringstream;
using std::istringstream;

template <class T>
        ConfigValue::ValueBox<T>::ValueBox(){}

template <class T>
        ConfigValue::ValueBox<T>::ValueBox(T value):_value(value){}

template <class T>
        ConfigValue::ValueBox<T>::~ValueBox(){}

template <class T>
        ConfigValue::ValueBox<T> * ConfigValue::ValueBox<T>::cloneValue() const {
    return new ValueBox<T>(*this);
}

template <class T>
        string ConfigValue::ValueBox<T>::getStringValue() const {
    ostringstream outstring;
    outstring << _value;
    return outstring.str();
}

template <class T>
        void ConfigValue::ValueBox<T>::setValueByString(const std::string &stringValue) {
    istringstream instream(stringValue);
    instream >> _value;
}

template <class T>
        const T &ConfigValue::value() const {
    if (_value) {
        if (ValueBox<T> * valueBox = dynamic_cast<ValueBox<T> *>(_value)){
            return valueBox->value();
        } else {
            throw wrong_type("name");
        }
    } else {
        throw value_not_set("name");
    }
}

template <class T>
        T &ConfigValue::value() {
    if (_value) {
        if (ValueBox<T> * valueBox = dynamic_cast<ValueBox<T> *>(_value)) {
            return valueBox->value();
        } else {
            throw wrong_type("name");
        }
    } else {
        _value = new ValueBox<T>();
        return static_cast<ValueBox<T> *>(_value)->value();
    }
}

#endif
