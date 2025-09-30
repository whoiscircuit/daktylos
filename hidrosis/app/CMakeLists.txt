project(hidrosis C)

# Detect if running on Linux with X11

include_directories(${PROJECT_NAME} "include/")

add_executable(${PROJECT_NAME}
    "src/main.c"
    "src/layout/linux.c" "src/layout/macos.c" "src/layout/windows.c" "src/layout/util.c"
    "src/log/unix.c" "src/log/log.c" "src/log/util.c" "src/log/windows.c"
    "src/os_type.c"
    "src/util.c"
)
target_link_libraries(${PROJECT_NAME} PRIVATE hidapi::hidapi)


find_package(X11 REQUIRED)
find_library(XKBFILE_LIB xkbfile REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${X11_LIBRARIES}
    ${XKBFILE_LIB}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${X11_INCLUDE_DIR})


if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Carbon")
endif()

if(WIN32)
    # Win32 APIs are part of user32.dll
    target_link_libraries(${PROJECT_NAME} user32)
endif()
