cmake_minimum_required(VERSION 3.16)
project(CXXCirculaBuffer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_DEBUG "Enable Debug Mode" ON)

if(ENABLE_DEBUG)
  message(STATUS "Building in Debug Mode")
  add_definitions(-DDEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
else()
  message(STATUS "Building in Release Mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

option(ENABLE_TEST "Enable Test" ON)

if(ENABLE_TEST)
  # GoogleTest setup
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)


  enable_testing()
  file (GLOB_RECURSE TEST_FILES "tests/*.cpp")
  
  add_executable(tests ${TEST_FILES})
    target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_link_libraries(tests PRIVATE gtest_main)

  include(GoogleTest)
  gtest_discover_tests(tests)

endif()


option(ENABLE_EXAMPLE "Enable Example" ON)

if(ENABLE_EXAMPLE)
  add_executable(circular_buffer examples/circular_buffer.cpp)
  target_include_directories(circular_buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  
endif()

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

if(ENABLE_COVERAGE)
  message(STATUS "Building with coverage flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()
