#ifndef __EXCEPTIONS_H_INCLUDED__DY62077_
#define __EXCEPTIONS_H_INCLUDED__DY62077_

namespace CodfigLite
{
	class codfiglite_exception { };
	
	class io_error : public codfiglite_exception { };

	class bad_type : public codfiglite_exception { };

	class key_exists : public codfiglite_exception { };

	class key_does_not_exist : public codfiglite_exception { };

	class file_format_error : public codfiglite_exception { };
}
#endif