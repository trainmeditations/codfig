cmake_minimum_required(VERSION 3.5.2 FATAL_ERROR)
project (Codfig)

option (BUILD_INI "Build support for INI files" ON)
option (BUILD_TEST "Build test binary" ON)
#option (BUILD_XML "Build support for XML files" OFF)
#option (BUILD_YAML "Build support for YAML files" OFF)
option (BUILD_SHARED_LIBS "Build Codfig as a shared library" OFF)
option (GOOGLE_TESTS "Enable GoogleTest unit tests" ON)

add_subdirectory (lib)

if (BUILD_INI)
	add_subdirectory (iniIO)
endif (BUILD_INI)

#add_subdirectory (xmlIO)
#add_subdirectory (yamlIO)

if (BUILD_TEST)
	add_subdirectory (test)
endif (BUILD_TEST)

if (GOOGLE_TESTS)
    add_subdirectory (googletest EXCLUDE_FROM_ALL)
    set (INSTALL_GTEST off)
    set (BUILD_GMOCK off)
    enable_testing ()
    add_subdirectory (gtest)
endif (GOOGLE_TESTS)
