add_library(mylib STATIC
    BaseFile.cpp
    mystring.cpp
)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})