// File: codfigmodel.h
// model of configuration data
// Copyright (C) Shaun Bouckaert

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
			const string &getApplicationName() const;
			const string &getApplicationVersion() const;
			const string &getDeveloper() const;
		private:
			string appName;
			string appVer;
			string developer;
	};

	class ConfigValue {
		private:
			class AbstractValueBox {
				public:
					virtual AbstractValueBox * clone() = 0;
			};

			template <class T>
			class ValueBox:public AbstractValueBox {
				public:
					ValueBox(T value);
					ValueBox<T> * clone();
					const T &getValue() const;
					void setValue(const T &newValue);
					string getStringValue() const;
					void setValueByString(const string &stringValue);
				private:
					T storedValue;
			};

		public:
			ConfigValue();
			ConfigValue(const ConfigValue &);
			~ConfigValue();
			template <class T>
				const T &getValue() const;
			template <class T>
				void setValue(const T &newValue);
		private:
			AbstractValueBox * value;
	};

	class ConfigSection;

	class SectionContainer { //should this protected inherit from vector<ConfigSection *> ?
		public:
			SectionContainer();
			SectionContainer(const SectionContainer &);
			virtual ~SectionContainer();
			void addSection(const string &name);
			void removeSection(const string &name);
			ConfigSection & getSection(const string &name);
			const vector<string> getSectionNames() const;
		private:
			map<string, ConfigSection *> subSections;
	};

	class ConfigSection:public SectionContainer {
		public:
			ConfigSection();
			ConfigSection(const ConfigSection &);
			~ConfigSection();
			const vector<string> getValueNames() const;
			ConfigValue & value(const string &name);
		private:
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
