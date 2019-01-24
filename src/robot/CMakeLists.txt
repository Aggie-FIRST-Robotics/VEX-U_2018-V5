include(src/robot/catapult/CMakeLists.txt)
include(src/robot/drive/CMakeLists.txt)

set(
        robot-src
        ${robot-drive-src}
        ${robot-catapult-src}
)

set(
        robot-test-src
        ${robot-drive-test-src}
        ${robot-catapult-test-src}
)

set(
        robot-V5-src
        ${robot-drive-V5-src}
        ${robot-catapult-V5-src}
        src/robot/robot.cpp
)