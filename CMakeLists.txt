cmake_minimum_required (VERSION 3.10 FATAL_ERROR)

project (CameraStateMachine
  VERSION 0.1.0.0
  DESCRIPTION "Camera state machine."
  LANGUAGES CXX
)

add_executable (${PROJECT_NAME})

target_compile_options (${PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      -Wall
      -Wextra
      -Wpedantic
      -pedantic-errors
    >
    $<$<CXX_COMPILER_ID:MSVC>:
      /Wall
      /EHsc
      /MP
    >
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:
      /Zi
      /MDd
    >
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:
      /MD
    >
)

set (SOURCE_FILES
  "./src/main.cpp"
  "./src/camera.cpp"
  "./src/camera.hpp"
  "./src/camera_state_machine.cpp"
  "./src/camera_state_machine.hpp"
)

source_group (TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  FILES
    ${SOURCE_FILES}
)

target_sources (${PROJECT_NAME}
  PRIVATE
    ${SOURCE_FILES}
)

set_target_properties (${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    USE_FOLDERS ON
)
