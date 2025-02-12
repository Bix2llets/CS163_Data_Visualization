cmake_minimum_required(VERSION 3.11)
project(DATA_VISUALIZER VERSION 1.0 DESCRIPTION "" LANGUAGES CXX)
# target_include_directories(include/raylib PUBLIC)
set(
    RAYLIB
    # ${PROJECT_SOURCE_DIR}/include/raylib/lib/libraylib.a
    ${PROJECT_SOURCE_DIR}/include/raylib/lib/libraylibdll.a
    ${PROJECT_SOURCE_DIR}/include/raylib/lib/raylib.dll
)
include_directories(include/raylib/include)
include_directories(include/raylib/include/src)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)
file(COPY ${PROJECT_SOURCE_DIR}/include/raylib/lib/raylib.dll
    DESTINATION ${PROJECT_SOURCE_DIR}/build)
target_link_libraries(${PROJECT_NAME} PUBLIC ${RAYLIB})
