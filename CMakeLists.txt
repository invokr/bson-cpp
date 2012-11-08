#------------------------------
# Standard CMake Stuff
#------------------------------

cmake_minimum_required (VERSION 2.8)
project (bson)

# ------------------------------
# Display some information
# ------------------------------

message(STATUS "Source DIR is ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary DIR is ${PROJECT_BINARY_DIR}")
message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")
message(STATUS "Libs extension is '${SUFFIXLIB}'. Bins extension is '${SUFFIXBIN}'." )
message(STATUS "Installation prefix directory is " ${CMAKE_INSTALL_PREFIX})
message(STATUS "Host system is " ${CMAKE_HOST_SYSTEM} " with processor " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "Target system is " ${CMAKE_SYSTEM} " with processor " ${CMAKE_SYSTEM_PROCESSOR})

#------------------------------
# Path Setup
#------------------------------

SET ( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake )
SET ( INSTALL_DIR ${CMAKE_SOURCE_DIR}/dist/ )

SET ( EXECUTABLE_OUTPUT_PATH ${INSTALL_DIR}/bin )
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR}/lib )

#------------------------------
# Compiler Setup
#------------------------------

SET ( CMAKE_CXX_FLAGS                "-fno-omit-frame-pointer -fPIC -Wall" )
SET ( CMAKE_CXX_FLAGS_DEBUG          "-g" )
SET ( CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG" )
SET ( CMAKE_CXX_FLAGS_RELEASE        "-O2 -DNDEBUG" )
SET ( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g" )

#------------------------------
# Include And Configure Libraries
#------------------------------

find_package (Boost COMPONENTS system REQUIRED)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${CMAKE_SOURCE_DIR}/dist/lib
)

include_directories (
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/
)

#------------------------------
# Add Source Directory
#------------------------------

add_subdirectory (src)
