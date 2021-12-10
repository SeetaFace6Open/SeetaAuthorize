@PACKAGE_INIT@

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")

include(CMakeFindDependencyMacro)
find_dependency(ORZ)
include("${CMAKE_CURRENT_LIST_DIR}/SeetaAuthorizeTarget.cmake")
