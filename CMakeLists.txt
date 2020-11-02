# Minimum CMake version needed when using hpc-coding-conventions cmake tools
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(cpp_example_project LANGUAGES CXX VERSION 1.0.0)

# --------------------------------------------------------------------------------
# Add hpc-coding-conventions tooling
# --------------------------------------------------------------------------------
# FORMATTING
# Enable clang code formatting
set(${PROJECT_NAME}_CLANG_FORMAT ON
    CACHE BOOL "Enable helpers to keep CMake and C++ code properly formatted"
    FORCE)
# Specify where to apply the formatting (in this case, everywhere but submodules)
set(${PROJECT_NAME}_FORMATTING_ON "all"
    CACHE STRING "Specify changeset where formatting applies (see documentation for detailed information)"
    FORCE)

# STATIC CODE ANALYSIS
# Enable static code analysis in production and test code
set(${PROJECT_NAME}_STATIC_ANALYSIS ON
    CACHE BOOL "Enable C++ static analysis during compilation"
    FORCE)
set(${PROJECT_NAME}_TEST_STATIC_ANALYSIS ON
    CACHE BOOL "Add CTest static analysis test"
    FORCE)

add_subdirectory(hpc-coding-conventions/cpp)
# --------------------------------------------------------------------------------

# Initial configuration provided by hpc-coding-conventions
# Package opening
bob_begin_package()

# C++ flags opening
bob_begin_cxx_flags()

bob_cxx14_flags()

# C++ flogs closing
bob_end_cxx_flags()

set(CPPEXAMPLE_LIB_HEADERS
    include/cpp_example_lib/types.h
    include/cpp_example_lib/operations.h
)

set(CPPEXAMPLE_LIB_SOURCES
    src/operations.cpp
)

# Generate the library
add_library(cppexample_shared SHARED ${CPPEXAMPLE_LIB_HEADERS} ${CPPEXAMPLE_LIB_SOURCES})

target_include_directories(cppexample_shared PUBLIC
                            "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
                            "$<INSTALL_INTERFACE:include>")

set_target_properties(cppexample_shared
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# Install it
# Export target
install(TARGETS cppexample_shared
    EXPORT cppexample_shared-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")


# Compile applications
add_subdirectory(apps)

# Package closing
bob_end_package()
