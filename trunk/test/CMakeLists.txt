#Make sure the compiler can find include files from Codfig source directory
IF (BUILD_INI)
	SET (OPT_INCS ${OPT_INCS} "${Codfig_SOURCE_DIR}/iniIO")
	SET (OPT_LIBS ${OPT_LIBS} CodfigINI)
	SET (Test_INI "true")
ELSE (BUILD_INI)
	SET (Test_INI "false")
ENDIF (BUILD_INI)

SET (OPT_INCS ${OPT_INCS} "${Codfig_BINARY_DIR}/test")
CONFIGURE_FILE (
	"${Codfig_SOURCE_DIR}/test/buildopts.h.in"
	"${Codfig_BINARY_DIR}/test/buildopts.h"
)

INCLUDE_DIRECTORIES("${Codfig_SOURCE_DIR}/lib" ${OPT_INCS})

#Add binary called codfigTest that is built from the source file "test.cpp"
#The extension is automatically found
ADD_EXECUTABLE(codfigTest test.cpp tests.cpp tests.h buildopts.h)

#Link the executable to the Codfig and other optional libraries
TARGET_LINK_LIBRARIES(codfigTest Codfig ${OPT_LIBS})

