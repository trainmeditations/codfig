// File: codfigmodel_t.h
// codfig model template definitions
// Copyright (C) Shaun Bouckaert

#ifndef TRAINMEDITATION_CODFIGMODEL_T_H
#define TRAINMEDITATION_CODFIGMODEL_T_H

#include "codfigmodel.h"
#include "codfigexceptions.h"
#include <sstream>

using namespace codfig;
using std::ostringstream;
using std::istringstream;

template <class T>
ConfigValue::ValueBox<T>::ValueBox(T value):storedValue(value){}

template <class T>
ConfigValue::ValueBox<T>::~ValueBox(){}

template <class T>
ConfigValue::ValueBox<T> * ConfigValue::ValueBox<T>::cloneValue() const {
    return new ValueBox<T>(*this);
}

template <class T>
const T &ConfigValue::ValueBox<T>::getValue() const {
	return storedValue;
}

template <class T>
void ConfigValue::ValueBox<T>::setValue(const T &newValue) {
	storedValue = newValue;
}

template <class T>
string ConfigValue::ValueBox<T>::getStringValue() const {
	ostringstream outstring();
	outstring << storedValue;
	return outstring.str();
}

template <class T>
void ConfigValue::ValueBox<T>::setValueByString(const std::string &stringValue) {
	istringstream instream(stringValue);
	instream >> storedValue;
}

template <class T>
const T &ConfigValue::getValue() const {
	if (value) {
		if (ValueBox<T> * valueBox = dynamic_cast<ValueBox<T> *>(value)){
			return valueBox->getValue();
		} else {
			throw wrong_type("name");
		}
	} else {
		throw value_not_set("name");
	}
}

template <class T>
void ConfigValue::setValue(const T &newValue){
	if (value) {
		if (ValueBox<T> * valueBox = dynamic_cast<ValueBox<T> *>(value)){
			valueBox->setValue(newValue);
		} else {
			throw wrong_type("name");
		}
	} else {
		value = new ValueBox<T>(newValue);
	}
}

#endif
