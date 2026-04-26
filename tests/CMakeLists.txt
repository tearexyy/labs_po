function(add_test_target name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE mylib)
    add_test(NAME ${name} COMMAND ${name}
             WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endfunction()

add_test_target(test_basefile test_basefile.cpp)
add_test_target(test_base32file test_base32file.cpp)
add_test_target(test_rlefile test_rlefile.cpp)
add_test_target(test_composition test_composition.cpp)
add_test_target(test_base32file2 test_base32file2.cpp)
add_test_target(test_rlefile2 test_rlefile2.cpp)