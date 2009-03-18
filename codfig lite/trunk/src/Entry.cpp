#include "Entry.h"
#include "StringManip.h"
#include <cctype>

CodfigLite::Entry::Entry()
: _needToLoad(false), _data(new DataType<int>(-1))
{
}

CodfigLite::Entry::~Entry()
{
	delete _data;
}

CodfigLite::Entry::Entry(const Entry& other)
: _needToLoad(false), _data(new DataType<int>(-1))
{
	*this = other;
}

CodfigLite::Entry& CodfigLite::Entry::operator=(const Entry& other)
{
	if (this != &other)
	{
		_needToLoad = other._needToLoad;
		_value = other._value;
		delete _data;
		_data = other._data->clone();
		_comments = other._comments;
	}

	return *this;
}


/////////////////////////////////////////////
//// comments related functions

void CodfigLite::Entry::saveComments(std::ofstream& out) const
{
	for (std::vector<std::string>::const_iterator it = _comments.begin(); it != _comments.end(); ++it)
		out << COMMENT_LINE << *it << std::endl;
}

void CodfigLite::Entry::loadComments(std::ifstream& in)
{
	// work out if this is a comment line
	_comments.clear();
	std::string line;
	for ( ; ; )
	{
		if (!isCommentLine(in))
			return;

		getline(in, line);
		if (in.fail())
			throw file_format_error();

		_comments.push_back(line);
	}
}

/**
 * if return = true, leading COMMENT_LINE character is removed
 */
bool CodfigLite::Entry::isCommentLine(std::ifstream& in)
{
	for ( ; ; )
	{
		char ch = in.get();
		if (in.fail())
			return false;
		else if (isspace(ch))
			continue;
		else if (ch == COMMENT_LINE)
			return true;
		else
		{
			in.putback(ch);
			return false;
		}
	}
}		

void CodfigLite::Entry::addComment(const std::string& comment)
{
	_comments.push_back(comment);
}

const std::vector<std::string>& CodfigLite::Entry::getComments() const
{
	return _comments;
}

void CodfigLite::Entry::clearComments()
{
	_comments.clear();
}


/////////////////////////////////////////////
//// data related functions

void CodfigLite::Entry::saveValue(std::ofstream& out) const
{
	if (_needToLoad)
	{
		out << _value << std::endl;
	}
	else
	{
		out << _data->toString() << std::endl;
	}
}


void CodfigLite::Entry::loadValue(std::ifstream& in)
{
	getline(in, _value);
	if (in.fail())
	{
		_value = "";
		throw file_format_error();
	}
	_needToLoad = true;
}
