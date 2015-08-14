include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckLibraryExists)

# Detect C++11 support and warn if (possibly) absent
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(FATAL_ERROR "Failed to detect C++11 mode for compiler ${CMAKE_CXX_COMPILER}")
endif()

# Determine if std::make_unique is supported
set(CMAKE_REQUIRED_FLAGS ${CMAKE_CXX_FLAGS})
check_cxx_source_compiles("#include <memory>\nclass C { };\nint main() { std::make_unique<C>(); }" HAVE_MAKE_UNIQUE)

# Detect Allegro
if(NOT DEFINED ELKULATOR_LINK_X11)
check_library_exists(alleg install_allegro "" HAVE_ALLEGRO)
if(NOT HAVE_ALLEGRO EQUAL 1)
  message(FATAL_ERROR "Must have Allegro installed")
endif()
endif()

# Detect alut
check_library_exists(alut alutInit "" HAVE_ALUT)
if(NOT HAVE_ALUT EQUAL 1)
  message(FATAL_ERROR "Must have alut installed")
endif()

# Detect libm
check_library_exists(m fmod "" HAVE_LIBM)
if(NOT HAVE_LIBM EQUAL 1)
  message(FATAL_ERROR "Must have libm installed")
endif()

# Detect OpenAL
check_library_exists(openal alGetError "" HAVE_OPENAL)
if(NOT HAVE_OPENAL EQUAL 1)
  message(FATAL_ERROR "Must have OpenAL installed")
endif()

# Detect zlib
check_library_exists(z gzopen "" HAVE_ZLIB)
if(NOT HAVE_ZLIB EQUAL 1)
  message(FATAL_ERROR "Must have zlib installed")
endif()

# Detect and configure CppUnit
include(${PROJECT_SOURCE_DIR}/cmake/cppunit.cmake)
