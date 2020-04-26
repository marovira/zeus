if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.8.0)
    include(CMakeFindDependencyMacro)
    find_dependency(fmt REQUIRED)
    find_dependency(magic_enum REQUIRED)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/zeusTargets.cmake)
