set(TEST_SOURCE
    ${ZEUS_TEST_ROOT}/assert_test.cpp
    ${ZEUS_TEST_ROOT}/float_test.cpp
    ${ZEUS_TEST_ROOT}/platform_test.cpp
    ${ZEUS_TEST_ROOT}/timer_test.cpp
    ${ZEUS_TEST_ROOT}/filesystem_test.cpp
    ${ZEUS_TEST_ROOT}/compiler_test.cpp
    ${ZEUS_TEST_ROOT}/algorithm_test.cpp
    ${ZEUS_TEST_ROOT}/type_traits_test.cpp
    ${ZEUS_TEST_ROOT}/named_type_test.cpp
    ${ZEUS_TEST_ROOT}/enum_bitfield_test.cpp
    ${ZEUS_TEST_ROOT}/random_test.cpp
    ${ZEUS_TEST_ROOT}/string_test.cpp
    ${ZEUS_TEST_ROOT}/range_test.cpp
    ${ZEUS_TEST_ROOT}/concepts_test.cpp
    ${ZEUS_TEST_ROOT}/container_traits_test.cpp
    ${ZEUS_TEST_ROOT}/cxx_version_test.cpp
    ${ZEUS_TEST_ROOT}/linspace_test.cpp
    )

source_group("source" FILES ${TEST_SOURCE})
add_executable(zeus_test ${TEST_SOURCE})
target_link_libraries(zeus_test PRIVATE
    zeus
    Catch2::Catch2WithMain)
set_target_properties(zeus_test PROPERTIES FOLDER "zeus")

catch_discover_tests(zeus_test)
