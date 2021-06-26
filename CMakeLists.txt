cmake_minimum_required(VERSION 3.15)

project(${CMAKE_PROJECT_NAME}Road)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(SRC 
    ${PROJECT_SOURCE_DIR}/src/Graph.cpp
    ${PROJECT_SOURCE_DIR}/src/Model.cpp
    ${PROJECT_SOURCE_DIR}/src/Resolve.cpp
)

add_library(Road
    ${SRC}
)

link_libraries(Road)

add_executable(run ${PROJECT_SOURCE_DIR}/main.cpp)

set(test_sources 
  ${PROJECT_SOURCE_DIR}/test/src/tmp_test.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${test_sources})

if (${CMAKE_PROJECT_NAME}_ENABLE_CODE_COVERAGE)
  target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -fprofile-arcs -ftest-coverage)
  verbose_message("Code coverage is enabled and provided with GCC.")
endif()

if(${CMAKE_PROJECT_NAME}_BUILD_EXECUTABLE)
	set(${CMAKE_PROJECT_NAME}_TEST_LIB ${CMAKE_PROJECT_NAME}_LIB)
else()
	set(${CMAKE_PROJECT_NAME}_TEST_LIB ${CMAKE_PROJECT_NAME})
endif()

if(${CMAKE_PROJECT_NAME}_USE_GTEST)
  find_package(GTest REQUIRED)

  if(${CMAKE_PROJECT_NAME}_USE_GOOGLE_MOCK)
		set(GOOGLE_MOCK_LIBRARIES GTest::gmock GTest::gmock_main)
  endif()

  target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
      GTest::GTest
      GTest::Main
      ${GOOGLE_MOCK_LIBRARIES}
      ${${CMAKE_PROJECT_NAME}_TEST_LIB}
  )
elseif(${CMAKE_PROJECT_NAME}_USE_CATCH2)
  find_package(Catch2 REQUIRED)
  target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
      Catch2::Catch2
      ${${CMAKE_PROJECT_NAME}_TEST_LIB}
  )
endif()

add_test(
  NAME
    ${PROJECT_NAME}
  COMMAND
    ${PROJECT_NAME}
)