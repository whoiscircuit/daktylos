cmake_minimum_required(VERSION 3.0)

project(hidrosis-root C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(HIDAPI_WITH_LIBUSB FALSE)
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(libs/hidapi EXCLUDE_FROM_ALL)
add_subdirectory(libs/cjson EXCLUDE_FROM_ALL)
add_subdirectory(app)

