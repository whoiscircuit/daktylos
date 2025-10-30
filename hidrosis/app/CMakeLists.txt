project(hidrosis C)

# Detect if running on Linux with X11

include_directories(${PROJECT_NAME} "include/")

SET(C_FILES "src/main.c"
    "src/layout/linux.c" "src/layout/x11.c" "src/layout/wayland.c" "src/layout/macos.c" "src/layout/windows.c" "src/layout/util.c"
    "src/log/unix.c" "src/log/log.c" "src/log/util.c" "src/log/windows.c"
    "src/os_type.c" "src/signal_control/unix.c" "src/signal_control/windows.c"
    "src/util.c")

if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_executable(${PROJECT_NAME} WIN32 ${C_FILES})
    else()
        add_executable(${PROJECT_NAME} ${C_FILES})
    endif()
else()
    add_executable(${PROJECT_NAME} ${C_FILES})
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE hidapi::hidapi)
target_link_libraries(${PROJECT_NAME} PRIVATE cjson)

add_compile_definitions(${PROJECT_NAME} PRIVATE _GNU_SOURCE)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
    pkg_check_modules(XKBCOMMON REQUIRED xkbcommon)
    find_library(XKBFILE_LIB xkbfile REQUIRED)
    target_ink_libraries(${PROJECT_NAME} PRIVATE
        ${X11_LIBRARIES}
        ${WAYLAND_CLIENT_LIBRARIES}
        ${XKBFILE_LIB}
        ${XKBCOMMON_LIBRARIES}
    )
    target_include_directories(${PROJECT_NAME} PRIVATE 
        ${X11_INCLUDE_DIR}
        ${XKBCOMMON_INCLUDE_DIRS}
        ${WAYLAND_CLIENT_INCLUDE_DIRS}
    )
    target_compile_options(${PROJECT_NAME} PRIVATE ${WAYLAND_CLIENT_CFLAGS_OTHER})
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Carbon")
elseif(WIN32)
    # Win32 APIs are part of user32.dll
    target_link_libraries(${PROJECT_NAME} PRIVATE user32)
endif()
