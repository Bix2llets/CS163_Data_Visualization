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
include_directories(include/raygui/src)
include_directories(include/GUI)
include_directories(include/basis)
include_directories(include/structures)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)
# For build and run purpose
file(COPY ${RAYLIB}
    DESTINATION ${PROJECT_SOURCE_DIR}/build)

# For releasing
file(MAKE_DIRECTORY bin)
file (COPY ${RAYLIB} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
file (COPY ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.exe DESTINATION ${PROJECT_SOURCE_DIR}/bin)

    
target_link_libraries(${PROJECT_NAME} PUBLIC ${RAYLIB})
