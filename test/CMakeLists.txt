set(TARGET_NAME unit_tests)
add_executable( 
	${TARGET_NAME}
    example_add.cpp
    example_subtract.cpp
)

target_link_libraries( 
	${TARGET_NAME}
    gtest_main
)

add_test(
  NAME
    test
  COMMAND
    ${TARGET_NAME}
)
