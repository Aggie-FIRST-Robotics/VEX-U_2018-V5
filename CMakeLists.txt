cmake_minimum_required(VERSION 3.12)
project(VEX_U_2018_V5)

set(CMAKE_CXX_STANDARD 17)

set(upload_command "prosv5" "upload" "--debug" "--verbose")

include_directories(include)

# Source files list, TODO: Add all cpp files
set(src_files
        src/autonomous.cpp
        src/initialize.cpp
        src/opcontrol.cpp
        )

# Builds program
add_custom_target(Build
        "$(MAKE)"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        VERBATIM
        SOURCES ${src_files}
        )

# Builds and uploads program
add_custom_target(Upload
        ${upload_command} ${upload_args}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/"
        VERBATIM
        SOURCES ${src_files}
        )

# Creates the bin directory for building with pros make file
add_custom_target(Before ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/bin"
        )

add_dependencies(Build Before)
add_dependencies(Upload Build)
