include(src/robot2/ball-intake/CMakeLists.txt)
include(src/robot2/cap/CMakeLists.txt)
include(src/robot2/drive/CMakeLists.txt)
include(src/robot2/shooter/CMakeLists.txt)

set(
        robot2-src
        ${robot2-ball-intake-src}
        ${robot2-cap-src}
        ${robot2-drive-src}
        ${robot2-shooter-src}
)

set(
        robot2-test-src
        ${robot2-ball-intake-test-src}
        ${robot2-cap-test-src}
        ${robot2-drive-test-src}
        ${robot2-shooter-test-src}
)

set(
        robot2-V5-src
        ${robot2-ball-intake-V5-src}
        ${robot2-cap-V5-src}
        ${robot2-drive-V5-src}
        ${robot2-shooter-V5-src}

        src/robot2/robot.cpp
        src/robot2/auto.cpp
)