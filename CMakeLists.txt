cmake_minimum_required(VERSION 3.10)

# GoogleTest requires at least C++11
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(Vector_t01 VERSION 0.1.0)

enable_testing()
#adding libs
add_library(Vec_training src/vec_training.cpp)
#adding executables
add_executable(Vector_t01 src/main.cpp)
#linking libs to executables
target_link_libraries(Vector_t01 Vec_training)
#gtest lib linking
target_link_libraries(Vector_t01 gtest_main)

target_include_directories(Vector_t01 PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_BINARY_DIR}/src"
                            )       

include(GoogleTest)
gtest_discover_tests(Vector_t01)