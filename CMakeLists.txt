cmake_minimum_required (VERSION 3.2)
 
set(PostgreSQL_ADDITIONAL_VERSIONS 16)

project(Lesson07)

add_subdirectory(libpqxx)

add_executable(Lesson07 main.cpp ClientManager.cpp ClientManager.h)

target_compile_features(Lesson07 PRIVATE cxx_std_17)

target_link_libraries(Lesson07 PRIVATE pqxx)

