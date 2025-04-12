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
include_directories(include)
include_directories(include/structures/graph)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    
    src/basis/button.cpp
    src/basis/utility.cpp
    src/basis/GUIObject.cpp
    src/basis/colorPalette.cpp
    src/basis/form.cpp
    src/basis/textbox.cpp

    src/basis/overload.cpp
    src/basis/toggleable.cpp
    src/basis/mForm.cpp
    src/basis/diceButton.cpp
    src/basis/textureButton.cpp
    src/basis/dynamicColor.cpp

    src/animation/animation.cpp
    src/animation/animationColor.cpp
    
    src/GUI/welcomeMenu.cpp
    src/GUI/CodePane.cpp
    src/GUI/menuPane.cpp
    src/GUI/menu.cpp
    src/GUI/AppInfo.cpp
    
    src/mLib/tinyfiledialogs.cpp

    src/structures/SLL/SLLNode.cpp
    src/structures/SLL/singlyLinkedList.cpp
    src/structures/trie/Trie.cpp
    src/structures/trie/TrieState.cpp

    src/structures/graph/edge.cpp
    src/structures/graph/node.cpp
    src/structures/graph/graph.cpp
    src/structures/AVL/AVL.cpp 
    src/structures/AVL/AVLState.cpp
    src/structures/hash/hash.cpp
    src/structures/hash/hashState.cpp
    
    src/scene/SLLScene.cpp
    src/scene/GraphScene.cpp
    src/scene/TrieScene.cpp
    src/scene/AVLScene.cpp
    src/scene/HashScene.cpp
    src/mainLoop.cpp
)
# For build and run purpose
file(COPY ${RAYLIB}
    DESTINATION ${PROJECT_SOURCE_DIR}/build)

# For releasing


target_link_libraries(${PROJECT_NAME} PUBLIC ${RAYLIB} comdlg32)

# file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build/assets)
file (COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_SOURCE_DIR}/build)
# file (COPY ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.exe DESTINATION ${PROJECT_SOURCE_DIR}/bin)


add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.exe
    ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.exe)
