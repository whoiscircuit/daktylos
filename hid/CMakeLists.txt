
cmake_minimum_required(VERSION 3.14)
project(daktylos-hid C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(libs/libusb EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME} "src/main.c")
target_link_libraries(${PROJECT_NAME} PUBLIC usb-1.0)
