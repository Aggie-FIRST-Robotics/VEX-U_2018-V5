include(src/robot/catapult/CMakeLists.txt)
include(src/robot/cap/CMakeLists.txt)
include(src/robot/drive/CMakeLists.txt)

set(
        robot-src
        ${robot-drive-src}
        ${robot-catapult-src}
        ${robot-cap-src}
        ${robot-shooter-src}
)

set(
        robot-test-src
        ${robot-drive-test-src}
        ${robot-catapult-test-src}
        ${robot-cap-test-src}
        ${robot-shooter-test-src}

)

set(
        robot-V5-src
        ${robot-drive-V5-src}
        ${robot-catapult-V5-src}
        ${robot-cap-V5-src}
        ${robot-shooter-V5-src}

        src/robot/robot.cpp
)
