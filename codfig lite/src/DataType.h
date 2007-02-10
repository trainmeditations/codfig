#ifndef _DATATYPE_H_L56720UXZ__
#define _DATATYPE_H_L56720UXZ__

#include <string>
#include <sstream>

#include "Data.h"
#include "Exceptions.h"

namespace CodfigLite
{
	template <typename T>
	class DataType : public Data
	{
	public:
		DataType(const T& value)
			: _data(value)
		{
		}

		DataType(std::string& value)
		{
			fromString(value);
		}

		virtual const std::type_info & type() const
		{
			return typeid(T);
		}

		virtual Data* clone() const
		{
			return new DataType(_data);
		}

		virtual void fromString(std::string& in)
		{
			std::stringstream ss(in);
			ss >> _data;
			if (ss.fail())
				throw io_error();
		}

		virtual std::string toString() const
		{
			std::stringstream ss;
			ss << _data;
			return ss.str();
		}

		T _data;
	};

	template <>
	class DataType<std::string> : public Data
	{
	public:
		DataType(const std::string& value)
			: _data(value)
		{
		}

		virtual const std::type_info & type() const
		{
			return typeid(std::string);
		}

		virtual Data* clone() const
		{
			return new DataType(_data);
		}

		virtual void fromString(std::string& in)
		{
			_data = in;
		}

		virtual std::string toString() const
		{
			return _data;
		}

		std::string _data;
	};
}

#endif //_DATATYPE_H_L56720UXZ__