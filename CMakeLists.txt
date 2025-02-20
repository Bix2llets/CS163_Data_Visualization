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
include_directories(include/animation)
include_directories(include/scene)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/basis/button.cpp
    src/basis/utility.cpp
    src/basis/GUIObject.cpp
    src/basis/colorPalette.cpp
    src/basis/textBox.cpp

    src/animation/animation.cpp
    src/animation/arrow.cpp
    src/animation/animationColor.cpp
    
    src/GUI/welcomeMenu.cpp
    
    src/structures/singlyLinkedList.cpp
    src/structures/TrieState.cpp
)
# For build and run purpose
file(COPY ${RAYLIB}
    DESTINATION ${PROJECT_SOURCE_DIR}/build)

# For releasing


target_link_libraries(${PROJECT_NAME} PUBLIC ${RAYLIB})

# file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build/assets)
file (COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_SOURCE_DIR}/build)
# file (COPY ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.exe DESTINATION ${PROJECT_SOURCE_DIR}/bin)
