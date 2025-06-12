#ifndef NEWCMAKEPROJECTCONSTANTS_H
#define NEWCMAKEPROJECTCONSTANTS_H
#include <QString>

namespace newProjectConstants
{
const QString rootCmakeListsContents{R"(
cmake_minimum_required(VERSION 3.14)
project(ProiectCMake)

set(CMAKE_CXX_STANDARD 17)

# Enable testing
include(CTest)
enable_testing()

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add components
add_subdirectory(Component1)

)"};

const QString Component1CmakeListsContents{R"(
# Add source files
add_library(Component1
src/exampleSource.cpp #add source files here
include/Component1/ExampleHeader.hpp #add include files here
)
# Include directories
target_include_directories(Component1 PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE Component1)

# Add tests
add_subdirectory(tests)

)"};

const QString testsCmakeListsContents{R"(
# Create test executable
add_executable(Component1_test Example_test.cpp)

# Link to GTest and the component
target_link_libraries(Component1_test
    GTest::gtest_main
    Component1
)

include(GoogleTest)
gtest_discover_tests(Component1_test)
)"};

const QString headerFileContents{R"(
/***********************************************/
/* Delete file contents and start programming! */
/***********************************************/
int sum(int a, int b);
int sub(int a, int b);
)"};

const QString sourceFileContents{R"(
/***********************************************/
/* Delete file contents and start programming! */
/***********************************************/

#include "Component1/ExampleHeader.hpp"

int sum(int a, int b)
{
    return a + b;
}
int sub(int a, int b)
{
    return a - b;
}
)"};

const QString mainFileContents{R"(
/***********************************************/
/* Delete file contents and start programming! */
/***********************************************/
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
    return 0;
}
)"};

const QString testFileContents{R"(
#include <gtest/gtest.h>
/***********************************************/
/* Delete file contents and start programming! */
/***********************************************/

#include "Component1/ExampleHeader.hpp"
TEST(ExampleSuite, exampleOne) {
    EXPECT_EQ(1, 1);
}

TEST(ExampleSuite, exampleTwo) {
    EXPECT_EQ(sum(1,2), 3);
}

TEST(ExampleSuite, exampleThree) {
    EXPECT_EQ(1, sub(3,2));
}

TEST(ExampleSuite, exampleFour) {
    EXPECT_EQ(sum(1,2), sub(9,6));
}

)"};
}
#endif // NEWCMAKEPROJECTCONSTANTS_H
