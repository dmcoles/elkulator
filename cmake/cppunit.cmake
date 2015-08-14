# Finds and configures CppUnit includes and library
#
# This module defines the following variables:
# CPPUNIT_INCLUDE_DIRS: location of include files
# CPPUNIT_LIBRARIES:    location of libraries
# CPPUNIT_FOUND:        true if CppUnit detected, false otherwise
#
# Based on:
# http://gnuradio.org/redmine/projects/gnuradio/repository/revisions/accb9f2fe8fd8f6a1e114adac5b15304b0e0012d/entry/cmake/Modules/FindCppUnit.cmake
# http://www.cmake.org/pipermail/cmake/2006-October/011446.html

if(NOT WIN32)
  include(FindPkgConfig)
  pkg_check_modules(CPPUNIT "cppunit")
endif()

if(NOT CPPUNIT_FOUND)
  find_path(CPPUNIT_INCLUDE_DIRS cppunit/TestCase.h
    /usr/local/include
    /usr/include)

  find_library(CPPUNIT_LIBRARIES cppunit
    ${CPPUNIT_INCLUDE_DIRS}/../lib
    /usr/local/lib
    /usr/lib)

  if(CPPUNIT_INCLUDE_DIRS)
    if(CPPUNIT_LIBRARIES)
      set(CPPUNIT_FOUND "YES")
      set(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARIES} ${CMAKE_DL_LIBS})
    endif()
  endif()

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(CPPUNIT
    DEFAULT_MSG
    CPPUNIT_LIBRARIES
    CPPUNIT_INCLUDE_DIRS)
endif()
