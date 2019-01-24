include(src/robot/drive/CMakeLists.txt)

set(
        robot-src
        ${robot-drive-src}
)

set(
        robot-test-src
        ${robot-drive-test-src}
)

set(
        robot-V5-src
        ${robot-drive-V5-src}
        src/robot/robot.cpp
)