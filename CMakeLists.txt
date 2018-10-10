cmake_minimum_required(VERSION 3.12)
project(VEX_U_2018_V5)

set(CMAKE_CXX_STANDARD 14)

set(build_command "prosv5" "make" "--debug")

set(upload_command "prosv5" "upload")
include_directories(include)

execute_process(
        COMMAND "build.bat"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/"
)

set(src_files src/autonomous.cpp src/initialize.cpp src/opcontrol.cpp)

add_custom_target(Upload
        ${upload_command} ${upload_args}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/"
        VERBATIM
        SOURCES ${src_files})

add_dependencies(Upload Build)

#add_custom_command(TARGET Build
#        PRE_BUILD
#        COMMAND ${build_command} ${build_args}
#        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#        VERBATIM)
