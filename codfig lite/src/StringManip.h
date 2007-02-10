#ifndef _STRINGMANIP_H_HS73K823KM_
#define _STRINGMANIP_H_HS73K823KM_

#include <string>

namespace CodfigLite
{
	namespace StringManip
	{
		void trim(std::string& s, char c = ' ');

		// Split string into left and right based on first delimeter
		// returns true if found delim
		bool splitFirst(const std::string& s, char delim, std::string& left, std::string& right);
	}
}
#endif //_STRINGMANIP_H_HS73K823KM_