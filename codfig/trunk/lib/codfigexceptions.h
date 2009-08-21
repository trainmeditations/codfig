// File: codfigexceptions.h
// Decleration of exception classes
// Copyright (C) Shaun Bouckaert

#ifndef TRAINMEDITATIONS_CODFIGEXCEPTIONS_H
#define TRAINMEDITATIONS_CODFIGEXCEPTIONS_H

#include <stdexcept>

namespace codfig {

	class bad_path: public std::runtime_error {
		public:
			explicit bad_path(const std::string &path):std::runtime_error("Bad path to section: " + path){}
	};

	class wrong_type: public std::logic_error {
		public:
			explicit wrong_type(const std::string &name):std::logic_error("Wrong type for value " + name + "."){}
	};

	class value_not_set: public std::runtime_error {
		public:
			explicit value_not_set(const std::string &name):std::runtime_error("Value not set for value " + name + "."){}
	};

	class duplicate_name: public std::runtime_error {
		public:
			explicit duplicate_name(const std::string &type, const std::string &name):std::runtime_error("A " + type + " named " + name + " already exists."){}
	};
}

#endif
