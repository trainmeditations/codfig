#ifndef _CodfigLite_H_NJ78555_
#define _CodfigLite_H_NJ78555_

#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Entry.h"

namespace CodfigLite
{
	class Config
	{
	public:
		~Config();

		// data related functions
		template <typename T>
		void add(const std::string& key, const T& value);
		template <typename T>
		T& get(const std::string& key) const;

		// comments related functions
		void addComment(const std::string& key, const std::vector<std::string>& lines);
		void addComment(const std::string& key, const std::string& line);
		const std::vector<std::string>& getComments(const std::string& key) const;
		void clearComments(const std::string& key);

		// serialization
		void save(std::ofstream& out) const;
		void load(std::ifstream& in);

	private:
		Entry& getKeyExists(const std::string& key);
		const Entry& getKeyExists(const std::string& key) const;

		static const char ASSIGNMENT_OPERATOR = '=';

		// both containers point to the same entries
		std::map<const std::string, Entry> _config;
	};
}

#include "Exceptions.h"

template <typename T>
void CodfigLite::Config::add(const std::string& key, const T& value)
{
	std::map<const std::string, Entry>::iterator itFind = _config.find(key);
	if (itFind != _config.end())
		throw key_exists();

	_config[key] = Entry(value);
}

template <typename T>
T& CodfigLite::Config::get(const std::string& key) const
{
	const Entry& entry = getKeyExists(key);
	return entry.getValue<T>();
}

#endif //_CHRISFIG_H_NJ78555_
