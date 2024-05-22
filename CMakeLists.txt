cmake_minimum_required(VERSION 3.16)
set(project TheGame)
project(${project} LANGUAGES CXX)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(${project}_SOURCES
        "script/main.cpp"
        "script/game/game.cpp"
        "script/level/level.cpp"
        "script/objects/objects.cpp"
        "script/player/player.cpp"
        "script/menu/menu.cpp"
)

set(${project}_HEADERS
        "script/constants/constants.h"
        "script/game/game.h"
        "script/level/level.h"
        "script/objects/objects.h"
        "script/player/player.h"
        "script/menu/menu.h"
)

add_custom_target(MyTarget ALL)
add_custom_command(TARGET MyTarget PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/"sources"/ $<TARGET_FILE_DIR:TheGame>/"sources")

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} PRIVATE sfml-graphics)
target_link_libraries(${project} PRIVATE sfml-audio)
target_compile_features(${project} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${project}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${project}>
        VERBATIM)
endif()

install(TARGETS ${project})
