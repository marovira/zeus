set(ZEUS_TEST_FILES
    ${ZEUS_TEST_ROOT}/assert_test.cpp
    ${ZEUS_TEST_ROOT}/float_test.cpp
    ${ZEUS_TEST_ROOT}/functional_test.cpp
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
    )

set(ZEUS_TEST_GROUP ${ZEUS_TEST_FILES} PARENT_SCOPE)
set(ZEUS_TEST_LIST ${ZEUS_TEST_FILES} PARENT_SCOPE)
