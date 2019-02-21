include(src/robot2/cap/CMakeLists.txt)
include(src/robot2/drive/CMakeLists.txt)
include(src/robot2/ball-intake/CMakeLists.txt)

set(
        robot2-src
        ${robot2-cap-src}
        ${robot2-drive-src}
        ${ball-intake-src}
)

set(
        robot2-test-src
        ${robot2-cap-test-src}
        ${robot2-drive-test-src}
        ${ball-intake-test-src}
)

set(
        robot2-V5-src
        ${robot2-cap-V5-src}
        ${robot2-drive-V5-src}
        ${ball-intake-V5-src}

        src/robot2/robot.cpp
)
