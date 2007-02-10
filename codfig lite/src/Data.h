#ifndef _DATA_H_B858M8KM__
#define _DATA_H_B858M8KM__

#include <string>

namespace CodfigLite
{
	class Data
	{
	public:
		virtual ~Data()
		{
		}

	public:
		virtual const std::type_info& type() const = 0;

		virtual Data* clone() const = 0;

		virtual void fromString(const std::string& in) = 0;

		virtual std::string toString() const = 0;
	};
}

#endif //_DATA_H_B858M8KM__
