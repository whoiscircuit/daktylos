cmake_minimum_required(VERSION 3.0)

project(hidrosis-root C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(HIDAPI_WITH_LIBUSB FALSE)
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(libs/hidapi)

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /std:c11")
    add_subdirectory(libs/cjson)
    string(REPLACE "/Za" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
else()
    add_subdirectory(libs/cjson)
endif()

add_subdirectory(app)

