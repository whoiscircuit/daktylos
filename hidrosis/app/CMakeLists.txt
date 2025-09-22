project(hidrosis-src C)

add_executable(${PROJECT_NAME} "src/main.c")
target_link_libraries(${PROJECT_NAME} PRIVATE hidapi::hidapi)
