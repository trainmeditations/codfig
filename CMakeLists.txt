cmake_minimum_required(VERSION 3.5.2 FATAL_ERROR)
if (POLICY CMP0115)
	cmake_policy(SET CMP0115 NEW)
endif()
project (Codfig)

option (BUILD_INI "Build support for INI files" ON)
option (BUILD_TEST "Build test binary" ON)
#option (BUILD_XML "Build support for XML files" OFF)
#option (BUILD_YAML "Build support for YAML files" OFF)
option (BUILD_SHARED_LIBS "Build Codfig as a shared library" OFF)

add_subdirectory (lib)

if (BUILD_INI)
	add_subdirectory (iniIO)
endif (BUILD_INI)

#add_subdirectory (xmlIO)
#add_subdirectory (yamlIO)

if (BUILD_TEST)
	add_subdirectory (test)
endif (BUILD_TEST)
