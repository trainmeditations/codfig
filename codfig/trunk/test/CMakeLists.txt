#Make sure the compiler can find include files from Codfig source directory
INCLUDE_DIRECTORIES(${CODFIG_SOURCE_DIR}/lib)

#Add binary called codfigTest that is built from the source file "test.cpp"
#The extension is automatically found
ADD_EXECUTABLE(codfigTest test.cpp tests.cpp tests.h)

#Link the executable to the Hello library
TARGET_LINK_LIBRARIES(codfigTest Codfig)

