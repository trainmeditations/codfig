#Make sure the compiler can find include files from Codfig source directory
INCLUDE_DIRECTORIES(${CODFIG_SOURCE_DIR}/src)

#Add binary called codfigTest that is built from the source file "test.cpp"
#The extension is automatically found
ADD_EXECUTABLE(codfigTest test)

#Link the executable to the Hello library
TARGET_LINK_LIBRARIES(codfigTest Codfig)

