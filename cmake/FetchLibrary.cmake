function(fetch_library)
    set(options)
    set(oneValueArgs NAME GIT_REPOSITORY GIT_TAG)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    include(FetchContent)
    FetchContent_Declare(${ARG_NAME} 
        GIT_REPOSITORY ${ARG_GIT_REPOSITORY} 
        GIT_TAG ${ARG_GIT_TAG}
        )
    FetchContent_MakeAvailable(${ARG_NAME})
endfunction()
