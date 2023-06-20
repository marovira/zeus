set(ZEUS_VERSION_HEADER
    ${ZEUS_SOURCE_ROOT}/zeus/zeus.hpp
    )
configure_file(${ZEUS_SOURCE_ROOT}/zeus/zeus.hpp.in ${ZEUS_VERSION_HEADER})

set(ZEUS_HEADER_LIST
    ${ZEUS_VERSION_HEADER}
    ${ZEUS_SOURCE_ROOT}/zeus/assert.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/float.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/functional.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/platform.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/timer.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/filesystem.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/compiler.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/algorithm.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/crtp.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/type_traits.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/named_type.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/enum_bitfield.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/concepts.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/random.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/string.hpp
    ${ZEUS_SOURCE_ROOT}/zeus/range.hpp
    )

# Wrap each list for the source groups above.
set(ZEUS_INCLUDE_GROUP ${ZEUS_HEADER_LIST} PARENT_SCOPE)

# Now compile the full list of files so we can format everything at once.
set(ZEUS_HEADER_FILES
    ${ZEUS_HEADER_LIST}
    PARENT_SCOPE)
