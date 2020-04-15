set(ZEUS_VERSION_HEADER
    ${ZEUS_SOURCE_ROOT}/zeus/zeus.hpp
    )
configure_file(${ZEUS_SOURCE_ROOT}/zeus/zeus.hpp.in ${ZEUS_VERSION_HEADER})

set(ZEUS_HEADER_LIST
    ${ZEUS_VERSION_HEADER}
    )

# Wrap each list for the source groups above.
set(ZEUS_INCLUDE_GROUP ${ZEUS_HEADER_LIST} PARENT_SCOPE)

# Now compile the full list of files so we can format everything at once.
set(ZEUS_HEADER_FILES
    ${ZEUS_HEADER_LIST}
    PARENT_SCOPE)
