INCLUDE_DIRECTORIES(${Codfig_SOURCE_DIR}/lib)
add_library( CodfigINI codfigio_ini.hpp codfigio_ini.cpp )
target_link_libraries(CodfigINI CodfigFileIO)
