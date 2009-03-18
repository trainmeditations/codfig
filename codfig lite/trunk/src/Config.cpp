#include "Config.h"
#include "StringManip.h"

CodfigLite::Config::~Config()
{
}

void CodfigLite::Config::addComment(const std::string& key, const std::vector<std::string>& lines)
{
	Entry& entry = getKeyExists(key);
	for (std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
		entry.addComment(*it);
}

void CodfigLite::Config::addComment(const std::string& key, const std::string& line)
{
	getKeyExists(key).addComment(line);
}

const std::vector<std::string>& CodfigLite::Config::getComments(const std::string& key) const
{
	return getKeyExists(key).getComments();
}

void CodfigLite::Config::clearComments(const std::string& key)
{
	getKeyExists(key).clearComments();
}

void CodfigLite::Config::save(std::ofstream& out) const
{
	for (std::map<const std::string, Entry>::const_iterator it = _config.begin(); it != _config.end(); ++it)
	{
		out << std::endl;
		it->second.saveComments(out);
		out << it->first << ASSIGNMENT_OPERATOR; 
		it->second.saveValue(out);
	}
}

void CodfigLite::Config::load(std::ifstream& in)
{
	Entry entry;
	std::string key;
	for ( ; ; )
	{
		entry.loadComments(in);
		if (in.fail())
			break;

		getline(in, key, ASSIGNMENT_OPERATOR);
		if (in.fail())
			break;

		entry.loadValue(in);
		if (in.fail())
			break;

		_config[key] = entry;
	}
}

CodfigLite::Entry& CodfigLite::Config::getKeyExists(const std::string& key)
{
	std::map<const std::string, Entry>::iterator itFind = _config.find(key);
	if (itFind == _config.end())
		throw key_does_not_exist();

	return itFind->second;
}

const CodfigLite::Entry& CodfigLite::Config::getKeyExists(const std::string& key) const
{
	std::map<const std::string, Entry>::const_iterator itFind = _config.find(key);
	if (itFind == _config.end())
		throw key_does_not_exist();

	return itFind->second;
}
