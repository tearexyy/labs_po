cmake_minimum_required(VERSION 3.15)
project(Lab2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека из всех реализаций
add_subdirectory(src)

# Исполняемый файл
add_executable(lab2 src/lab2.cpp)
target_link_libraries(lab2 PRIVATE mylib)

# Тесты
enable_testing()
add_subdirectory(tests)