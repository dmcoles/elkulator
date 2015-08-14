cmake_minimum_required(VERSION 2.8)
project(elkulator C CXX)
set(ELKULATOR_VERSION_MAJOR 1)
set(ELKULATOR_VERSION_MINOR 1)

enable_testing()

include(${PROJECT_SOURCE_DIR}/cmake/checks.cmake)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUGMODE")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fomit-frame-pointer")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -falign-loops")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -falign-jumps")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -falign-functions")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-unused-result")

configure_file(
  ${PROJECT_SOURCE_DIR}/elkulator-config.h.in
  ${PROJECT_BINARY_DIR}/elkulator-config.h
)
configure_file(
  ${PROJECT_SOURCE_DIR}/elkulator-common.h.in
  ${PROJECT_BINARY_DIR}/elkulator-common.h
)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(TEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/test)
include(${PROJECT_SOURCE_DIR}/sources.cmake)
include(${PROJECT_SOURCE_DIR}/libs.cmake)

include_directories(
  ${PROJECT_BINARY_DIR}
  ${SOURCE_DIR}
  ${CPPUNIT_INCLUDE_DIRS}
)

add_library(elkulator-objs OBJECT
  ${OBJ_SOURCE_FILES}
  ${PLATFORM_OBJ_SOURCE_FILES}
)

add_library(elkulator-test-objs OBJECT
  ${TEST_OBJ_SOURCE_FILES}
  ${PLATFORM_TEST_OBJ_SOURCE_FILES}
)

add_executable(elkulator WIN32
  $<TARGET_OBJECTS:elkulator-objs>
  ${BIN_SOURCE_FILES}
)
target_link_libraries(elkulator
  ${THIRD_PARTY_LIBS}
  ${PLATFORM_THIRD_PARTY_LIBS}
)

add_executable(elkulator-test
  $<TARGET_OBJECTS:elkulator-objs>
  $<TARGET_OBJECTS:elkulator-test-objs>
  ${TEST_BIN_SOURCE_FILES}
)
target_link_libraries(elkulator-test
  ${THIRD_PARTY_LIBS}
  ${PLATFORM_THIRD_PARTY_LIBS}
)

add_test(NAME elkulator-test COMMAND elkulator-test)

install(TARGETS elkulator DESTINATION bin)

