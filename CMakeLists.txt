cmake_minimum_required(VERSION 3.16)
project(NauvooLegion VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/Engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/Systems)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/Characters)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/Data)

# Source files (only .cpp files should be listed as sources)
set(ENGINE_SOURCES
    source/Engine/GameManager.cpp
    source/Engine/Game.cpp
)

set(SYSTEMS_SOURCES
    source/Systems/ReputationManager.cpp
    source/Systems/NPCScheduleManager.cpp
    source/Systems/DialogueManager.cpp
    source/Systems/CombatSystem.cpp
    source/Systems/SaveGameManager.cpp
)

# Main executable
add_executable(nauvoo_game
    source/main.cpp
    ${ENGINE_SOURCES}
    ${SYSTEMS_SOURCES}
)

# Test executable
add_executable(nauvoo_tests
    source/Tests/test_runner.cpp
    ${ENGINE_SOURCES}
    ${SYSTEMS_SOURCES}
)

# Compiler flags
if(MSVC)
    target_compile_options(nauvoo_game PRIVATE /W4)
    target_compile_options(nauvoo_tests PRIVATE /W4)
else()
    target_compile_options(nauvoo_game PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(nauvoo_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Output directories
set_target_properties(nauvoo_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(nauvoo_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
