cmake_minimum_required(VERSION 2.7)
project(SeetaAuthorize)
# global root dir
set(SOLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DORZ_SOLUTION_DIR="${SOLUTION_DIR}")

# dir for common cmake files
list(APPEND CMAKE_MODULE_PATH ${SOLUTION_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${SOLUTION_DIR}/cmake)

# option for platform
set(PLATFORM "x64" CACHE STRING "auto, x86 or x64")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Debug or Release")

set(CONFIGURATION ${CMAKE_BUILD_TYPE})

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)
# set common compiler flags
include(LOCAL_FLAGS)
include(LOCAL_ENV)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/build CACHE STRING "set install prefix")
install(CODE "MESSAGE(\"Installing into ${CMAKE_INSTALL_PREFIX}\")")

set(LOCAL_OUTPUT_DIR ${PROJECT_BINARY_DIR})

if (LOCAL_OUTPUT_DIR)
    set(EXECUTABLE_OUTPUT_PATH ${LOCAL_OUTPUT_DIR}/${ENV_RUNTIME_DIR})
    set(LIBRARY_OUTPUT_PATH ${LOCAL_OUTPUT_DIR}/${ENV_LIBRARY_DIR})
endif ()

FILE(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

FILE(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

FILE(GLOB_RECURSE SRC_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# For debug libs and exes, add "_d" postfix
if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX "_d")
endif()

add_library(${PROJECT_NAME} ${INCLUDE_FILES} ${SRC_INCLUDE_FILES} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${ENV_SUFFIX})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${SOLUTION_DIR}/include>
    $<BUILD_INTERFACE:${SOLUTION_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOLUTION_DIR}/include/hidden
    ${SOLUTION_DIR}/include/lock)

message(STATUS "Build with ORZ")
if(TARGET ORZ)
    target_link_libraries(${PROJECT_NAME} ORZ)
else()
    find_package(ORZ REQUIRED)
    target_link_libraries(${PROJECT_NAME} SeetaFace6::ORZ)
endif()

export(TARGETS ${PROJECT_NAME}
    APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    )

string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
GENERATE_EXPORT_HEADER(${PROJECT_NAME})
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h" # Install head files
    )

install(TARGETS
    ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Target
    RUNTIME DESTINATION ${ENV_RUNTIME_DIR}
        COMPONENT Runtime
    LIBRARY DESTINATION ${ENV_LIBRARY_DIR}
        COMPONENT Runtime
    ARCHIVE DESTINATION ${ENV_ARCHIVE_DIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

# Install cmake configure files
install(
    EXPORT ${PROJECT_NAME}Target
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SeetaFace6"
    NAMESPACE
        SeetaFace6::
    )
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${BUILD_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SeetaAuthorizeConfig.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SeetaFace6")

install(DIRECTORY ${SOLUTION_DIR}/include/
    DESTINATION ${ENV_HEADER_DIR})
