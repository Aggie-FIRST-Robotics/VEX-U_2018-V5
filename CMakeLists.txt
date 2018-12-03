cmake_minimum_required(VERSION 3.12)
project(VEX_U_2018_V5)

set(CMAKE_CXX_STANDARD 17)

set(upload_command "prosv5" "upload" "--debug" "--verbose")
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

include_directories(
        include
)

# General source files list with no calls to pros, files with pros calls need to be added to only_V5_src_files
set(
        src_files
        src/afr-vexu-lib/action.cpp
        src/afr-vexu-lib/commandable.cpp
        src/afr-vexu-lib/ordered_input.cpp
        src/afr-vexu-lib/readable.cpp
        src/afr-vexu-lib/scheduled.cpp
        src/afr-vexu-lib/state.cpp
        src/afr-vexu-lib/state_controller.cpp
        src/afr-vexu-lib/subsystem_controller.cpp
)

set(
        only_test_src_files
)

# TODO: These files need to be moved to src_files by adding their referenced functions to only_test
set(
        only_V5_src_files
        src/afr-vexu-lib/base-commandable/motor_commandable.cpp
        src/afr-vexu-lib/base-commandable/adi_analog_commandable.cpp
        src/afr-vexu-lib/base-readable/adi_encoder_readable.cpp
        src/afr-vexu-lib/base-readable/motor_encoder_readable.cpp
        src/afr-vexu-lib/base-readable/adi_analog_readable.cpp
        src/afr-vexu-lib/base-readable/adi_digital_readable.cpp
)

set(
        pros_src_files
        src/autonomous.cpp
        src/initialize.cpp
        src/opcontrol.cpp
)

add_compile_definitions(AFR_VEXU_TEST AFR_VEXU_THROW_ON_ERROR)
add_executable(APITest ${src_files} ${only_test_src_files} test/api_test.cpp)
add_executable(DONOTCOMPILE ${only_V5_src_files} blank/v5_files_include.cpp blank/blank.cpp)

# Blank targte for running build.bat externally
add_executable(BlankBuild blank/blank.cpp)
add_executable(BlankUpload blank/blank.cpp)

# Builds program
add_custom_target(
        Build
        "$(MAKE)"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        VERBATIM
        SOURCES ${src_files} ${pros_src_files} ${only_V5_src_files}
)

# Builds and uploads program
add_custom_target(
        Upload
        ${upload_command}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/"
        VERBATIM
        SOURCES ${src_files} ${pros_src_files} ${only_V5_src_files}
)

# Creates the bin directory for building with pros make file
#add_custom_target(Before ALL
#        COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/bin"
#        )

#add_dependencies(Build Before)
#add_dependencies(Upload Build)