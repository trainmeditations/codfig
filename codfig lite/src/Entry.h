#ifndef __ENTRY_H_INCLUDED__765DHN7373JW8710_
#define __ENTRY_H_INCLUDED__765DHN7373JW8710_

#include <vector>
#include <string>
#include <fstream>

namespace CodfigLite
{
	class Data;

	class Entry
	{
	public:
		Entry();

		~Entry();

		Entry(const Entry& other);

		Entry& operator=(const Entry& other);

		template <typename T>
		Entry(const T& value);

		// comments related functions
		void saveComments(std::ofstream& out) const;
		void loadComments(std::ifstream& in);
		void addComment(const std::string& comment);
		const std::vector<std::string>& getComments() const;
		void clearComments();

		// data related functions
		void saveValue(std::ofstream& out) const;
		void loadValue(std::ifstream& in);
		template <typename T>
		void setValue(const T& value);
		template <typename T>
		T& getValue() const;

	private:
		bool isCommentLine(std::ifstream& in);

		static const char COMMENT_LINE = '#';

		// does this entry still need to be loaded from _value?
		bool _needToLoad;

		// if _needToLoad then _value is the string representation of the config option data
		std::string _value;

		// data for this config option
		Data* _data;

		// comments for this config option
		std::vector<std::string> _comments;
	};
}

#include "Exceptions.h"
#include "DataType.h"

template <typename T>
CodfigLite::Entry::Entry(const T& value)
: _needToLoad(false), _data(new DataType<T>(value))
{
}

template <typename T>
void  CodfigLite::Entry::setValue(const T& value)
{
	delete _data;
	_data = new DataType<T>(value);
}

template <typename T>
T& CodfigLite::Entry::getValue() const
{
	if (_needToLoad)
	{
		delete _data;
		Data** oldData = (Data**)&_data;
		*oldData = new DataType<T>(_value);
	}
	else
	{
		if (_data->type() != typeid(T))
			throw bad_type();
	}

	return static_cast<DataType<T>*>(_data)->_data;
}


#endif // __ENTRY_H_INCLUDED__765DHN7373JW8710_
