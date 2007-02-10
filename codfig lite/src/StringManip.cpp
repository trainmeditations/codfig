#include "StringManip.h"

void CodfigLite::StringManip::trim(std::string& s, char c)
{
	if (!s.empty())
	{
		std::string::size_type size = s.size();
		std::string::size_type start;
		for (start = 0; start < size; ++start)
		{
			if (s[start] != c)
				break;
		}

		std::string::size_type end;
		for (end = size - 1; end != 0; --end)
		{
			if (s[end] != c)
				break;
		}

		s = s.substr(start, end + 1);
	}
}

// Split string into left and right based on first delimeter
// returns true if found delim
bool CodfigLite::StringManip::splitFirst(const std::string& s, char delim, std::string& left, std::string& right)
{
	for (std::string::size_type i = 0; i < s.size(); ++i)
	{
		if (s[i] == delim)
		{
			left = s.substr(0, i - 1);
			right = s.substr(i + 1, s.size() - 1);
			return true;
		}
	}

	return false;
}
