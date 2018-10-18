find_package(CppUnit REQUIRED)
include_directories(${CPPUNIT_INCLUDE_DIR})
LIST(APPEND UnitTestLibs ${CPPUNIT_LIBRARY})

#Include the "unit-tests" directory 
include_directories("unit-tests")

#Add all unit tests in addition to all source files.
add_executable(UnitTests unit-tests/utest.cpp ${SRCS})

#Link this executable.
target_link_libraries (UnitTests ${LibraryList} ${UnitTestLibs})
